using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS2SX.SwitchFormsLib;
public class Button : Control
{
    private string _text;
    public int focused;
    public Action OnClick;

    public Button(string text)
    {
        _text = text;
        visible = 1;
        focusable = 1;
    }

    public override void Draw()
    {
        if (visible == 0) return;
        if (focused == 1)
            Console.Write($"\x1B[{y};{x}H> {_text} <");
        else
            Console.Write($"\x1B[{y};{x}H  {_text}  ");
    }

    public override void Update(ulong kDown, ulong kHeld)
    {
        if (focused == 1)
        {
            if (Input.IsDown(NpadButton.A))
                OnClick();
        }
    }
}