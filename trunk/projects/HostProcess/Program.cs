using System;
using System.IO;
using System.Reflection;

namespace HostProcess {
	class Program {
		static void Main(string[] args) {
			if (args.Length != 1) {
				Console.WriteLine("Usage: HostProcess.exe <AssemblyName>");
				return;
			}

			var fi = new FileInfo(args[0]);

			var assembly = fi.Exists ? Assembly.LoadFile(fi.FullName) : AppDomain.CurrentDomain.Load(new AssemblyName(args[0]));

			foreach (var type in assembly.GetTypes()) {
				type.GetMethods();
			}

			if (System.Diagnostics.Debugger.IsAttached) {
				System.Diagnostics.Debugger.Break();
			}
		}
	}
}
