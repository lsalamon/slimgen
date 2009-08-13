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
            this.groupBox = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.templatesButton = new System.Windows.Forms.Button();
            this.testButton = new System.Windows.Forms.Button();
            this.editXmlButton = new System.Windows.Forms.Button();
            this.compileButton = new System.Windows.Forms.Button();
            this.ngenButton = new System.Windows.Forms.Button();
            this.createXmlButton = new System.Windows.Forms.Button();
            this.groupBox.SuspendLayout();
            this.tableLayoutPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox
            // 
            this.groupBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox.Controls.Add(this.tableLayoutPanel);
            this.groupBox.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox.Location = new System.Drawing.Point(10, 12);
            this.groupBox.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox.Name = "groupBox";
            this.groupBox.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox.Size = new System.Drawing.Size(531, 357);
            this.groupBox.TabIndex = 0;
            this.groupBox.TabStop = false;
            this.groupBox.Text = "What would you like to do?";
            // 
            // tableLayoutPanel
            // 
            this.tableLayoutPanel.ColumnCount = 2;
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel.Controls.Add(this.templatesButton, 0, 0);
            this.tableLayoutPanel.Controls.Add(this.testButton, 1, 2);
            this.tableLayoutPanel.Controls.Add(this.editXmlButton, 1, 1);
            this.tableLayoutPanel.Controls.Add(this.compileButton, 0, 1);
            this.tableLayoutPanel.Controls.Add(this.ngenButton, 0, 2);
            this.tableLayoutPanel.Controls.Add(this.createXmlButton, 1, 0);
            this.tableLayoutPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel.Location = new System.Drawing.Point(2, 18);
            this.tableLayoutPanel.Name = "tableLayoutPanel";
            this.tableLayoutPanel.RowCount = 3;
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33555F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33223F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33223F));
            this.tableLayoutPanel.Size = new System.Drawing.Size(527, 337);
            this.tableLayoutPanel.TabIndex = 6;
            // 
            // templatesButton
            // 
            this.templatesButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.templatesButton.Image = global::SlimGen.Properties.Resources.templates;
            this.templatesButton.Location = new System.Drawing.Point(3, 3);
            this.templatesButton.Name = "templatesButton";
            this.templatesButton.Size = new System.Drawing.Size(257, 106);
            this.templatesButton.TabIndex = 0;
            this.templatesButton.Text = "Generate Templates";
            this.templatesButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.templatesButton.UseVisualStyleBackColor = true;
            this.templatesButton.Click += new System.EventHandler(this.templatesButton_Click);
            // 
            // testButton
            // 
            this.testButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.testButton.Image = global::SlimGen.Properties.Resources.test;
            this.testButton.Location = new System.Drawing.Point(266, 227);
            this.testButton.Name = "testButton";
            this.testButton.Size = new System.Drawing.Size(258, 107);
            this.testButton.TabIndex = 4;
            this.testButton.Text = "Performance Test";
            this.testButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.testButton.UseVisualStyleBackColor = true;
            // 
            // editXmlButton
            // 
            this.editXmlButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.editXmlButton.Image = global::SlimGen.Properties.Resources.edit;
            this.editXmlButton.Location = new System.Drawing.Point(266, 115);
            this.editXmlButton.Name = "editXmlButton";
            this.editXmlButton.Size = new System.Drawing.Size(258, 106);
            this.editXmlButton.TabIndex = 5;
            this.editXmlButton.Text = "Edit XML Configuration";
            this.editXmlButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.editXmlButton.UseVisualStyleBackColor = true;
            // 
            // compileButton
            // 
            this.compileButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.compileButton.Image = global::SlimGen.Properties.Resources.compile;
            this.compileButton.Location = new System.Drawing.Point(3, 115);
            this.compileButton.Name = "compileButton";
            this.compileButton.Size = new System.Drawing.Size(257, 106);
            this.compileButton.TabIndex = 1;
            this.compileButton.Text = "Compile To SGen";
            this.compileButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.compileButton.UseVisualStyleBackColor = true;
            // 
            // ngenButton
            // 
            this.ngenButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ngenButton.Image = global::SlimGen.Properties.Resources.ngen;
            this.ngenButton.Location = new System.Drawing.Point(3, 227);
            this.ngenButton.Name = "ngenButton";
            this.ngenButton.Size = new System.Drawing.Size(257, 107);
            this.ngenButton.TabIndex = 2;
            this.ngenButton.Text = "NGEN an Assembly";
            this.ngenButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.ngenButton.UseVisualStyleBackColor = true;
            // 
            // createXmlButton
            // 
            this.createXmlButton.Dock = System.Windows.Forms.DockStyle.Fill;
            this.createXmlButton.Image = global::SlimGen.Properties.Resources.create;
            this.createXmlButton.Location = new System.Drawing.Point(266, 3);
            this.createXmlButton.Name = "createXmlButton";
            this.createXmlButton.Size = new System.Drawing.Size(258, 106);
            this.createXmlButton.TabIndex = 3;
            this.createXmlButton.Text = "Create XML Configuration";
            this.createXmlButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.createXmlButton.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(553, 378);
            this.Controls.Add(this.groupBox);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(2, 3, 2, 3);
            this.Name = "MainForm";
            this.Text = "SlimGen";
            this.groupBox.ResumeLayout(false);
            this.tableLayoutPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox;
        private System.Windows.Forms.Button editXmlButton;
        private System.Windows.Forms.Button testButton;
        private System.Windows.Forms.Button createXmlButton;
        private System.Windows.Forms.Button ngenButton;
        private System.Windows.Forms.Button compileButton;
        private System.Windows.Forms.Button templatesButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel;
    }
}

