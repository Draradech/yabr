using System;
using System.Windows.Forms;

namespace YabrTool
{
    public class Channels : UserControl
    {
        private TableLayoutPanel primaryLayout;
        private Channel channel1;
        private Channel channel2;
        private Channel channel3;
        private Channel channel4;
        private Channel channel5;
        private YabrTool yabrTool;

        public Channels(YabrTool yabrTool)
        {
            this.yabrTool = yabrTool;
            InitializeComponent();
        }

        public void AppendMeasurement(Int16[] measurement)
        {
            for (Int32 i = 0; i < measurement.Length; ++i)
            {
                Console.WriteLine(String.Format("{0}", measurement[i]));
            }
            Console.WriteLine();
            yabrTool.Canvas.Invalidate();
        }

        private void InitializeComponent()
        {
            primaryLayout = new TableLayoutPanel();
            channel1 = new Channel();
            channel2 = new Channel();
            channel3 = new Channel();
            channel4 = new Channel();
            channel5 = new Channel();

            // 
            // primaryLayout
            // 
            primaryLayout.Dock = DockStyle.Fill;
            primaryLayout.AutoSize = true;
            primaryLayout.ColumnCount = 5;
            primaryLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20F));
            primaryLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20F));
            primaryLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20F));
            primaryLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20F));
            primaryLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 20F));
            primaryLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            primaryLayout.Controls.Add(channel1, 0, 0);
            primaryLayout.Controls.Add(channel2, 1, 0);
            primaryLayout.Controls.Add(channel3, 2, 0);
            primaryLayout.Controls.Add(channel4, 3, 0);
            primaryLayout.Controls.Add(channel5, 4, 0);

            //
            // channel1
            //
            channel1.BorderStyle = BorderStyle.Fixed3D;

            //
            // channel2
            //
            channel2.BorderStyle = BorderStyle.Fixed3D;

            //
            // channel3
            //
            channel3.BorderStyle = BorderStyle.Fixed3D;

            //
            // channel4
            //
            channel4.BorderStyle = BorderStyle.Fixed3D;

            //
            // channel5
            //
            channel5.BorderStyle = BorderStyle.Fixed3D;

            // 
            // Channels
            // 
            Controls.Add(primaryLayout);
        }
    }
}
