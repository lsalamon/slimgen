using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SlimGen.Dialogs
{
    public enum Platform
    {
        None,
        X86,
        X64,
        Both
    }

    public partial class TemplatesDialog : Form
    {
        public string AssemblyPath
        {
            get { return assemblyBox.Text; }
        }

        public string OutputPath
        {
            get { return outputBox.Text; }
        }

        public Platform Platform
        {
            get
            {
                switch (platformBox.SelectedIndex)
                {
                    case 0:
                        return Platform.Both;
                    case 1:
                        return Platform.X86;
                    case 2:
                        return Platform.X64;
                    default:
                        return Platform.None;
                }
            }
        }

        public TemplatesDialog()
        {
            InitializeComponent();
            Font = SystemFonts.DefaultFont;

            platformBox.SelectedIndex = 0;
        }

        void UpdateButtonState()
        {
            okButton.Enabled = !string.IsNullOrEmpty(assemblyBox.Text) && !string.IsNullOrEmpty(outputBox.Text);
        }

        void assemblyBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (assemblyBox.SelectedIndex == assemblyBox.Items.Count - 1)
            {
                if (openFileDialog.ShowDialog(this) == DialogResult.OK)
                {
                    assemblyBox.Items.Insert(0, openFileDialog.FileName);
                    assemblyBox.SelectedIndex = 0;
                }
                else
                    assemblyBox.SelectedText = string.Empty;
            }

            UpdateButtonState();
        }

        void assemblyBox_TextUpdate(object sender, EventArgs e)
        {
            UpdateButtonState();
        }

        void outputBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (outputBox.SelectedIndex == outputBox.Items.Count - 1)
            {
                if (folderDialog.ShowDialog(this) == DialogResult.OK)
                {
                    outputBox.Items.Insert(0, folderDialog.SelectedPath);
                    outputBox.SelectedIndex = 0;
                }
                else
                    outputBox.SelectedText = string.Empty;
            }

            UpdateButtonState();
        }

        void outputBox_TextUpdate(object sender, EventArgs e)
        {
            UpdateButtonState();
        }
    }
}
