using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Autodesk.Max;

namespace AutodeskMaxDllDemo
{
    public class NodeReport
    {
        public static String GetReport()
        {
            NodeReport r = new NodeReport(); 
            return r.Report;
        }

        StringBuilder sb = new StringBuilder();

        public String Report
        {
            get { return sb.ToString(); } 
        }

        public NodeReport()
        {
            IGlobal Global = Autodesk.Max.GlobalInterface.Instance;
            IInterface13 Interface = Global.COREInterface13;
            IINode rootNode = Interface.RootNode;
            GetNodeInfo(rootNode, 0);
        }

        void GetNodeInfo(Autodesk.Max.IINode node, int indent)
        {
            int nChild = node.NumberOfChildren;
            sb.Append(new String(' ', indent));
            sb.Append("Node ");
            sb.Append(node.Name);
            sb.AppendLine();
            for (int i = 0; i < nChild; i++)
                GetNodeInfo(node.GetChildNode(i), indent + 4);
        }
    }
}
