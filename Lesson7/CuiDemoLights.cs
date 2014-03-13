using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Autodesk.Max.Plugins;
using Autodesk.Max;

namespace AutodeskMaxDllDemo
{
    /// <summary>
    /// Outputs the list of all lights. 
    /// </summary>
    public class CuiDemoLights : CuiDemoBase
    {
        private String lightNames;
        private int lightNum;
        public override void InternalExecute()
        {
            lightNum = 0;
            lightNames = "";
            IGlobal Global = Autodesk.Max.GlobalInterface.Instance;
            IInterface13 Interface = Global.COREInterface13;
            IINode rootNode = Interface.RootNode;
            ReportLights(rootNode);
            MessageBox.Show(String.Format("{0} light objects found in the scene.\n {1}", lightNum, lightNames));
        }

        private void ReportLights(IINode node)
        {
            if (node.ObjectRef is ILightObject)
            {
                lightNum++;
                lightNames += (node.NodeName + "\n");
            }
            
            for (int i = 0; i < node.NumberOfChildren; i++)
                ReportLights(node.GetChildNode(i));
        }

        public override string InternalActionText
        {
            get { return "Show lights"; }
        }
    }
}
