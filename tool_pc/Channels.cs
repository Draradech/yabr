using System;
using System.Windows.Forms;

namespace YabrTool
{
    public class Channels : UserControl
    {
        private TableLayoutPanel tableLayoutPanel1;
        private YabrTool yabrTool;

        public Channels()
        {
            InitializeComponent();
        }

        public Channels(YabrTool yabrTool)
        {
            this.yabrTool = yabrTool;
            InitializeComponent();
        }

        public void AppendMeasurement(Int16[] measurement)
        {
            throw new System.NotImplementedException();
        }

        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 5;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(750, 150);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // Channels
            // 
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Channels";
            this.Size = new System.Drawing.Size(750, 150);
            this.ResumeLayout(false);

        }
    }
}
