using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using SlimGen.Properties;
using SlimGen.Dialogs;
using System.Diagnostics;
using System.IO;

namespace SlimGen
{
    public partial class MainForm : Form
    {
        string BinDirectory;

        public MainForm()
        {
            InitializeComponent();
            Font = SystemFonts.DefaultFont;

            BinDirectory = Path.Combine(Application.StartupPath, "bin");
        }

        void templatesButton_Click(object sender, EventArgs e)
        {
            var dialog = new TemplatesDialog();
            if (dialog.ShowDialog(this) == DialogResult.OK)
            {
                var startInfo = new ProcessStartInfo();
                startInfo.UseShellExecute = false;
                startInfo.Arguments = dialog.AssemblyPath;

                if (dialog.Platform == Platform.X86 || dialog.Platform == Platform.Both)
                {
                    startInfo.FileName = Path.Combine(BinDirectory, "tg.exe");
                    Process.Start(startInfo);
                }

                if (dialog.Platform == Platform.X64 || dialog.Platform == Platform.Both)
                {
                    startInfo.FileName = Path.Combine(BinDirectory, "tg64.exe");
                    Process.Start(startInfo);
                }

                foreach (var file in Directory.GetFiles(BinDirectory, "*.asm", SearchOption.TopDirectoryOnly))
                    File.Move(file, Path.Combine(dialog.OutputPath, file));
            }
        }
    }
}
