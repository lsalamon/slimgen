namespace Builder
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
			this.label1 = new System.Windows.Forms.Label();
			this.assemblyBox = new System.Windows.Forms.TextBox();
			this.browseAssembliesButton = new System.Windows.Forms.Button();
			this.methodsBox = new System.Windows.Forms.TreeView();
			this.treeImages = new System.Windows.Forms.ImageList(this.components);
			this.directoryBox = new System.Windows.Forms.TextBox();
			this.directoryBrowseButton = new System.Windows.Forms.Button();
			this.label3 = new System.Windows.Forms.Label();
			this.generateButton = new System.Windows.Forms.Button();
			this.clearButton = new System.Windows.Forms.Button();
			this.folderDialog = new System.Windows.Forms.FolderBrowserDialog();
			this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 15);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(54, 13);
			this.label1.TabIndex = 0;
			this.label1.Text = "Assembly:";
			// 
			// assemblyBox
			// 
			this.assemblyBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.assemblyBox.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
			this.assemblyBox.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
			this.assemblyBox.Location = new System.Drawing.Point(72, 13);
			this.assemblyBox.Name = "assemblyBox";
			this.assemblyBox.Size = new System.Drawing.Size(230, 20);
			this.assemblyBox.TabIndex = 1;
			this.assemblyBox.TextChanged += new System.EventHandler(this.assemblyBox_TextChanged);
			// 
			// browseAssembliesButton
			// 
			this.browseAssembliesButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.browseAssembliesButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.browseAssembliesButton.Location = new System.Drawing.Point(308, 10);
			this.browseAssembliesButton.Name = "browseAssembliesButton";
			this.browseAssembliesButton.Size = new System.Drawing.Size(32, 23);
			this.browseAssembliesButton.TabIndex = 2;
			this.browseAssembliesButton.Text = "...";
			this.browseAssembliesButton.UseVisualStyleBackColor = true;
			this.browseAssembliesButton.Click += new System.EventHandler(this.browseAssembliesButton_Click);
			// 
			// methodsBox
			// 
			this.methodsBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.methodsBox.CheckBoxes = true;
			this.methodsBox.ImageIndex = 0;
			this.methodsBox.ImageList = this.treeImages;
			this.methodsBox.Location = new System.Drawing.Point(12, 64);
			this.methodsBox.Name = "methodsBox";
			this.methodsBox.SelectedImageIndex = 0;
			this.methodsBox.Size = new System.Drawing.Size(328, 263);
			this.methodsBox.TabIndex = 3;
			this.methodsBox.AfterCheck += new System.Windows.Forms.TreeViewEventHandler(this.methodsBox_AfterCheck);
			// 
			// treeImages
			// 
			this.treeImages.ColorDepth = System.Windows.Forms.ColorDepth.Depth24Bit;
			this.treeImages.ImageSize = new System.Drawing.Size(16, 16);
			this.treeImages.TransparentColor = System.Drawing.Color.Fuchsia;
			// 
			// directoryBox
			// 
			this.directoryBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.directoryBox.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
			this.directoryBox.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystemDirectories;
			this.directoryBox.Location = new System.Drawing.Point(105, 38);
			this.directoryBox.Name = "directoryBox";
			this.directoryBox.Size = new System.Drawing.Size(197, 20);
			this.directoryBox.TabIndex = 5;
			this.directoryBox.TextChanged += new System.EventHandler(this.directoryBox_TextChanged);
			// 
			// directoryBrowseButton
			// 
			this.directoryBrowseButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.directoryBrowseButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.directoryBrowseButton.Location = new System.Drawing.Point(308, 36);
			this.directoryBrowseButton.Name = "directoryBrowseButton";
			this.directoryBrowseButton.Size = new System.Drawing.Size(32, 23);
			this.directoryBrowseButton.TabIndex = 6;
			this.directoryBrowseButton.Text = "...";
			this.directoryBrowseButton.UseVisualStyleBackColor = true;
			this.directoryBrowseButton.Click += new System.EventHandler(this.directoryBrowseButton_Click);
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(12, 41);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(87, 13);
			this.label3.TabIndex = 7;
			this.label3.Text = "Output Directory:";
			// 
			// generateButton
			// 
			this.generateButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.generateButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.generateButton.Location = new System.Drawing.Point(204, 333);
			this.generateButton.Name = "generateButton";
			this.generateButton.Size = new System.Drawing.Size(137, 23);
			this.generateButton.TabIndex = 8;
			this.generateButton.Text = "Generate Templates";
			this.generateButton.UseVisualStyleBackColor = true;
			this.generateButton.Click += new System.EventHandler(this.generateButton_Click);
			// 
			// clearButton
			// 
			this.clearButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.clearButton.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.clearButton.Location = new System.Drawing.Point(12, 333);
			this.clearButton.Name = "clearButton";
			this.clearButton.Size = new System.Drawing.Size(75, 23);
			this.clearButton.TabIndex = 9;
			this.clearButton.Text = "Clear";
			this.clearButton.UseVisualStyleBackColor = true;
			this.clearButton.Click += new System.EventHandler(this.clearButton_Click);
			// 
			// folderDialog
			// 
			this.folderDialog.Description = "Select output directory for generated files.";
			// 
			// openFileDialog
			// 
			this.openFileDialog.DefaultExt = "*.dll";
			this.openFileDialog.Filter = "Assemblies|*.exe;*.dll|All files|*.*";
			this.openFileDialog.Title = "Open Assembly";
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(353, 367);
			this.Controls.Add(this.clearButton);
			this.Controls.Add(this.generateButton);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.directoryBrowseButton);
			this.Controls.Add(this.directoryBox);
			this.Controls.Add(this.methodsBox);
			this.Controls.Add(this.browseAssembliesButton);
			this.Controls.Add(this.assemblyBox);
			this.Controls.Add(this.label1);
			this.Name = "MainForm";
			this.Text = "SlimGen Builder";
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox assemblyBox;
        private System.Windows.Forms.Button browseAssembliesButton;
        private System.Windows.Forms.TreeView methodsBox;
        private System.Windows.Forms.TextBox directoryBox;
        private System.Windows.Forms.Button directoryBrowseButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button generateButton;
        private System.Windows.Forms.Button clearButton;
        private System.Windows.Forms.ImageList treeImages;
        private System.Windows.Forms.FolderBrowserDialog folderDialog;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
    }
}

