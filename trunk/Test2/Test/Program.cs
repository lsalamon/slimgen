using System;
using System.Collections.Generic;
using System.Text;
using SlimMath;
using SlimGen;
using System.IO;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            var injector = new Injector("debugger.exe");

            var method = new MethodReplacement(typeof(Vector4).GetMethod("Dot"), Platform.X64, InstructionSets.SSE41, new[] { File.ReadAllBytes("dot.obj") });
            injector.Replace(new[] { method });
            Console.WriteLine(injector.Errors);

            float result = Vector4.Dot(Vector4.One, Vector4.UnitY);
            Console.WriteLine(result);
        }
    }
}
