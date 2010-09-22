using System.Windows.Forms;

namespace YabrTool
{
    class Channel : UserControl
    {
        private FlowLayoutPanel primaryLayout;
        private Label nameLabel;
        private Label valueLabel;

        public Channel()
        {
            InitializeComponent();
        }
    
        private void InitializeComponent()
        {
            this.primaryLayout = new System.Windows.Forms.FlowLayoutPanel();
            this.nameLabel = new System.Windows.Forms.Label();
            this.valueLabel = new System.Windows.Forms.Label();
            this.primaryLayout.SuspendLayout();
            this.SuspendLayout();
            // 
            // primaryLayout
            // 
            this.primaryLayout.AutoSize = true;
            this.primaryLayout.Controls.Add(this.nameLabel);
            this.primaryLayout.Controls.Add(this.valueLabel);
            this.primaryLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.primaryLayout.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.primaryLayout.Location = new System.Drawing.Point(0, 0);
            this.primaryLayout.Name = "primaryLayout";
            this.primaryLayout.Size = new System.Drawing.Size(150, 150);
            this.primaryLayout.TabIndex = 0;
            // 
            // nameLabel
            // 
            this.nameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nameLabel.Location = new System.Drawing.Point(3, 0);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(100, 23);
            this.nameLabel.TabIndex = 0;
            this.nameLabel.Text = "name";
            // 
            // valueLabel
            // 
            this.valueLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.valueLabel.Location = new System.Drawing.Point(3, 23);
            this.valueLabel.Name = "valueLabel";
            this.valueLabel.Size = new System.Drawing.Size(100, 23);
            this.valueLabel.TabIndex = 1;
            this.valueLabel.Text = "value";
            // 
            // Channel
            // 
            this.AutoSize = true;
            this.Controls.Add(this.primaryLayout);
            this.Name = "Channel";
            this.primaryLayout.ResumeLayout(false);
            this.primaryLayout.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
    }
}
