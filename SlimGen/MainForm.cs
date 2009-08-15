using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace SlimGen
{
    public partial class MainForm : Form
    {
        [DllImport("uxtheme", CharSet = CharSet.Unicode)]
        public extern static int SetWindowTheme(IntPtr hWnd, string textSubAppName, string textSubIdList);

        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        static extern IntPtr SendMessage(HandleRef hWnd, uint Msg, IntPtr wParam, IntPtr lParam);


        Project project;

        public MainForm()
        {
            InitializeComponent();

            ToolStripManager.Renderer = new ToolStripNativeRenderer(ToolbarTheme.Toolbar);
            Font = SystemFonts.DefaultFont;

            SetWindowTheme(methodView.Handle, "explorer", null);
            SendMessage(new HandleRef(methodView, methodView.Handle), 0x1100 + 44, new IntPtr(0x0040), new IntPtr(0x0040));
            SendMessage(new HandleRef(methodView, methodView.Handle), 0x1100 + 44, new IntPtr(0x0020), new IntPtr(0x0020));

            UpdateInterface();
        }

        void NewProject()
        {
            if (openAssemblyDialog.ShowDialog(this) == DialogResult.OK)
            {
                if (!CloseProject())
                    return;

                project = new Project(openAssemblyDialog.FileName);
                UpdateInterface();
            }
        }

        void OpenProject()
        {
            if (openProjectDialog.ShowDialog(this) == DialogResult.OK)
            {
                if (!CloseProject())
                    return;

                project = Project.FromFile(openProjectDialog.FileName);
                UpdateInterface();
            }
        }

        bool CloseProject()
        {
            if (project != null && project.Changed)
            {
                var result = MessageBox.Show("Do you want to save changes?", "SlimGen", MessageBoxButtons.YesNoCancel);
                if (result == DialogResult.Cancel)
                    return false;
                else if (result == DialogResult.Yes)
                    Save();
            }

            return true;
        }

        void Save()
        {
            if (string.IsNullOrEmpty(project.FileName))
                SaveAs();
            else
                project.Save(project.FileName);
        }

        void SaveAs()
        {
            saveProjectDialog.FileName = project.FileName;
            if (saveProjectDialog.ShowDialog(this) == DialogResult.OK)
                project.Save(saveProjectDialog.FileName);
        }

        void UpdateInterface()
        {
            methodView.Nodes.Clear();

            if (project == null)
            {
                splitContainer.Hide();
                platformBox.Visible = false;
                viewStyleButton.Visible = false;
                closeMenuItem.Enabled = false;
                saveMenuItem.Enabled = false;
                saveAsMenuItem.Enabled = false;
                refreshMenuItem.Enabled = false;
                installMenuItem.Enabled = false;
                uninstallMenuItem.Enabled = false;
                compileMenuItem.Enabled = false;
                performanceTestMenuItem.Enabled = false;
                refreshToolStripButton.Enabled = false;
                compileToolStripButton.Enabled = false;
                testToolStripButton.Enabled = false;

                Text = "SlimGen";
            }
            else
            {
                splitContainer.Show();
                platformBox.Visible = true;
                viewStyleButton.Visible = true;
                closeMenuItem.Enabled = true;
                saveMenuItem.Enabled = true;
                saveAsMenuItem.Enabled = true;
                refreshMenuItem.Enabled = true;
                installMenuItem.Enabled = true;
                uninstallMenuItem.Enabled = true;
                compileMenuItem.Enabled = true;
                performanceTestMenuItem.Enabled = true;
                refreshToolStripButton.Enabled = true;
                compileToolStripButton.Enabled = true;
                testToolStripButton.Enabled = true;

                if (string.IsNullOrEmpty(project.FileName))
                    Text = "SlimGen";
                else
                    Text = Path.GetFileNameWithoutExtension(project.FileName) + " - SlimGen";

                TreeNode node = methodView.Nodes.Add(Path.GetFileName(project.Build.Assembly));
                for (int i = 0; i < project.Build.Platforms[0].Methods.Length; i++)
                {
                    var method = project.Build.Platforms[0].Methods[i];
                    string name = method.Name;

                    int index = name.IndexOf('.');
                    while (index != -1)
                    {
                        string piece = name.Substring(0, index);
                        name = name.Substring(index + 1);

                        if (node.Nodes.ContainsKey(piece))
                            node = node.Nodes[piece];
                        else
                            node = node.Nodes.Add(piece, piece);

                        index = name.IndexOf('.');
                    }

                    var newNode = node.Nodes.Add(name, name);
                    newNode.Tag = i;
                    node = methodView.Nodes[0];
                }
            }
        }

        void RefreshAssembly()
        {
        }

        void InstallAssembly()
        {
        }

        void UninstallAssembly()
        {
        }

        void Compile()
        {
        }

        void Test()
        {
        }

        void SystemInfo()
        {
        }

        void About()
        {
        }

        #region Event Handlers

        void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing && !CloseProject())
                e.Cancel = true;
        }

        void newMenuItem_Click(object sender, EventArgs e)
        {
            NewProject();
        }

        void openMenuItem_Click(object sender, EventArgs e)
        {
            OpenProject();
        }

        void closeMenuItem_Click(object sender, EventArgs e)
        {
            CloseProject();
            UpdateInterface();
        }

        void saveMenuItem_Click(object sender, EventArgs e)
        {
            Save();
        }

        void saveAsMenuItem_Click(object sender, EventArgs e)
        {
            SaveAs();
        }

        void exitMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        void refreshMenuItem_Click(object sender, EventArgs e)
        {
            RefreshAssembly();
        }

        void installMenuItem_Click(object sender, EventArgs e)
        {
            InstallAssembly();
        }

        void uninstallMenuItem_Click(object sender, EventArgs e)
        {
            UninstallAssembly();
        }

        void compileMenuItem_Click(object sender, EventArgs e)
        {
            Compile();
        }

        void performanceTestMenuItem_Click(object sender, EventArgs e)
        {
            Test();
        }

        void systemInformationMenuItem_Click(object sender, EventArgs e)
        {
            SystemInfo();
        }

        void aboutMenuItem_Click(object sender, EventArgs e)
        {
            About();
        }

        void newToolStripButton_Click(object sender, EventArgs e)
        {
            NewProject();
        }

        void openToolStripButton_Click(object sender, EventArgs e)
        {
            OpenProject();
        }

        void saveToolStripButton_Click(object sender, EventArgs e)
        {
            Save();
        }

        void refreshToolStripButton_Click(object sender, EventArgs e)
        {
            SaveAs();
        }

        void compileToolStripButton_Click(object sender, EventArgs e)
        {
            Compile();
        }

        void testToolStripButton_Click(object sender, EventArgs e)
        {
            Test();
        }

        #endregion
    }
}
