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
            this.primaryLayout = new System.Windows.Forms.TableLayoutPanel();
            this.channel1 = new Channel();
            this.channel2 = new Channel();
            this.channel3 = new Channel();
            this.channel4 = new Channel();
            this.channel5 = new Channel();
            this.primaryLayout.SuspendLayout();
            this.SuspendLayout();
            // 
            // primaryLayout
            // 
            this.primaryLayout.AutoSize = true;
            this.primaryLayout.ColumnCount = 5;
            this.primaryLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.primaryLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.primaryLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.primaryLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.primaryLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.primaryLayout.Controls.Add(this.channel1, 0, 0);
            this.primaryLayout.Controls.Add(this.channel2, 1, 0);
            this.primaryLayout.Controls.Add(this.channel3, 2, 0);
            this.primaryLayout.Controls.Add(this.channel4, 3, 0);
            this.primaryLayout.Controls.Add(this.channel5, 4, 0);
            this.primaryLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.primaryLayout.Location = new System.Drawing.Point(0, 0);
            this.primaryLayout.Name = "primaryLayout";
            this.primaryLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.primaryLayout.Size = new System.Drawing.Size(560, 150);
            this.primaryLayout.TabIndex = 0;
            // 
            // Channels
            // 
            this.AutoSize = true;
            this.Controls.Add(this.primaryLayout);
            this.Name = "Channels";
            this.Size = new System.Drawing.Size(560, 150);
            this.primaryLayout.ResumeLayout(false);
            this.primaryLayout.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
    }
}
