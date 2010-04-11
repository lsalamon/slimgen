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
using System.Runtime.InteropServices;
using System.Security;
using Microsoft.Win32.SafeHandles;

namespace SlimGen
{
    [StructLayout(LayoutKind.Sequential)]
    struct SECURITY_ATTRIBUTES
    {
        public int nLength;
        public IntPtr lpSecurityDescriptor;
        public int bInheritHandle;

        public SECURITY_ATTRIBUTES(bool inherit)
        {
            nLength = Marshal.SizeOf(typeof(SECURITY_ATTRIBUTES));
            lpSecurityDescriptor = IntPtr.Zero;
            bInheritHandle = inherit ? 1 : 0;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    struct CPUInfo
    {
        int Part1;
        int Part2;
        int Part3;
        int Part4;

        public int this[int index]
        {
            get
            {
                switch (index)
                {
                    case 0: return Part1;
                    case 1: return Part2;
                    case 2: return Part3;
                    case 3: return Part4;
                }

                return -1;
            }
        }
    }

    static class NativeMethods
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [SuppressUnmanagedCodeSecurity]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool CreatePipe(out SafeFileHandle hReadPipe, out SafeFileHandle hWritePipe, ref SECURITY_ATTRIBUTES lpPipeAttributes, uint nSize);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [SuppressUnmanagedCodeSecurity]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool DuplicateHandle(IntPtr hSourceProcessHandle, SafeFileHandle hSourceHandle, IntPtr hTargetProcessHandle, out SafeFileHandle lpTargetHandle, uint dwDesiredAccess, [MarshalAs(UnmanagedType.Bool)] bool bInheritHandle, uint dwOptions);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        [SuppressUnmanagedCodeSecurity]
        public static extern IntPtr GetCurrentProcess();

        [DllImport("cpuid.dll")]
        public static extern CPUInfo cpuid(int InfoType);

        [DllImport("cpuid.dll")]
        public static extern CPUInfo cpuid(uint InfoType);

        [DllImport("cpuid.dll")]
        public static extern CPUInfo cpuidex(int InfoType, int ECXValue);
    }
}
