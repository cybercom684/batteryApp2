using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CS2SX.SwitchFormsLib;
public abstract class SwitchApp
{
    public Form Form;
    public ulong kDown;
    public ulong kHeld;

    public abstract void OnInit();
    public abstract void OnFrame();
    public virtual void OnExit()
    {
    }
}
