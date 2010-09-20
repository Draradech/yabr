using System;
using System.Diagnostics;
using System.Windows.Forms;

namespace YabrTool
{
    public partial class YabrTool : Form
    {
        private Stopwatch watch = new Stopwatch();
        private Int32 frames = 0;

        public YabrTool()
        {
            InitializeComponent();
            watch.Start();
        }

        private void glControl1_Paint(object sender, PaintEventArgs e)
        {
            frames++;
            if (watch.ElapsedMilliseconds > 1000)
            {
                button1.Text = String.Format("{0} fps", frames * 1000 / (Int32)watch.ElapsedMilliseconds);
                watch.Reset();
                watch.Start();
                frames = 0;
            }
        }
    }
}
