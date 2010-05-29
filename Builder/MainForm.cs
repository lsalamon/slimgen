using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Builder.Properties;
using System.IO;
using System.Reflection;
using SlimGen;

namespace Builder {
	public partial class MainForm : Form {
		[DllImport("uxtheme", CharSet = CharSet.Unicode)]
		public extern static int SetWindowTheme(IntPtr hWnd, string textSubAppName, string textSubIdList);

		[DllImport("user32.dll", CharSet = CharSet.Unicode)]
		static extern IntPtr SendMessage(HandleRef hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

		public MainForm() {
			InitializeComponent();

			Font = SystemFonts.DefaultFont;

			SetWindowTheme(methodsBox.Handle, "explorer", null);
			SendMessage(new HandleRef(methodsBox, methodsBox.Handle), 0x1100 + 44, new IntPtr(0x0040), new IntPtr(0x0040));
			SendMessage(new HandleRef(methodsBox, methodsBox.Handle), 0x1100 + 44, new IntPtr(0x0020), new IntPtr(0x0020));

			treeImages.Images.Add("assembly", Resources.assembly);
			treeImages.Images.Add("namespace", Resources._namespace);
			treeImages.Images.Add("class", Resources._class);
			treeImages.Images.Add("method", Resources.method);

			generateButton.Enabled = false;
		}

		public void Generate() {
			if (!Directory.Exists(directoryBox.Text))
				Directory.CreateDirectory(directoryBox.Text);

			var methods = new List<MethodBase>();
			foreach (var node in methodsBox.Nodes)
				ProcessNode(node as TreeNode, methods);

			var injector = new Injector("debugger.exe");
			if (!injector.GenerateTemplates(methods, directoryBox.Text))
				MessageBox.Show(injector.Errors);
		}

		static void ProcessNode(TreeNode node, List<MethodBase> methods) {
			if (node.Checked && node.Tag != null)
				methods.Add(node.Tag as MethodBase);

			foreach (var child in node.Nodes)
				ProcessNode(child as TreeNode, methods);
		}

		void FillMethods(string assemblyPath) {
			var assembly = Assembly.LoadFile(assemblyPath);
			var node = methodsBox.Nodes.Add(Path.GetFileName(assemblyPath));

			foreach (var type in assembly.GetTypes()) {
				foreach (var method in type.GetMethods(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static)) {
					var name = method.DeclaringType.FullName + "." + method.Name;
					var index = name.IndexOf('.');
					while (index != -1) {
						var piece = name.Substring(0, index);
						name = name.Substring(index + 1);

						node = node.Nodes.ContainsKey(piece) ? node.Nodes[piece] : node.Nodes.Add(piece, piece, "namespace", "namespace");

						index = name.IndexOf('.');
					}

					node.ImageKey = "class";
					node.SelectedImageKey = "class";

					var newNode = node.Nodes.Add(MethodReplacement.GetMethodSignature(method), name, "method", "method");
					newNode.Tag = method;

					var attributes = method.GetCustomAttributes(typeof(ReplaceMethodAttribute), false);
					if (attributes.Length != 0)
						newNode.Checked = true;

					var parent = newNode.Parent;
					while (parent != null) {
						if (newNode.Checked)
							parent.Checked = true;
						parent = parent.Parent;
					}

					node = methodsBox.Nodes[0];
				}
			}
		}

		void clearButton_Click(object sender, EventArgs e) {
			methodsBox.Nodes.Clear();
			assemblyBox.Clear();
			directoryBox.Clear();
		}

		void generateButton_Click(object sender, EventArgs e) {
			Generate();
		}

		void browseAssembliesButton_Click(object sender, EventArgs e) {
			if (openFileDialog.ShowDialog(this) == DialogResult.OK)
				assemblyBox.Text = openFileDialog.FileName;
		}

		void directoryBrowseButton_Click(object sender, EventArgs e) {
			if (folderDialog.ShowDialog(this) == DialogResult.OK)
				directoryBox.Text = folderDialog.SelectedPath;
		}

		void assemblyBox_TextChanged(object sender, EventArgs e) {
			generateButton.Enabled = assemblyBox.Text.Length != 0 && directoryBox.Text.Length != 0;

			if (assemblyBox.Text.Length != 0 && File.Exists(assemblyBox.Text))
				FillMethods(assemblyBox.Text);
		}

		void directoryBox_TextChanged(object sender, EventArgs e) {
			generateButton.Enabled = assemblyBox.Text.Length != 0 && directoryBox.Text.Length != 0;
		}

		void methodsBox_AfterCheck(object sender, TreeViewEventArgs e) {
			foreach (var child in e.Node.Nodes) {
				var childNode = child as TreeNode;
				childNode.Checked = e.Node.Checked;
			}
		}
	}
}
