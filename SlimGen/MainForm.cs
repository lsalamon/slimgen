using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using SlimGen.Properties;

namespace SlimGen
{
    public partial class MainForm : Form
    {
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        static extern IntPtr SendMessage(IntPtr hWnd, UInt32 Msg, IntPtr wParam, IntPtr lParam);

        const int BM_SETIMAGE = 0x00F7;

        public MainForm()
        {
            InitializeComponent();

            SetButtonImage(templatesButton, Resources.templates);
            SetButtonImage(createXmlButton, Resources.create);
            SetButtonImage(compileButton, Resources.compile);
            SetButtonImage(editXmlButton, Resources.edit);
            SetButtonImage(ngenButton, Resources.ngen);
            SetButtonImage(testButton, Resources.test);
        }

        public static void SetButtonImage(Button button, Bitmap image)
        {
            SendMessage(button.Handle, BM_SETIMAGE, new IntPtr(1), image.GetHicon());
        }

        private void templatesButton_Click(object sender, EventArgs e)
        {

        }

        private void createXmlButton_Click(object sender, EventArgs e)
        {

        }

        private void compileButton_Click(object sender, EventArgs e)
        {

        }

        private void editXmlButton_Click(object sender, EventArgs e)
        {

        }

        private void ngenButton_Click(object sender, EventArgs e)
        {

        }

        private void testButton_Click(object sender, EventArgs e)
        {

        }
    }
}
