using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Autodesk.Max;
using Autodesk.Max.Plugins;

namespace AutodeskMaxDllDemo
{
    /// <summary>
    /// Creates and shows a teapot in the viewport.
    /// </summary>
    public class CuiDemoTeapot : CuiDemoBase
    {
        public override void InternalExecute()
        {
            try
            {
                IGlobal global = Autodesk.Max.GlobalInterface.Instance;  //note that global will be an instance of an abstract class.
                var i = global.COREInterface13;
                IClass_ID cid = global.Class_ID.Create((uint)BuiltInClassIDA.TEAPOT_CLASS_ID, (uint)BuiltInClassIDB.TEAPOT_CLASS_ID);
                object obj = i.CreateInstance(SClass_ID.Geomobject, cid as IClass_ID);
                if (obj == null) throw new Exception("Failed to create a sphere!");
                IINode n = global.COREInterface.CreateObjectNode((IObject)obj);
                IObject iobj = (IObject)obj;
                IIParamArray ps = iobj.ParamBlock;
                ps.SetValue(0, global.COREInterface.Time, 20.0f);
                n.Move(global.COREInterface.Time, global.Matrix3.Create(), global.Point3.Create(20, 20, 0), true, true, 0, true);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("Creating teapot failed: " + ex.Message);
            }
        }

        public override string InternalActionText
        {
            get { return "Show teapot";  }
        }
    }
}
