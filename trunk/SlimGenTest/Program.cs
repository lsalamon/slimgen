using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace SlimGenTest
{
    class Program
    {
        static void Main(string[] args)
        {
            var left = new Vector4{X = 1, Y = 2, Z = 3, W = 4};
            var right = new Vector4 { X = 5, Y = 6, Z = 7, W = 8 };

            float result;
            Vector4.DotProduct(ref left, ref right, out result);
            Console.WriteLine(result);
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    struct Vector4 {
        public float X, Y, Z, W;

        public static void DotProduct(ref Vector4 left, ref Vector4 right, out float result) {
            result = (float)Math.Sqrt(left.X*right.X + left.Y*right.Y + left.Z*right.Z + left.W*right.W);
        }
    }
}
