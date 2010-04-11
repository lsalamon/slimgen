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
using System.Text;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Runtime.CompilerServices;
using System.Globalization;

namespace SlimGen
{
    public static class Injector
    {
        public static string Errors
        {
            get;
            private set;
        }

        public static bool Replace(string debuggerPath, IEnumerable<MethodReplacement> methods)
        {
            var stack = new StackTrace(false).GetFrames();
            foreach (var frame in stack)
            {
                foreach (var method in methods)
                {
                    if (frame.GetMethod() == method.Method)
                        throw new InvalidOperationException("Cannot replace a method that is currently on the call stack.");
                }
            }

            var data = new List<byte>();
            foreach (var method in methods)
            {
                RuntimeHelpers.PrepareMethod(method.Method.MethodHandle);
                method.GetBytes(data);
            }

            return Launch(debuggerPath, data.ToArray());
        }

        static bool Launch(string debuggerPath, byte[] data)
        {
            Errors = string.Empty;

            using (var process = new Process())
            {
                process.StartInfo.Arguments = Process.GetCurrentProcess().Id.ToString(CultureInfo.InvariantCulture);
                process.StartInfo.CreateNoWindow = false;
                process.StartInfo.FileName = debuggerPath;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.RedirectStandardInput = true;
                process.StartInfo.RedirectStandardOutput = true;
                process.Start();

                process.StandardInput.BaseStream.Write(data, 0, data.Length);
                process.StandardInput.Flush();

                while (!Debugger.IsAttached && !process.HasExited)
                    Thread.Sleep(10);

                if (process.HasExited)
                    return false;

                Debugger.Break();
                process.WaitForExit();

                Errors = process.StandardOutput.ReadToEnd();
                return process.ExitCode == 0;
            }
        }
    }
}
