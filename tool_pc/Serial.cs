using System;
using System.IO.Ports;

namespace YabrTool
{
    public class Serial
    {
        private const Int32 DATABUFFER = 32;

        private enum ReceiveState
        {
            Nothing,
            Begin,
            Data,
            End
        };

        private YabrTool yabrTool;
        private SerialPort port = new SerialPort();
        private Byte[] packetData = new Byte[DATABUFFER];
        private Byte command;
        private Byte packetSize;
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
                        Int16[] test = new Int16[4];
                        for (Int32 i = 0; i < 4; ++i)
                        {
                            test[i] = (Int16)(packetData[2 * i] << 8 | packetData[2 * i + 1]);
                            Console.WriteLine(String.Format("{0}", test[i]));
                        }
                        Console.WriteLine();
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
                        packetSize = 0;
                    }
                    else if(state == ReceiveState.Data)
                    {
                        if(packetSize == 0)
                        {
                            command = received;
                        }
                        else if(packetSize - 1 < DATABUFFER)
                        {
                            packetData[packetSize - 1] = received;
                        }
                        else
                        {
                            // packet too long for buffer, discard
                            inPacket = false;
                        }
                        packetSize++;
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
                        packetSize = 0;
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
