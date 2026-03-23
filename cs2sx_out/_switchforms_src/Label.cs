using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS2SX.SwitchFormsLib;
public class Label : Control
{
    private string _text;

    public Label(string text)
    {
        _text = text;
        visible = 1;
        focusable = 0;
    }

    public override void Draw()
    {
        if (visible == 0) return;
        Console.Write($"\x1B[{y};{x}H{_text}");
    }

    public void SetText(string text)
    {
        _text = text;
    }

    public string GetText()
    {
        return _text;
    }
}