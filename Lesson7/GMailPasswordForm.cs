using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MaxCustomControls;

namespace AutodeskMaxDllDemo
{
    public partial class GMailPasswordForm : MaxCustomControls.MaxForm
    {
        public GMailPasswordForm()
        {
            InitializeComponent();
        }

        public string UserName
        {
            get { return userNameTextBox.Text; }
        }

        public string Password
        {
            get { return passwordTextBox.Text; }
        }

        public bool GetUserInfo()
        {
            return ShowDialog() == DialogResult.OK; 
        }
    }
}
