using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Autodesk.Max;

namespace AutodeskMaxDllDemo
{
    public class CuiDemoPrompt : CuiDemoBase
    {
        public override void InternalExecute()
        {            
            IInterface17 Interface = Autodesk.Max.GlobalInterface.Instance.COREInterface17;
            Interface.PushPrompt("Hello from the AutoDeskMaxDllDemo.dll");
        }

        public override string InternalActionText
        {
            get { return "Send a prompt."; }
        }
    }
}
