using System;
using System.Collections.Generic;
using System.Text;
using SlimMath;
using SlimGen;
using System.IO;
using System.Diagnostics;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {
            float result = 0.0f;
            var injector = new Injector("debugger.exe");

            var watch = Stopwatch.StartNew();
            for (int i = 0; i < 100000; i++)
                result += Vector4.Dot(new Vector4(1.0f, 2.0f, 3.0f, 4.0f), new Vector4(5.0f, 6.0f, 7.0f, 8.0f));
            watch.Stop();
            Console.WriteLine("normal: " + watch.ElapsedTicks);

            var method = new MethodReplacement(typeof(Vector4).GetMethod("Dot"), Platform.X64, InstructionSets.SSE41, new[] { File.ReadAllBytes("dot_movups.bin") });
            injector.Replace(new[] { method });

            watch = Stopwatch.StartNew();
            for (int i = 0; i < 100000; i++)
                result += Vector4.Dot(new Vector4(1.0f, 2.0f, 3.0f, 4.0f), new Vector4(5.0f, 6.0f, 7.0f, 8.0f));
            watch.Stop();
            Console.WriteLine("movups: " + watch.ElapsedTicks);

            method = new MethodReplacement(typeof(Vector4).GetMethod("Dot"), Platform.X64, InstructionSets.SSE41, new[] { File.ReadAllBytes("dot_lddqu.bin") });
            injector.Replace(new[] { method });

            watch = Stopwatch.StartNew();
            for (int i = 0; i < 100000; i++)
                result += Vector4.Dot(new Vector4(1.0f, 2.0f, 3.0f, 4.0f), new Vector4(5.0f, 6.0f, 7.0f, 8.0f));
            watch.Stop();
            Console.WriteLine("lddqu: " + watch.ElapsedTicks);

            method = new MethodReplacement(typeof(Vector4).GetMethod("Dot"), Platform.X64, InstructionSets.SSE41, new[] { File.ReadAllBytes("dot_movaps.bin") });
            injector.Replace(new[] { method });

            watch = Stopwatch.StartNew();
            for (int i = 0; i < 100000; i++)
                result += Vector4.Dot(new Vector4(1.0f, 2.0f, 3.0f, 4.0f), new Vector4(5.0f, 6.0f, 7.0f, 8.0f));
            watch.Stop();
            Console.WriteLine("movaps: " + watch.ElapsedTicks);
        }
    }
}
