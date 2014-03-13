using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Mail;

using Autodesk.Max;

namespace AutodeskMaxDllDemo
{
    /// <summary>
    /// Emails a report with the list of scene objects.
    /// </summary>
    public class CuiDemoGMailScene : CuiDemoBase
    {
        GMailPasswordForm form = new GMailPasswordForm();

        public override void InternalExecute()
        {
            if (!form.GetUserInfo())
                return;

            string address = form.UserName + "@gmail.com";
            string password = form.Password;

            MailMessage msg = new MailMessage();
            msg.From = new MailAddress(address);
            msg.Subject = "This is a 3ds Max node report";
            msg.To.Add(msg.From);
            msg.Body = NodeReport.GetReport();

            SmtpClient client = new SmtpClient("smtp.gmail.com", 587);
            client.EnableSsl = true;
            client.UseDefaultCredentials = false;
            client.Credentials = new NetworkCredential(address, password);
            client.Send(msg);
        }

        public override string InternalActionText
        {
            get { return "Emails a report"; }
        }
    }
}
