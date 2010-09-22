using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Windows.Forms;

namespace YabrTool
{
    public partial class YabrTool : Form
    {
        private Stopwatch watch = new Stopwatch();
        private Int32 frames = 0;
        private Serial serial;
        private Channels channels;
        private Canvas canvas;

        public Serial Serial { get { return serial; } }
        public Channels Channels { get { return channels; } }
        public Canvas Canvas { get { return canvas; } }
        
        public YabrTool()
        {
            InitializeComponent();

            serial = new Serial(this);
            channels = new Channels(this);
            canvas = new Canvas(this);

            canvas.Dock = DockStyle.Fill;
            canvasContainer.Controls.Add(canvas); 
            canvas.Paint += new PaintEventHandler(canvas_Paint);

            channels.Dock = DockStyle.Fill;
            channelsContainer.Controls.Add(channels);

            RefreshPorts();
            watch.Start();
        }

        private void RefreshPorts()
        {
            comPortComboBox.Items.Clear();

            String[] pnames = SerialPort.GetPortNames();
            List<String> ports = new List<String>(pnames);
            ports.Sort();
            foreach (String name in ports)
            {
                String fixedname = name;
                if(name[name.Length - 1] < '0' || name[name.Length - 1] > '9')
                {
                    fixedname = name.Remove(name.Length - 1);
                }
                comPortComboBox.Items.Add(fixedname);
            }

            comPortComboBox.SelectedIndex = 0;
        }

        private void canvas_Paint(object sender, PaintEventArgs e)
        {
            frames++;
            if (watch.ElapsedMilliseconds > 1000)
            {
                fpsLabel.Text = String.Format("{0} fps", frames * 1000 / (Int32)watch.ElapsedMilliseconds);
                watch.Reset();
                watch.Start();
                frames = 0;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Serial.IsConnected)
            {
                Serial.Disconnect();
            }
            else
            {
                Serial.Connect(comPortComboBox.SelectedItem.ToString());
            }
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            RefreshPorts();
        }
    }
}
