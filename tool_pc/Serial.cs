using System;
using System.IO.Ports;
using System.Collections.Generic;

namespace YabrTool
{
    public class Serial
    {
        private enum ReceiveState
        {
            Nothing,
            Begin,
            Data,
            End
        };

        private YabrTool yabrTool;
        private SerialPort port = new SerialPort();
        private List<Byte> packetData = new List<Byte>();
        private Byte command;
        private Boolean decryptNext;
        private Boolean inPacket;

        public Boolean IsConnected { get { return port.IsOpen; } }

        public Serial(YabrTool yabrTool)
        {
            this.yabrTool = yabrTool;
            port.DataReceived += new SerialDataReceivedEventHandler(DataReceived);
        }

        void DataReceived(Object sender, SerialDataReceivedEventArgs e)
        {
            while (ReceivePacket())
            {
                switch (command)
                {
                    case (Byte)'t':
                    {
                        Int16[] measurement = new Int16[packetData.Count / 2];
                        for (Int32 i = 0; i < packetData.Count / 2; ++i)
                        {
                            measurement[i] = (Int16)(packetData[2 * i] << 8 | packetData[2 * i + 1]);
                        }
                        yabrTool.Channels.AppendMeasurement(measurement);
                        break;
                    }
                }
            }
        }

        public void Connect(String portName)
        {
            Disconnect();
            port.PortName = portName;
            port.BaudRate = 115200;
            port.Open();
        }

        public void Disconnect()
        {
            if (port.IsOpen)
            {
                port.Close();
            }
        }

        private ReceiveState Receive(ref Byte received)
        {
            Byte rawByte;
    
            if(!decryptNext)
            {
                if(port.BytesToRead > 0)
                {
                    rawByte = (Byte)port.ReadByte();
                    if(rawByte == '}')
                    {
                        return ReceiveState.End;
                    }
                    else if(rawByte == '{')
                    {
                        return ReceiveState.Begin;
                    }
                    else if(rawByte == '|')
                    {
                        decryptNext = true;
                    }
                    else
                    {
                        received = rawByte;
                        return ReceiveState.Data;
                    }
                }
            }
    
            if(decryptNext)
            {
                if(port.BytesToRead > 0)
                {
                    rawByte = (Byte)port.ReadByte();
                    decryptNext = false;
                    received = (Byte)(rawByte ^ 0x20);
                    return ReceiveState.Data;
                }
            }

            return ReceiveState.Nothing;
        }

        private Boolean ReceivePacket()
        {
            ReceiveState state = ReceiveState.Nothing;
            Byte received = 0;
    
            while((state = Receive(ref received)) != ReceiveState.Nothing)
            {
                if(inPacket)
                {
                    // in packet
                    if(state == ReceiveState.Begin)
                    {
                        // incomplete packet in buffer, discard
                        packetData.Clear();
                        command = 0;
                    }
                    else if(state == ReceiveState.Data)
                    {
                        if(command == 0)
                        {
                            command = received;
                        }
                        else
                        {
                            packetData.Add(received);
                        }
                    }
                    else if(state == ReceiveState.End)
                    {
                        // packet complete, deliver
                        inPacket = false;
                        return true;
                    }
                }
                else
                {
                    // outside packet
                    if(state == ReceiveState.Begin)
                    {
                        inPacket = true;
                        packetData.Clear();
                        command = 0;
                    }
                    else if(state == ReceiveState.Data)
                    {
                        ; // ignore
                    }
                    else if(state == ReceiveState.End)
                    {
                        ; // ignore
                    }
                }
            }
    
            return false;
        }
    }
}
