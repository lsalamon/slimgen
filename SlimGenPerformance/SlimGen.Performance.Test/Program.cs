using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimGen.Performance.Math;
using System.Diagnostics;

namespace SlimGen.Performance.Test
{
    class Program
    {
        static void FillMatrixArray(Matrix[] m)
        {
            var r = new Random();
            for (var i = 0; i < m.Length; ++i)
            {
                m[i].M11 = (float)r.NextDouble();
                m[i].M12 = (float)r.NextDouble();
                m[i].M13 = (float)r.NextDouble();
                m[i].M14 = (float)r.NextDouble();

                m[i].M21 = (float)r.NextDouble();
                m[i].M22 = (float)r.NextDouble();
                m[i].M23 = (float)r.NextDouble();
                m[i].M24 = (float)r.NextDouble();

                m[i].M31 = (float)r.NextDouble();
                m[i].M32 = (float)r.NextDouble();
                m[i].M33 = (float)r.NextDouble();
                m[i].M34 = (float)r.NextDouble();

                m[i].M41 = (float)r.NextDouble();
                m[i].M42 = (float)r.NextDouble();
                m[i].M43 = (float)r.NextDouble();
                m[i].M44 = (float)r.NextDouble();
            }
        }
        static void Main(string[] args)
        {
            var source1 = new Matrix[100000];
            var source2 = new Matrix[100000];
            var result = new Matrix[100000];
            var watch = new Stopwatch();

            FillMatrixArray(source1);
            FillMatrixArray(source2);

            watch.Start();
            watch.Stop();
            watch.Reset();
            Matrix.SlimGenMultiply(ref source1[0], ref source2[0], out result[0]);
            Matrix.Multiply(ref source1[0], ref source2[0], out result[0]);

            watch.Start();
            for (var i = 0; i < result.Length; ++i)
            {
                Matrix.SlimGenMultiply(ref source1[i], ref source2[i], out result[i]);
            }
            watch.Stop();
            watch.Reset();

            watch.Start();
            for (var i = 0; i < result.Length; ++i)
            {
                Matrix.Multiply(ref source1[i], ref source2[i], out result[i]);
            }
            watch.Stop();
            watch.Reset();

            watch.Start();
            for (int i = 0; i < result.Length; ++i)
            {
                Matrix.Multiply(ref source1[i], ref source2[i], out result[i]);
            }
            watch.Stop();
            Console.WriteLine("Multiply        tick count: {0}", watch.ElapsedTicks);
            watch.Reset();

            watch.Start();
            for (int i = 0; i < result.Length; ++i)
            {
                Matrix.SlimGenMultiply(ref source1[i], ref source2[i], out result[i]);
            }
            watch.Stop();
            Console.WriteLine("SlimGenMultiply tick count: {0}", watch.ElapsedTicks);
            watch.Reset();
        }
    }
}
