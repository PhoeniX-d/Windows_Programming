using System;
using System.Windows.Forms;
using System.Drawing;

public class CSharpMsgHandling : Form
{
    public static void Main()
    {
        Application.Run(new CSharpMsgHandling());
    }

    public CSharpMsgHandling()
    {
        Width = 800;
        Height = 600;
        ResizeRedraw = true;
        BackColor = System.Drawing.Color.Black;
        this.KeyDown += new KeyEventHandler(MyKeyDown);
        this.MouseDown += new MouseEventHandler(MyMouseClicked);
    }

    void MyKeyDown(Object sender, KeyEventArgs e)
    {
        MessageBox.Show("Some Key is Pressed");
    }

    void MyMouseClicked(Object sender, MouseEventArgs e)
    {
        MessageBox.Show("Mouse Key is clicked");
    }
}
