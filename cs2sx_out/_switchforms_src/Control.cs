using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS2SX.SwitchFormsLib;
public abstract class Control
{
    public int x;
    public int y;
    public int width;
    public int height;
    public int visible;
    public int focusable;

    public abstract void Draw();
    public virtual void Update(ulong kDown, ulong kHeld)
    {
    }
}