namespace YabrTool
{
    partial class YabrTool
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.primaryLayout = new System.Windows.Forms.TableLayoutPanel();
            this.toolbarLayout = new System.Windows.Forms.FlowLayoutPanel();
            this.comPortComboBox = new System.Windows.Forms.ComboBox();
            this.connectButton = new System.Windows.Forms.Button();
            this.canvasContainer = new System.Windows.Forms.Panel();
            this.channelsContainer = new System.Windows.Forms.Panel();
            this.refreshButton = new System.Windows.Forms.Button();
            this.fpsLabel = new System.Windows.Forms.Label();
            this.primaryLayout.SuspendLayout();
            this.toolbarLayout.SuspendLayout();
            this.SuspendLayout();
            // 
            // primaryLayout
            // 
            this.primaryLayout.ColumnCount = 1;
            this.primaryLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.primaryLayout.Controls.Add(this.toolbarLayout, 0, 0);
            this.primaryLayout.Controls.Add(this.canvasContainer, 0, 2);
            this.primaryLayout.Controls.Add(this.channelsContainer, 0, 1);
            this.primaryLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.primaryLayout.Location = new System.Drawing.Point(0, 0);
            this.primaryLayout.Name = "primaryLayout";
            this.primaryLayout.RowCount = 3;
            this.primaryLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.primaryLayout.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.primaryLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.primaryLayout.Size = new System.Drawing.Size(800, 600);
            this.primaryLayout.TabIndex = 0;
            // 
            // toolbarLayout
            // 
            this.toolbarLayout.AutoSize = true;
            this.toolbarLayout.Controls.Add(this.comPortComboBox);
            this.toolbarLayout.Controls.Add(this.refreshButton);
            this.toolbarLayout.Controls.Add(this.connectButton);
            this.toolbarLayout.Controls.Add(this.fpsLabel);
            this.toolbarLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolbarLayout.Location = new System.Drawing.Point(3, 3);
            this.toolbarLayout.Name = "toolbarLayout";
            this.toolbarLayout.Size = new System.Drawing.Size(794, 27);
            this.toolbarLayout.TabIndex = 0;
            // 
            // comPortComboBox
            // 
            this.comPortComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comPortComboBox.Location = new System.Drawing.Point(3, 3);
            this.comPortComboBox.Name = "comPortComboBox";
            this.comPortComboBox.Size = new System.Drawing.Size(121, 21);
            this.comPortComboBox.TabIndex = 0;
            // 
            // connectButton
            // 
            this.connectButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.connectButton.Location = new System.Drawing.Point(211, 3);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(75, 21);
            this.connectButton.TabIndex = 1;
            this.connectButton.Text = "Connect";
            this.connectButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // canvasContainer
            // 
            this.canvasContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.canvasContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.canvasContainer.Location = new System.Drawing.Point(3, 46);
            this.canvasContainer.Name = "canvasContainer";
            this.canvasContainer.Size = new System.Drawing.Size(794, 551);
            this.canvasContainer.TabIndex = 1;
            // 
            // channelsContainer
            // 
            this.channelsContainer.AutoSize = true;
            this.channelsContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.channelsContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.channelsContainer.Location = new System.Drawing.Point(3, 36);
            this.channelsContainer.Name = "channelsContainer";
            this.channelsContainer.Size = new System.Drawing.Size(794, 4);
            this.channelsContainer.TabIndex = 2;
            // 
            // refreshButton
            // 
            this.refreshButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.refreshButton.Location = new System.Drawing.Point(130, 3);
            this.refreshButton.Name = "refreshButton";
            this.refreshButton.Size = new System.Drawing.Size(75, 21);
            this.refreshButton.TabIndex = 2;
            this.refreshButton.Text = "Refresh";
            this.refreshButton.UseVisualStyleBackColor = true;
            this.refreshButton.Click += new System.EventHandler(this.refreshButton_Click);
            // 
            // fpsLabel
            // 
            this.fpsLabel.AutoSize = true;
            this.fpsLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.fpsLabel.Location = new System.Drawing.Point(292, 0);
            this.fpsLabel.Name = "fpsLabel";
            this.fpsLabel.Size = new System.Drawing.Size(21, 27);
            this.fpsLabel.TabIndex = 3;
            this.fpsLabel.Text = "fps";
            this.fpsLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // YabrTool
            // 
            this.ClientSize = new System.Drawing.Size(800, 600);
            this.Controls.Add(this.primaryLayout);
            this.Name = "YabrTool";
            this.Text = "YabrTool";
            this.primaryLayout.ResumeLayout(false);
            this.primaryLayout.PerformLayout();
            this.toolbarLayout.ResumeLayout(false);
            this.toolbarLayout.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel primaryLayout;
        private System.Windows.Forms.FlowLayoutPanel toolbarLayout;
        private System.Windows.Forms.ComboBox comPortComboBox;
        private System.Windows.Forms.Panel canvasContainer;
        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.Panel channelsContainer;
        private System.Windows.Forms.Button refreshButton;
        private System.Windows.Forms.Label fpsLabel;
    }
}

