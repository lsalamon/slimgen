using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using SlimGen;
using System.IO;

namespace Test
{
    struct Vector4
    {
        public float X, Y, Z, W;

		[ReplaceMethod(DataFiles = new []{"dp.sse3.x64"}, InstructionSet = InstructionSets.SSE3, Platform = Platform.X64)]
        public static void DotProduct(ref Vector4 left, ref Vector4 right, out float result)
        {
            result = left.X * right.X + left.Y * right.Y + left.Z * right.Z + left.W * right.W;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var left = new Vector4 { X = 1, Y = 2, Z = 3, W = 4 };
            var right = new Vector4 { X = 5, Y = 6, Z = 7, W = 8 };

            float result1;
            Vector4.DotProduct(ref left, ref right, out result1);

            var injector = new Injector("../../../Debugger/x64/Debug/debugger.exe");
            injector.ProcessAssemblies(typeof(Program).Assembly);

            //Console.WriteLine(injector.Errors);

            float result2;
            Vector4.DotProduct(ref left, ref right, out result2);

            Console.WriteLine("{0} == {1}", result1, result2);

            //Debug.Assert(result1 == result2, "Dot product between SlimGen and non-SlimGen were different!");*/

            Console.ReadLine();
        }
    }
}
