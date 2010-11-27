using System;
using System.Drawing;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace YabrTool
{
    public class Canvas : GLControl
    {
        private Random r = new Random();
        private YabrTool yabrTool;

        public Canvas(YabrTool yabrTool)
        {
            this.yabrTool = yabrTool;
        }

        private void glLine(Int32 x1, Int32 y1, Int32 x2, Int32 y2)
        {
            if (Math.Abs(x1 - x2) < Math.Abs(y1 - y2) / 2)
            {
                GL.Vertex2(x1 + 0.5, Math.Min(y1, y2));
                GL.Vertex2(x2 + 0.5, Math.Max(y1, y2) + 1.0);
            }
            else if (Math.Abs(y1 - y2) < Math.Abs(x1 - x2) / 2)
            {
                GL.Vertex2(Math.Min(x1, x2), y1 + 0.5);
                GL.Vertex2(Math.Max(x1, x2) + 1.0, y2 + 0.5);
            }
            else
            {
                GL.Vertex2(Math.Min(x1, x2), Math.Min(y1, y2));
                GL.Vertex2(Math.Max(x1, x2) + 1.0, Math.Max(y1, y2) + 1.0);
            }
        }

        protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
        {
            base.OnPaint(e);

            GL.Clear(ClearBufferMask.ColorBufferBit);

            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadIdentity();

            GL.Begin(BeginMode.Lines);
            Int32 y = 0, yo = 0;
            for (Int32 i = 0; i < 5; ++i)
            {
                GL.Color3(r.NextDouble() / 4, r.NextDouble() / 4, r.NextDouble() / 4);
                for (Int32 x = 0; x < Width; ++x)
                {
                    y = (Int32)(r.NextDouble() * Height);
                    glLine(x, yo, x, y);
                    yo = y;
                }
            }
            GL.End();

            SwapBuffers();
        }

        protected override void OnResize(System.EventArgs e)
        {
            base.OnResize(e);

            if (IsHandleCreated)
            {
                GL.MatrixMode(MatrixMode.Projection);
                GL.LoadIdentity();
                GL.Ortho(0, Width, 0, Height, -1, 1);
                GL.Viewport(0, 0, Width, Height);
            }
        }

        protected override void OnLoad(System.EventArgs e)
        {
            base.OnLoad(e);

            GL.Disable(EnableCap.DepthTest);
            GL.ClearColor(Color.Black);
            OnResize(null);
        }
    }
}
