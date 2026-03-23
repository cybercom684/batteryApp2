using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS2SX.SwitchFormsLib;
public class Form
{
    private List<Control> _controls;
    private int _focusedIndex;

    public Form()
    {
        _controls = new List<Control>();
        _focusedIndex = -1;
    }

    public void Add(Control control)
    {
        _controls.Add(control);
    }

    public void DrawAll()
    {
        int i = 0;
        while (i < _controls.Count)
        {
            var ctrl = _controls[i];
            if (ctrl.visible == 1)
                ctrl.Draw();
            i++;
        }
    }

    public void UpdateAll(ulong kDown, ulong kHeld)
    {
        if (Input.IsDown(NpadButton.Down))
            MoveFocus(1);
        if (Input.IsDown(NpadButton.Up))
            MoveFocus(-1);

        int i = 0;
        while (i < _controls.Count)
        {
            var ctrl = _controls[i];
            if (ctrl.visible == 1)
                ctrl.Update(kDown, kHeld);
            i++;
        }
    }

    public void MoveFocus(int direction)
    {
        int current = -1;
        int i = 0;
        while (i < _controls.Count)
        {
            if (_controls[i].focusable == 1)
            {
                var btn = (Button)_controls[i];
                if (btn.focused == 1)
                {
                    btn.focused = 0;
                    current = i;
                    break;
                }
            }
            i++;
        }

        int next = current;
        int tries = 0;
        while (tries < _controls.Count)
        {
            next = next + direction;
            if (next < 0)
                next = _controls.Count - 1;
            if (next >= _controls.Count)
                next = 0;
            if (_controls[next].focusable == 1)
            {
                var btn = (Button)_controls[next];
                btn.focused = 1;
                _focusedIndex = next;
                return;
            }
            tries++;
        }

        if (current >= 0 && _controls[current].focusable == 1)
        {
            var btn = (Button)_controls[current];
            btn.focused = 1;
        }
    }

    public void InitFocus()
    {
        int i = 0;
        while (i < _controls.Count)
        {
            if (_controls[i].focusable == 1)
            {
                var btn = (Button)_controls[i];
                btn.focused = 1;
                _focusedIndex = i;
                return;
            }
            i++;
        }
    }
}