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
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace SlimGenTest {
    class Program {
        static void Main(string[] args) {
            var left = new Vector4 { X = 1, Y = 2, Z = 3, W = 4 };
            var right = new Vector4 { X = 5, Y = 6, Z = 7, W = 8 };

            float result1;
            Vector4.DotProduct(ref left, ref right, out result1);

            SlimGenUtility.Run();
            
            float result2;
            Vector4.DotProduct(ref left, ref right, out result2);

            Console.WriteLine("{0} == {1}", result1, result2);
            Debug.Assert(result1 == result2, "Dot product between SlimGen and non-SlimGen were different!");
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    struct Vector4 {
        public float X, Y, Z, W;

        public static void DotProduct(ref Vector4 left, ref Vector4 right, out float result) {
            result = left.X * right.X + left.Y * right.Y + left.Z * right.Z + left.W * right.W;
        }
    }

    public static class SlimGenUtility {
        public static void Run() {
            RuntimeHelpers.PrepareMethod(typeof(Vector4).GetMethod("DotProduct").MethodHandle);

            if(Debugger.IsAttached) {
                Debugger.Break();
            }
        }
    }
}
