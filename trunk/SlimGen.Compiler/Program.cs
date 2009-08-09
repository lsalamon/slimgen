/*
* Copyright (c) 2007-2009 SlimGen Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml.Serialization;

namespace SlimGen.Compiler {
	struct ChunkInfo {
		public string ChunkFileName;
		public InstructionSetSpecifier InstructionSet;
	}

	struct PlatformHeader {
		public PlatformSpecifier Platform;
		public List<MethodHeader> Methods;
	}

	struct MethodHeader {
		public string MethodName;
		public string MethodSignature;
		public List<ChunkInfo> Chunks;
	}

	class Program {
		static void Main(string[] args) {
			if (args.Length != 2) {
				Console.WriteLine("Usage: Comiler <Build File> <Output File>");
				return;
			}

			var buildFileInfo = new FileInfo(args[0]);
			if (!buildFileInfo.Exists) {
				Console.WriteLine("Error: Unable to open build file: '{0}', ensure that it exists and is readable.", buildFileInfo.FullName);
			}

			var serializer = new XmlSerializer(typeof(Build));
			Build buildProject = null;
			try {
				using (Stream bf = buildFileInfo.OpenRead())
					buildProject = (Build)serializer.Deserialize(bf);
			} catch (Exception ex) {
				Console.WriteLine("Error: Invalid configuration file: {0}", ex);
				return;
			}

			var binFiles = new List<PlatformHeader>();

			foreach (var platform in buildProject.Platforms) {
				var currentPlatform = new PlatformHeader() { Platform = platform.Type, Methods = new List<MethodHeader>() };
				binFiles.Add(currentPlatform);
				foreach (var method in platform.Methods) {
					var currentMethod = new MethodHeader() { MethodName = method.Name, Chunks = new List<ChunkInfo>(), MethodSignature = method.Signature };
					currentPlatform.Methods.Add(currentMethod);
					foreach (var instructionSet in method.InstructionSets) {
						if (instructionSet.ChunkCount != instructionSet.CodeChunks.Length) {
							Console.WriteLine("Error: Chunk count does not match number of chunks.");
							return;
						}

						foreach (var chunk in instructionSet.CodeChunks) {
							var tmpFile = Path.GetTempFileName();
							var si = new ProcessStartInfo("nasm", string.Format("-fbin -o{1} {0}", chunk.FileName, tmpFile)) { RedirectStandardOutput = true, UseShellExecute = false };
							var nasm = new Process { StartInfo = si };
							nasm.Start();
							nasm.WaitForExit();
							if (nasm.ExitCode == 0) {
								currentMethod.Chunks.Add(new ChunkInfo() { ChunkFileName = tmpFile, InstructionSet = instructionSet.Type });
							} else
								Console.WriteLine(nasm.StandardOutput.ReadToEnd());
						}
					}
				}
			}

			using (var outFile = File.Open(args[1], FileMode.Create, FileAccess.Write)) {
				var writer = new BinaryWriter(outFile);
				writer.Write("SGEN".ToCharArray());
				writer.Write(binFiles.Count);
				foreach (var platform in binFiles) {
					writer.Write(platform.Methods.Count);
					writer.Write((int)platform.Platform);

					foreach (var method in platform.Methods) {
						writer.Write(method.Chunks.Count);
						var methodNameBytes = Encoding.Unicode.GetBytes(method.MethodName);
                        var methodSignatureBytes = Encoding.Unicode.GetBytes(method.MethodSignature);
						writer.Write(methodNameBytes.Length);
                        writer.Write(methodSignatureBytes.Length);
						writer.Write(methodNameBytes);
                        writer.Write(methodSignatureBytes);

						foreach (var chunk in method.Chunks) {
							var fi = new FileInfo(chunk.ChunkFileName);
							writer.Write((int)fi.Length); //ChunkInfo [ LEN, InstructionSet, byte[] ]
							writer.Write((int)chunk.InstructionSet);
							using (var fis = new BinaryReader(fi.OpenRead())) {
								writer.Write(fis.ReadBytes((int)fi.Length));
							}
						}
					}
				}
			}
		}
	}
}
