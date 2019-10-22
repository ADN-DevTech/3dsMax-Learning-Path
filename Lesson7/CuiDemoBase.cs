using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Windows.Forms;

using Autodesk.Max;
using UiViewModels.Actions;

namespace AutodeskMaxDllDemo
{

    /// <summary>
    /// This exists for one purpose: to avoid having to declare ActionText and Category over and over again 
    /// in all of the MaxSharp demos. 
    /// </summary>
    public abstract class CuiDemoBase : CuiActionCommandAdapter
    {
        public override string ActionText
        {
            get { return InternalActionText; }
        }

        public override string Category
        {
            get { return InternalCategory; }
        }

        public override string InternalCategory
        {
            get { return "Autodesk.Max.Dll Demo"; }
        }

        public override void Execute(object parameter)
        {
            try
            {
                InternalExecute();
            }
            catch (Exception e)
            {
                MessageBox.Show("Uncaught exception occurred: " + e.Message);
            }
        }

        public abstract void InternalExecute();
    }
}
