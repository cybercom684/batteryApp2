using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS2SX.SwitchFormsLib;
public class ProgressBar : Control
{
    public int value;
    public int width_chars;

    public ProgressBar(int widthChars)
    {
        width_chars = widthChars;
        visible = 1;
        focusable = 0;
    }

    public override void Draw()
    {
        if (visible == 0) return;
        int fill = (value * width_chars) / 100;
        Console.Write($"\x1B[{y};{x}H[");
        int i = 0;
        while (i < width_chars)
        {
            if (i < fill)
                Console.Write("#");
            else
                Console.Write("-");
            i++;
        }
        Console.Write($"] {value}%%");
    }
}