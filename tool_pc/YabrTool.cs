using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Windows.Forms;
using System.Drawing;

namespace YabrTool
{
    public partial class YabrTool : Form
    {
        private TableLayoutPanel primaryLayout;
        private FlowLayoutPanel toolbarLayout;
        private ComboBox comPortComboBox;
        private Button connectButton;
        private Button refreshButton;
        private Label fpsLabel;

        private Channels channels;
        private Canvas canvas;
        private Serial serial;
        private Stopwatch watch = new Stopwatch();
        private Int32 frames = 0;

        public Serial Serial { get { return serial; } }
        public Channels Channels { get { return channels; } }
        public Canvas Canvas { get { return canvas; } }
        
        public YabrTool()
        {
            InitializeComponent();

            serial = new Serial(this);

            RefreshPorts();
            watch.Start();
        }

        private void RefreshPorts()
        {
            comPortComboBox.Items.Clear();

            String[] pnames = SerialPort.GetPortNames();
            List<String> ports = new List<String>(pnames);
            ports.Sort();

            // fix stupid M$ bug - ugly hack
            foreach (String name in ports)
            {
                String fixedname = name;
                if(name[name.Length - 1] < '0' || name[name.Length - 1] > '9')
                {
                    fixedname = name.Remove(name.Length - 1);
                }
                comPortComboBox.Items.Add(fixedname);
            }

            if (comPortComboBox.Items.Count > 0)
            {
                comPortComboBox.SelectedIndex = 0;
            }
        }

        private void onCanvasPaint(object sender, PaintEventArgs e)
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

        private void onConnectButtonClick(object sender, EventArgs e)
        {
            if (Serial.IsConnected)
            {
                Serial.Disconnect();
            }
            else
            {
                if (comPortComboBox.SelectedItem != null)
                {
                    Serial.Connect(comPortComboBox.SelectedItem.ToString());
                }
            }
        }

        private void onRefreshButtonClick(object sender, EventArgs e)
        {
            RefreshPorts();
        }

        private void InitializeComponent()
        {
            primaryLayout = new TableLayoutPanel();
            toolbarLayout = new FlowLayoutPanel();
            comPortComboBox = new ComboBox();
            connectButton = new Button();
            canvas = new Canvas(this);
            channels = new Channels(this);
            refreshButton = new Button();
            fpsLabel = new Label();

            // 
            // primaryLayout
            // 
            primaryLayout.Dock = DockStyle.Fill;
            primaryLayout.ColumnCount = 1;
            primaryLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            primaryLayout.RowCount = 3;
            primaryLayout.RowStyles.Add(new RowStyle());
            primaryLayout.RowStyles.Add(new RowStyle());
            primaryLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            primaryLayout.Controls.Add(toolbarLayout, 0, 0);
            primaryLayout.Controls.Add(canvas, 0, 2);
            primaryLayout.Controls.Add(channels, 0, 1);

            // 
            // toolbarLayout
            // 
            toolbarLayout.Dock = DockStyle.Fill;
            toolbarLayout.AutoSize = true;
            toolbarLayout.Controls.Add(comPortComboBox);
            toolbarLayout.Controls.Add(refreshButton);
            toolbarLayout.Controls.Add(connectButton);
            toolbarLayout.Controls.Add(fpsLabel);

            // 
            // comPortComboBox
            // 
            comPortComboBox.Dock = DockStyle.Fill;
            comPortComboBox.DropDownStyle = ComboBoxStyle.DropDownList;

            // 
            // connectButton
            // 
            connectButton.Dock = DockStyle.Fill;
            connectButton.Text = "Connect";
            connectButton.Click += new EventHandler(onConnectButtonClick);

            // 
            // canvas
            // 
            canvas.Dock = DockStyle.Fill;
            canvas.BorderStyle = BorderStyle.Fixed3D;
            canvas.Paint += new PaintEventHandler(onCanvasPaint);

            // 
            // channels
            // 
            channels.Dock = DockStyle.Fill;
            channels.AutoSize = true;

            // 
            // refreshButton
            // 
            connectButton.Dock = DockStyle.Fill;
            refreshButton.Text = "Refresh";
            refreshButton.Click += new System.EventHandler(onRefreshButtonClick);

            // 
            // fpsLabel
            // 
            fpsLabel.Dock = DockStyle.Fill;
            fpsLabel.AutoSize = true;
            fpsLabel.TextAlign = ContentAlignment.MiddleLeft;
            fpsLabel.Text = "fps";

            // 
            // YabrTool
            // 
            Dock = DockStyle.Fill; 
            ClientSize = new Size(800, 600);
            Controls.Add(primaryLayout);
            Text = "YabrTool";
        }
    }
}
