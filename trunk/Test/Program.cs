using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using SlimGen;

namespace Test
{
    struct Vector4
    {
        public float X, Y, Z, W;

        public static void DotProduct(ref Vector4 left, ref Vector4 right, out float result)
        {
            result = left.X * right.X + left.Y * right.Y + left.Z * right.Z + left.W * right.W;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            /*var left = new Vector4 { X = 1, Y = 2, Z = 3, W = 4 };
            var right = new Vector4 { X = 5, Y = 6, Z = 7, W = 8 };

            float result1;
            Vector4.DotProduct(ref left, ref right, out result1);

            var methods = new List<MethodReplacement>();
            methods.Add(new MethodReplacement(typeof(Vector4).GetMethod("DotProduct"), Platform.X64, InstructionSet.SSE3, new byte[10][]));
            bool result = Injector.Replace("../../../Debugger/x64/Debug/debugger.exe", methods);

            float result2;
            Vector4.DotProduct(ref left, ref right, out result2);

            Console.WriteLine("{0} == {1}", result1, result2);
            Debug.Assert(result1 == result2, "Dot product between SlimGen and non-SlimGen were different!");*/

            Console.WriteLine(CpuInformation.Manufacturer);
            Console.WriteLine(CpuInformation.Brand);
            Console.WriteLine(CpuInformation.InstructionSets);
            Console.WriteLine(CpuInformation.Features.ToString().Replace(",", "\n"));
            Console.WriteLine(CpuInformation.ExtraInstructions);
            Console.WriteLine();
            Console.WriteLine(CpuInformation.GetHighestSimdLevel(InstructionSets.MMX | InstructionSets.Amd3DNow | InstructionSets.SSE3));
        }
    }
}
