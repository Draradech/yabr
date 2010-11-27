using System.Windows.Forms;
using System.Drawing;

namespace YabrTool
{
    class Channel : UserControl
    {
        private TableLayoutPanel primaryLayout;
        private Label nameLabel;
        private Label valueLabel;

        public Channel()
        {
            InitializeComponent();
        }
    
        private void InitializeComponent()
        {
            primaryLayout = new TableLayoutPanel();
            nameLabel = new Label();
            valueLabel = new Label();

            // 
            // primaryLayout
            // 
            primaryLayout.Dock = DockStyle.Fill;
            primaryLayout.AutoSize = true;
            primaryLayout.RowCount = 2;
            primaryLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            primaryLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            primaryLayout.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            primaryLayout.Controls.Add(nameLabel, 0, 0);
            primaryLayout.Controls.Add(valueLabel, 0, 1);

            // 
            // nameLabel
            // 
            nameLabel.Dock = DockStyle.Fill;
            nameLabel.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, ((byte)(0)));
            nameLabel.Text = "name";

            // 
            // valueLabel
            // 
            valueLabel.Dock = DockStyle.Fill;
            valueLabel.Font = new Font("Microsoft Sans Serif", 12F, FontStyle.Regular, GraphicsUnit.Point, ((byte)(0)));
            valueLabel.Text = "value";

            // 
            // Channel
            // 
            Dock = DockStyle.Fill;
            AutoSize = true;
            Controls.Add(primaryLayout);
        }
    }
}
