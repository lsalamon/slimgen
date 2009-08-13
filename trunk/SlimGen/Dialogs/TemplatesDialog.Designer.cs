namespace SlimGen.Dialogs
{
    partial class TemplatesDialog
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
            this.assemblyBox = new System.Windows.Forms.ComboBox();
            this.groupBox = new System.Windows.Forms.GroupBox();
            this.outputBox = new System.Windows.Forms.ComboBox();
            this.platformBox = new System.Windows.Forms.ComboBox();
            this.cancelButton = new System.Windows.Forms.Button();
            this.okButton = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.folderDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.groupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // assemblyBox
            // 
            this.assemblyBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.assemblyBox.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.assemblyBox.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
            this.assemblyBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.assemblyBox.FormattingEnabled = true;
            this.assemblyBox.Items.AddRange(new object[] {
            "Browse..."});
            this.assemblyBox.Location = new System.Drawing.Point(6, 22);
            this.assemblyBox.Name = "assemblyBox";
            this.assemblyBox.Size = new System.Drawing.Size(294, 23);
            this.assemblyBox.TabIndex = 1;
            this.assemblyBox.SelectedIndexChanged += new System.EventHandler(this.assemblyBox_SelectedIndexChanged);
            this.assemblyBox.TextUpdate += new System.EventHandler(this.assemblyBox_TextUpdate);
            // 
            // groupBox
            // 
            this.groupBox.Controls.Add(this.outputBox);
            this.groupBox.Controls.Add(this.platformBox);
            this.groupBox.Controls.Add(this.assemblyBox);
            this.groupBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox.Location = new System.Drawing.Point(12, 12);
            this.groupBox.Name = "groupBox";
            this.groupBox.Size = new System.Drawing.Size(310, 119);
            this.groupBox.TabIndex = 4;
            this.groupBox.TabStop = false;
            this.groupBox.Text = "Options";
            // 
            // outputBox
            // 
            this.outputBox.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Suggest;
            this.outputBox.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystemDirectories;
            this.outputBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.outputBox.FormattingEnabled = true;
            this.outputBox.Items.AddRange(new object[] {
            "Browse..."});
            this.outputBox.Location = new System.Drawing.Point(6, 51);
            this.outputBox.Name = "outputBox";
            this.outputBox.Size = new System.Drawing.Size(294, 23);
            this.outputBox.TabIndex = 2;
            this.outputBox.SelectedIndexChanged += new System.EventHandler(this.outputBox_SelectedIndexChanged);
            this.outputBox.TextUpdate += new System.EventHandler(this.outputBox_TextUpdate);
            // 
            // platformBox
            // 
            this.platformBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.platformBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.platformBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.platformBox.FormattingEnabled = true;
            this.platformBox.Items.AddRange(new object[] {
            "Both x86 and x64 templates",
            "Only x86 templates",
            "Only x64 templates"});
            this.platformBox.Location = new System.Drawing.Point(6, 80);
            this.platformBox.Name = "platformBox";
            this.platformBox.Size = new System.Drawing.Size(294, 23);
            this.platformBox.TabIndex = 1;
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(248, 137);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 25);
            this.cancelButton.TabIndex = 5;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            // 
            // okButton
            // 
            this.okButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.okButton.Enabled = false;
            this.okButton.Location = new System.Drawing.Point(167, 137);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 25);
            this.okButton.TabIndex = 6;
            this.okButton.Text = "Generate";
            this.okButton.UseVisualStyleBackColor = true;
            // 
            // openFileDialog
            // 
            this.openFileDialog.DefaultExt = "dll";
            this.openFileDialog.Filter = "Assembly files (*.exe, *.dll)|*.exe;*.dll|All files (*.*)|*.*";
            this.openFileDialog.Title = "Select Assembly";
            // 
            // folderDialog
            // 
            this.folderDialog.Description = "Output Directory";
            // 
            // TemplatesDialog
            // 
            this.AcceptButton = this.okButton;
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(335, 173);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.groupBox);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TemplatesDialog";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Generate Templates";
            this.groupBox.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox assemblyBox;
        private System.Windows.Forms.GroupBox groupBox;
        private System.Windows.Forms.ComboBox platformBox;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.ComboBox outputBox;
        private System.Windows.Forms.FolderBrowserDialog folderDialog;

    }
}