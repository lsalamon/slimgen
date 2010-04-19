/*
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
            if (IntPtr.Size == 4)
                Platform = Platform.X86;
            else
                Platform = Platform.X64;
        }

        public Injector(string debuggerPath)
        {
            DebuggerPath = debuggerPath;
        }

        public bool Replace(IEnumerable<MethodReplacement> methods)
        {
            methods = Filter(methods);
            return Launch(methods);
        }

        IEnumerable<MethodReplacement> Filter(IEnumerable<MethodReplacement> methods)
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

        bool Launch(IEnumerable<MethodReplacement> methods)
        {
            Errors = string.Empty;

            using (var process = new Process())
            {
                process.StartInfo.Arguments = Process.GetCurrentProcess().Id.ToString(CultureInfo.InvariantCulture);
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.FileName = DebuggerPath;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.RedirectStandardInput = true;
                process.StartInfo.RedirectStandardOutput = true;
                process.Start();

                foreach (var method in methods)
                {
                    RuntimeHelpers.PrepareMethod(method.Method.MethodHandle);
                    method.Write(process.StandardInput);
                }

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
