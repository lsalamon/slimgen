namespace SlimGen
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.saveMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.assemblyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.refreshMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.installMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.uninstallMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.compileMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.performanceTestMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.systemInformationMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip = new System.Windows.Forms.ToolStrip();
            this.newToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.openToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.saveToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator7 = new System.Windows.Forms.ToolStripSeparator();
            this.platformBox = new System.Windows.Forms.ToolStripComboBox();
            this.viewStyleButton = new System.Windows.Forms.ToolStripSplitButton();
            this.largeIconsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.smallIconsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.detailsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.refreshToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.compileToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.testToolStripButton = new System.Windows.Forms.ToolStripButton();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.splitContainer = new System.Windows.Forms.SplitContainer();
            this.methodView = new System.Windows.Forms.TreeView();
            this.treeImages = new System.Windows.Forms.ImageList(this.components);
            this.listView1 = new System.Windows.Forms.ListView();
            this.openAssemblyDialog = new System.Windows.Forms.OpenFileDialog();
            this.openProjectDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveProjectDialog = new System.Windows.Forms.SaveFileDialog();
            this.menuStrip.SuspendLayout();
            this.toolStrip.SuspendLayout();
            this.splitContainer.Panel1.SuspendLayout();
            this.splitContainer.Panel2.SuspendLayout();
            this.splitContainer.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.assemblyToolStripMenuItem,
            this.toolsToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(622, 28);
            this.menuStrip.TabIndex = 0;
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newMenuItem,
            this.openMenuItem,
            this.closeMenuItem,
            this.toolStripSeparator,
            this.saveMenuItem,
            this.saveAsMenuItem,
            this.toolStripSeparator1,
            this.exitMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newMenuItem
            // 
            this.newMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("newMenuItem.Image")));
            this.newMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.newMenuItem.Name = "newMenuItem";
            this.newMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newMenuItem.Size = new System.Drawing.Size(217, 24);
            this.newMenuItem.Text = "&New Project";
            this.newMenuItem.Click += new System.EventHandler(this.newMenuItem_Click);
            // 
            // openMenuItem
            // 
            this.openMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("openMenuItem.Image")));
            this.openMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.openMenuItem.Name = "openMenuItem";
            this.openMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openMenuItem.Size = new System.Drawing.Size(217, 24);
            this.openMenuItem.Text = "&Open Project";
            this.openMenuItem.Click += new System.EventHandler(this.openMenuItem_Click);
            // 
            // closeMenuItem
            // 
            this.closeMenuItem.Name = "closeMenuItem";
            this.closeMenuItem.Size = new System.Drawing.Size(217, 24);
            this.closeMenuItem.Text = "&Close";
            this.closeMenuItem.Click += new System.EventHandler(this.closeMenuItem_Click);
            // 
            // toolStripSeparator
            // 
            this.toolStripSeparator.Name = "toolStripSeparator";
            this.toolStripSeparator.Size = new System.Drawing.Size(214, 6);
            // 
            // saveMenuItem
            // 
            this.saveMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("saveMenuItem.Image")));
            this.saveMenuItem.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.saveMenuItem.Name = "saveMenuItem";
            this.saveMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveMenuItem.Size = new System.Drawing.Size(217, 24);
            this.saveMenuItem.Text = "&Save";
            this.saveMenuItem.Click += new System.EventHandler(this.saveMenuItem_Click);
            // 
            // saveAsMenuItem
            // 
            this.saveAsMenuItem.Name = "saveAsMenuItem";
            this.saveAsMenuItem.Size = new System.Drawing.Size(217, 24);
            this.saveAsMenuItem.Text = "Save &As";
            this.saveAsMenuItem.Click += new System.EventHandler(this.saveAsMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(214, 6);
            // 
            // exitMenuItem
            // 
            this.exitMenuItem.Name = "exitMenuItem";
            this.exitMenuItem.Size = new System.Drawing.Size(217, 24);
            this.exitMenuItem.Text = "E&xit";
            this.exitMenuItem.Click += new System.EventHandler(this.exitMenuItem_Click);
            // 
            // assemblyToolStripMenuItem
            // 
            this.assemblyToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.refreshMenuItem,
            this.toolStripSeparator2,
            this.installMenuItem,
            this.uninstallMenuItem});
            this.assemblyToolStripMenuItem.Name = "assemblyToolStripMenuItem";
            this.assemblyToolStripMenuItem.Size = new System.Drawing.Size(84, 24);
            this.assemblyToolStripMenuItem.Text = "&Assembly";
            // 
            // refreshMenuItem
            // 
            this.refreshMenuItem.Image = global::SlimGen.Properties.Resources.Refresh;
            this.refreshMenuItem.Name = "refreshMenuItem";
            this.refreshMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.R)));
            this.refreshMenuItem.Size = new System.Drawing.Size(178, 24);
            this.refreshMenuItem.Text = "&Refresh";
            this.refreshMenuItem.Click += new System.EventHandler(this.refreshMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(175, 6);
            // 
            // installMenuItem
            // 
            this.installMenuItem.Name = "installMenuItem";
            this.installMenuItem.Size = new System.Drawing.Size(178, 24);
            this.installMenuItem.Text = "NGen &Install";
            this.installMenuItem.Click += new System.EventHandler(this.installMenuItem_Click);
            // 
            // uninstallMenuItem
            // 
            this.uninstallMenuItem.Name = "uninstallMenuItem";
            this.uninstallMenuItem.Size = new System.Drawing.Size(178, 24);
            this.uninstallMenuItem.Text = "NGen &Uninstall";
            this.uninstallMenuItem.Click += new System.EventHandler(this.uninstallMenuItem_Click);
            // 
            // toolsToolStripMenuItem
            // 
            this.toolsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.compileMenuItem,
            this.performanceTestMenuItem,
            this.toolStripSeparator3,
            this.systemInformationMenuItem});
            this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
            this.toolsToolStripMenuItem.Size = new System.Drawing.Size(57, 24);
            this.toolsToolStripMenuItem.Text = "&Tools";
            // 
            // compileMenuItem
            // 
            this.compileMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("compileMenuItem.Image")));
            this.compileMenuItem.ImageTransparentColor = System.Drawing.Color.Fuchsia;
            this.compileMenuItem.Name = "compileMenuItem";
            this.compileMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F5;
            this.compileMenuItem.Size = new System.Drawing.Size(217, 24);
            this.compileMenuItem.Text = "&Compile";
            this.compileMenuItem.Click += new System.EventHandler(this.compileMenuItem_Click);
            // 
            // performanceTestMenuItem
            // 
            this.performanceTestMenuItem.Image = global::SlimGen.Properties.Resources.Test;
            this.performanceTestMenuItem.Name = "performanceTestMenuItem";
            this.performanceTestMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F6;
            this.performanceTestMenuItem.Size = new System.Drawing.Size(217, 24);
            this.performanceTestMenuItem.Text = "Performance &Test";
            this.performanceTestMenuItem.Click += new System.EventHandler(this.performanceTestMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(214, 6);
            // 
            // systemInformationMenuItem
            // 
            this.systemInformationMenuItem.Name = "systemInformationMenuItem";
            this.systemInformationMenuItem.Size = new System.Drawing.Size(217, 24);
            this.systemInformationMenuItem.Text = "&System Information";
            this.systemInformationMenuItem.Click += new System.EventHandler(this.systemInformationMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(53, 24);
            this.helpToolStripMenuItem.Text = "&Help";
            // 
            // aboutMenuItem
            // 
            this.aboutMenuItem.Name = "aboutMenuItem";
            this.aboutMenuItem.Size = new System.Drawing.Size(128, 24);
            this.aboutMenuItem.Text = "&About...";
            this.aboutMenuItem.Click += new System.EventHandler(this.aboutMenuItem_Click);
            // 
            // toolStrip
            // 
            this.toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripButton,
            this.openToolStripButton,
            this.saveToolStripButton,
            this.toolStripSeparator7,
            this.platformBox,
            this.viewStyleButton,
            this.refreshToolStripButton,
            this.toolStripSeparator4,
            this.compileToolStripButton,
            this.testToolStripButton});
            this.toolStrip.Location = new System.Drawing.Point(0, 28);
            this.toolStrip.Name = "toolStrip";
            this.toolStrip.Size = new System.Drawing.Size(622, 32);
            this.toolStrip.TabIndex = 1;
            // 
            // newToolStripButton
            // 
            this.newToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.newToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("newToolStripButton.Image")));
            this.newToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.newToolStripButton.Name = "newToolStripButton";
            this.newToolStripButton.Size = new System.Drawing.Size(23, 29);
            this.newToolStripButton.Text = "&New";
            this.newToolStripButton.ToolTipText = "Create a new project";
            this.newToolStripButton.Click += new System.EventHandler(this.newToolStripButton_Click);
            // 
            // openToolStripButton
            // 
            this.openToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.openToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("openToolStripButton.Image")));
            this.openToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.openToolStripButton.Name = "openToolStripButton";
            this.openToolStripButton.Size = new System.Drawing.Size(23, 29);
            this.openToolStripButton.Text = "&Open";
            this.openToolStripButton.ToolTipText = "Open an existing project";
            this.openToolStripButton.Click += new System.EventHandler(this.openToolStripButton_Click);
            // 
            // saveToolStripButton
            // 
            this.saveToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.saveToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("saveToolStripButton.Image")));
            this.saveToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.saveToolStripButton.Name = "saveToolStripButton";
            this.saveToolStripButton.Size = new System.Drawing.Size(23, 29);
            this.saveToolStripButton.Text = "&Save";
            this.saveToolStripButton.ToolTipText = "Save changes to the project";
            this.saveToolStripButton.Click += new System.EventHandler(this.saveToolStripButton_Click);
            // 
            // toolStripSeparator7
            // 
            this.toolStripSeparator7.Name = "toolStripSeparator7";
            this.toolStripSeparator7.Size = new System.Drawing.Size(6, 32);
            // 
            // platformBox
            // 
            this.platformBox.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.platformBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.platformBox.DropDownWidth = 32;
            this.platformBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.platformBox.Items.AddRange(new object[] {
            "x86",
            "x64"});
            this.platformBox.Margin = new System.Windows.Forms.Padding(1, 2, 1, 2);
            this.platformBox.Name = "platformBox";
            this.platformBox.Size = new System.Drawing.Size(75, 28);
            // 
            // viewStyleButton
            // 
            this.viewStyleButton.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.viewStyleButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.viewStyleButton.DropDownButtonWidth = 18;
            this.viewStyleButton.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.largeIconsMenuItem,
            this.smallIconsMenuItem,
            this.listMenuItem,
            this.detailsMenuItem});
            this.viewStyleButton.Image = global::SlimGen.Properties.Resources.LargeIcons;
            this.viewStyleButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.viewStyleButton.Margin = new System.Windows.Forms.Padding(0, 1, 10, 2);
            this.viewStyleButton.Name = "viewStyleButton";
            this.viewStyleButton.Size = new System.Drawing.Size(39, 29);
            // 
            // largeIconsMenuItem
            // 
            this.largeIconsMenuItem.Image = global::SlimGen.Properties.Resources.LargeIcons;
            this.largeIconsMenuItem.Name = "largeIconsMenuItem";
            this.largeIconsMenuItem.Size = new System.Drawing.Size(153, 24);
            this.largeIconsMenuItem.Text = "Large Icons";
            // 
            // smallIconsMenuItem
            // 
            this.smallIconsMenuItem.Image = global::SlimGen.Properties.Resources.SmallIcons;
            this.smallIconsMenuItem.Name = "smallIconsMenuItem";
            this.smallIconsMenuItem.Size = new System.Drawing.Size(153, 24);
            this.smallIconsMenuItem.Text = "Small Icons";
            // 
            // listMenuItem
            // 
            this.listMenuItem.Image = global::SlimGen.Properties.Resources.List;
            this.listMenuItem.Name = "listMenuItem";
            this.listMenuItem.Size = new System.Drawing.Size(153, 24);
            this.listMenuItem.Text = "List";
            // 
            // detailsMenuItem
            // 
            this.detailsMenuItem.Image = global::SlimGen.Properties.Resources.Details;
            this.detailsMenuItem.Name = "detailsMenuItem";
            this.detailsMenuItem.Size = new System.Drawing.Size(153, 24);
            this.detailsMenuItem.Text = "Details";
            // 
            // refreshToolStripButton
            // 
            this.refreshToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.refreshToolStripButton.Image = global::SlimGen.Properties.Resources.Refresh;
            this.refreshToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.refreshToolStripButton.Name = "refreshToolStripButton";
            this.refreshToolStripButton.Size = new System.Drawing.Size(23, 29);
            this.refreshToolStripButton.ToolTipText = "Refresh the assembly";
            this.refreshToolStripButton.Click += new System.EventHandler(this.refreshToolStripButton_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 32);
            // 
            // compileToolStripButton
            // 
            this.compileToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.compileToolStripButton.Image = global::SlimGen.Properties.Resources.Compile;
            this.compileToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.compileToolStripButton.Name = "compileToolStripButton";
            this.compileToolStripButton.Size = new System.Drawing.Size(23, 29);
            this.compileToolStripButton.Text = "toolStripButton2";
            this.compileToolStripButton.ToolTipText = "Compile to .sgen";
            this.compileToolStripButton.Click += new System.EventHandler(this.compileToolStripButton_Click);
            // 
            // testToolStripButton
            // 
            this.testToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.testToolStripButton.Image = global::SlimGen.Properties.Resources.Test;
            this.testToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.testToolStripButton.Name = "testToolStripButton";
            this.testToolStripButton.Size = new System.Drawing.Size(23, 29);
            this.testToolStripButton.Text = "toolStripButton3";
            this.testToolStripButton.ToolTipText = "Run a performance test";
            this.testToolStripButton.Click += new System.EventHandler(this.testToolStripButton_Click);
            // 
            // statusStrip
            // 
            this.statusStrip.Location = new System.Drawing.Point(0, 413);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(622, 22);
            this.statusStrip.TabIndex = 2;
            // 
            // splitContainer
            // 
            this.splitContainer.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer.Location = new System.Drawing.Point(0, 60);
            this.splitContainer.Name = "splitContainer";
            // 
            // splitContainer.Panel1
            // 
            this.splitContainer.Panel1.Controls.Add(this.methodView);
            // 
            // splitContainer.Panel2
            // 
            this.splitContainer.Panel2.Controls.Add(this.listView1);
            this.splitContainer.Size = new System.Drawing.Size(622, 353);
            this.splitContainer.SplitterDistance = 269;
            this.splitContainer.TabIndex = 3;
            // 
            // methodView
            // 
            this.methodView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.methodView.ImageIndex = 0;
            this.methodView.ImageList = this.treeImages;
            this.methodView.Location = new System.Drawing.Point(0, 0);
            this.methodView.Name = "methodView";
            this.methodView.SelectedImageIndex = 0;
            this.methodView.ShowLines = false;
            this.methodView.Size = new System.Drawing.Size(269, 353);
            this.methodView.TabIndex = 0;
            // 
            // treeImages
            // 
            this.treeImages.ColorDepth = System.Windows.Forms.ColorDepth.Depth24Bit;
            this.treeImages.ImageSize = new System.Drawing.Size(16, 16);
            this.treeImages.TransparentColor = System.Drawing.Color.Fuchsia;
            // 
            // listView1
            // 
            this.listView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView1.Location = new System.Drawing.Point(0, 0);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(349, 353);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            // 
            // openAssemblyDialog
            // 
            this.openAssemblyDialog.DefaultExt = "dll";
            this.openAssemblyDialog.Filter = "Assembly files (*.dll, *.exe)|*.dll;*.exe|All files (*.*)|*.*";
            this.openAssemblyDialog.Title = "Select Assembly";
            // 
            // openProjectDialog
            // 
            this.openProjectDialog.DefaultExt = "sgproj";
            this.openProjectDialog.Filter = "SGen Projects (*.sgproj)|*.sgproj|All files (*.*)|*.*";
            this.openProjectDialog.Title = "Open Project";
            // 
            // saveProjectDialog
            // 
            this.saveProjectDialog.DefaultExt = "sgproj";
            this.saveProjectDialog.Filter = "SGen Projects (*.sgproj)|*.sgproj|All files (*.*)|*.*";
            this.saveProjectDialog.Title = "Save Project";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.ClientSize = new System.Drawing.Size(622, 435);
            this.Controls.Add(this.splitContainer);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.toolStrip);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "MainForm";
            this.Text = "SlimGen";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.toolStrip.ResumeLayout(false);
            this.toolStrip.PerformLayout();
            this.splitContainer.Panel1.ResumeLayout(false);
            this.splitContainer.Panel2.ResumeLayout(false);
            this.splitContainer.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
        private System.Windows.Forms.ToolStripMenuItem saveMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem exitMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip;
        private System.Windows.Forms.ToolStripButton newToolStripButton;
        private System.Windows.Forms.ToolStripButton openToolStripButton;
        private System.Windows.Forms.ToolStripButton saveToolStripButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator7;
        private System.Windows.Forms.ToolStripSplitButton viewStyleButton;
        private System.Windows.Forms.ToolStripComboBox platformBox;
        private System.Windows.Forms.ToolStripMenuItem largeIconsMenuItem;
        private System.Windows.Forms.ToolStripMenuItem smallIconsMenuItem;
        private System.Windows.Forms.ToolStripMenuItem listMenuItem;
        private System.Windows.Forms.ToolStripMenuItem detailsMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.SplitContainer splitContainer;
        private System.Windows.Forms.TreeView methodView;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ToolStripMenuItem closeMenuItem;
        private System.Windows.Forms.ToolStripMenuItem assemblyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem refreshMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem installMenuItem;
        private System.Windows.Forms.ToolStripMenuItem uninstallMenuItem;
        private System.Windows.Forms.ToolStripMenuItem compileMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem performanceTestMenuItem;
        private System.Windows.Forms.ToolStripMenuItem systemInformationMenuItem;
        private System.Windows.Forms.ToolStripButton refreshToolStripButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripButton compileToolStripButton;
        private System.Windows.Forms.ToolStripButton testToolStripButton;
        private System.Windows.Forms.OpenFileDialog openAssemblyDialog;
        private System.Windows.Forms.OpenFileDialog openProjectDialog;
        private System.Windows.Forms.SaveFileDialog saveProjectDialog;
        private System.Windows.Forms.ImageList treeImages;
    }
}

