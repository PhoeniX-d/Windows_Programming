using System;
using System.Windows.Forms;
using System.Drawing;

public class CSharpHelloWindow : Form
{
    public static void Main()
    {
        Application.Run(new CSharpHelloWindow());
    }

    public CSharpHelloWindow()
    {
        Width = 800;
        Height = 600;
        ResizeRedraw = true;
        BackColor = System.Drawing.Color.Black;
    }

    protected override void OnPaint(PaintEventArgs pea)
    {
        Graphics grfx = pea.Graphics;
        StringFormat strfmt = new StringFormat();
        strfmt.Alignment = StringAlignment.Center;
        strfmt.LineAlignment = StringAlignment.Center;
        grfx.DrawString(
            "Hello, World !!!",
            Font,
            new SolidBrush(System.Drawing.Color.Green),
            ClientRectangle,
            strfmt
        );
    }
}
