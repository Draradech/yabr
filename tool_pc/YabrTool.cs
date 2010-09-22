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
        private Canvas canvas;

        public Serial Serial { get { return serial; } }
        public Channels Channels { get { return channels; } }
        public Canvas Canvas { get { return canvas; } }
        
        public YabrTool()
        {
            InitializeComponent();

            serial = new Serial(this);
            canvas = new Canvas(this);

            canvas.Dock = System.Windows.Forms.DockStyle.Fill;
            canvasContainer.Controls.Add(canvas); 
            canvas.Paint += new System.Windows.Forms.PaintEventHandler(canvas_Paint);

            RefreshPorts();
            watch.Start();
        }

        private void RefreshPorts()
        {
            comPortComboBox.Items.Clear();

            List<String> ports = new List<String>(SerialPort.GetPortNames());
            ports.Sort();
            foreach (String name in ports)
            {
                comPortComboBox.Items.Add(name);
            }

            comPortComboBox.SelectedIndex = 0;
        }

        private void canvas_Paint(object sender, PaintEventArgs e)
        {
            frames++;
            if (watch.ElapsedMilliseconds > 1000)
            {
                connectButton.Text = String.Format("{0} fps", frames * 1000 / (Int32)watch.ElapsedMilliseconds);
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
    }
}
