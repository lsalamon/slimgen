﻿/*
* Copyright (c) 2007-2010 SlimGen Group
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
using System.Globalization;
using System.IO;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Reflection;

namespace SlimGen
{
    public class Injector
    {
        public static readonly Platform Platform;

        public string DebuggerPath
        {
            get;
            private set;
        }

        public string Errors
        {
            get;
            private set;
        }

        static Injector()
        {
            Platform = IntPtr.Size == 4 ? Platform.X86 : Platform.X64;
        }

        public Injector(string debuggerPath)
        {
            DebuggerPath = debuggerPath;
        }

        public void ProcessAssemblies(params Assembly[] assemblies)
        {
            var methods = new List<MethodReplacement>();

            foreach (var assembly in assemblies)
            {
                foreach (var type in assembly.GetTypes())
                {
                    foreach (var method in type.GetMethods(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static))
                    {
                        ProcessMethod(method, methods);
                    }
                }
            }

            Replace(methods);
        }

        public bool Replace(IEnumerable<MethodReplacement> methods)
        {
            methods = Filter(methods);
            return Launch(false, stream =>
            {
                foreach (var method in methods)
                {
                    RuntimeHelpers.PrepareMethod(method.Method.MethodHandle);
                    method.Write(stream);
                }
            });
        }

        public bool GenerateTemplates(IEnumerable<MethodBase> methods, string outputDirectory)
        {
            return Launch(true, stream =>
            {
                stream.WriteLine(outputDirectory);
                foreach (var method in methods)
                {
                    RuntimeHelpers.PrepareMethod(method.MethodHandle);
                    stream.WriteLine(method.DeclaringType.Assembly.FullName);
                    stream.WriteLine(MethodReplacement.GetMethodSignature(method));
                }
            });
        }

        static void ProcessMethod(MethodBase method, ICollection<MethodReplacement> methods)
        {
            var attributes = method.GetCustomAttributes(typeof(ReplaceMethodAttribute), false);

            foreach (ReplaceMethodAttribute replaceMethodAttribute in attributes)
            {
                var dataSets = new byte[replaceMethodAttribute.DataFiles.Length][];
                var isMissingData = false;
                for (var i = 0; i < dataSets.Length; ++i)
                {
                    try
                    {
                        dataSets[i] = File.ReadAllBytes(replaceMethodAttribute.DataFiles[i]);
                    }
                    catch (Exception)
                    {
                        isMissingData = true;
                        break;
                    }
                }
                if (isMissingData)
                    continue;
                methods.Add(new MethodReplacement(method, replaceMethodAttribute.Platform, replaceMethodAttribute.InstructionSet, dataSets));
            }
        }

        static IEnumerable<MethodReplacement> Filter(IEnumerable<MethodReplacement> methods)
        {
            var stack = new Dictionary<MethodBase, object>();
            var map = new Dictionary<MethodBase, MethodReplacement>();

            foreach (var frame in new StackTrace(false).GetFrames())
                stack.Add(frame.GetMethod(), null);

            foreach (var method in methods)
            {
                if (method.Platform != Platform || (CpuInformation.InstructionSets & method.InstructionSet) == 0)
                    continue;

                if (stack.ContainsKey(method.Method))
                    throw new InvalidOperationException("Cannot replace a method that is currently on the call stack.");

                if (map.ContainsKey(method.Method))
                {
                    if (method.InstructionSet.CompareTo(map[method.Method]) > 0)
                        map[method.Method] = method;
                }
                else
                    map.Add(method.Method, method);
            }

            return map.Values;
        }

        bool Launch(bool buildTemplates, Action<StreamWriter> writeMethods)
        {
            Errors = string.Empty;

            using (var process = new Process())
            {
                process.StartInfo.Arguments = Process.GetCurrentProcess().Id.ToString(CultureInfo.InvariantCulture) + (buildTemplates ? " builder" : "");
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.FileName = DebuggerPath;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.RedirectStandardInput = true;
                process.StartInfo.RedirectStandardOutput = true;
                process.Start();

                process.StandardInput.WriteLine(GetType().Assembly.ImageRuntimeVersion);

                writeMethods(process.StandardInput);

                process.StandardInput.WriteLine();
                process.StandardInput.Flush();

                while (!Debugger.IsAttached && !process.HasExited)
                    Thread.Sleep(10);

                if (process.HasExited)
                    return false;

                Debugger.Break();

                Errors = process.StandardOutput.ReadToEnd();
                process.WaitForExit();

                return process.ExitCode == 0;
            }
        }
    }
}
