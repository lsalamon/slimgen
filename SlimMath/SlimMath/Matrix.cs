using System;
using System.Runtime.InteropServices;

using SlimGen.Generator;

namespace SlimMath {
    [StructLayout(LayoutKind.Sequential)]
    public struct Matrix {
        public float M11, M12, M13, M14;
        public float M21, M22, M23, M24;
        public float M31, M32, M33, M34;
        public float M41, M42, M43, M44;

        public static readonly Matrix IdentityMatrix;
        public static readonly Matrix ZeroMatrix;

        #region Constructors
        static Matrix() {
            Identity(ref IdentityMatrix);
            Zero(ref ZeroMatrix);
        }

        public Matrix(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44) {
            M11 = m11;
            M12 = m12;
            M13 = m13;
            M14 = m14;

            M21 = m21;
            M22 = m22;
            M23 = m23;
            M24 = m24;

            M31 = m31;
            M32 = m32;
            M33 = m33;
            M34 = m34;

            M41 = m41;
            M42 = m42;
            M43 = m43;
            M44 = m44;
        }

        public Matrix(float[] m) {
            if (m.Length != 16)
                throw new IndexOutOfRangeException("Array must be 16 elements in size.");

            M11 = m[0];
            M12 = m[1];
            M13 = m[2];
            M14 = m[3];

            M21 = m[4];
            M22 = m[5];
            M23 = m[6];
            M24 = m[7];

            M31 = m[8];
            M32 = m[9];
            M33 = m[10];
            M34 = m[11];

            M41 = m[12];
            M42 = m[13];
            M43 = m[14];
            M44 = m[15];
        }

        public unsafe Matrix(float* m) {
            M11 = m[0];
            M12 = m[1];
            M13 = m[2];
            M14 = m[3];

            M21 = m[4];
            M22 = m[5];
            M23 = m[6];
            M24 = m[7];

            M31 = m[8];
            M32 = m[9];
            M33 = m[10];
            M34 = m[11];

            M41 = m[12];
            M42 = m[13];
            M43 = m[14];
            M44 = m[15];
        }

        public Matrix(Vector v1, Vector v2, Vector v3, Vector v4) {
            M11 = v1.X;
            M12 = v1.Y;
            M13 = v1.Z;
            M14 = v1.W;

            M21 = v2.X;
            M22 = v2.Y;
            M23 = v2.Z;
            M24 = v2.W;

            M31 = v3.X;
            M32 = v3.Y;
            M33 = v3.Z;
            M34 = v3.W;

            M41 = v4.X;
            M42 = v4.Y;
            M43 = v4.Z;
            M44 = v4.W;
        }

        public Matrix(Vector[] va) : this(va[0], va[1], va[2], va[3]) {}
        #endregion

        public static void Identity(ref Matrix m) {
            m = new Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
        }

        public static void Zero(ref Matrix m) {
            m = new Matrix();
        }

        [ReplaceMethodNative]
        public static void Add(ref Matrix left, ref Matrix right, out Matrix result) {
            Matrix r;
            r.M11 = left.M11 + right.M11;
            r.M12 = left.M12 + right.M12;
            r.M13 = left.M13 + right.M13;
            r.M14 = left.M14 + right.M14;

            r.M21 = left.M21 + right.M21;
            r.M22 = left.M22 + right.M22;
            r.M23 = left.M23 + right.M23;
            r.M24 = left.M24 + right.M24;

            r.M31 = left.M31 + right.M31;
            r.M32 = left.M32 + right.M32;
            r.M33 = left.M33 + right.M33;
            r.M34 = left.M34 + right.M34;

            r.M41 = left.M41 + right.M41;
            r.M42 = left.M42 + right.M42;
            r.M43 = left.M43 + right.M43;
            r.M44 = left.M44 + right.M44;
            result = r;
        }

        [ReplaceMethodNative]
        public static void Subtract(ref Matrix left, ref Matrix right, out Matrix result) {
            Matrix r;
            r.M11 = left.M11 - right.M11;
            r.M12 = left.M12 - right.M12;
            r.M13 = left.M13 - right.M13;
            r.M14 = left.M14 - right.M14;

            r.M21 = left.M21 - right.M21;
            r.M22 = left.M22 - right.M22;
            r.M23 = left.M23 - right.M23;
            r.M24 = left.M24 - right.M24;

            r.M31 = left.M31 - right.M31;
            r.M32 = left.M32 - right.M32;
            r.M33 = left.M33 - right.M33;
            r.M34 = left.M34 - right.M34;

            r.M41 = left.M41 - right.M41;
            r.M42 = left.M42 - right.M42;
            r.M43 = left.M43 - right.M43;
            r.M44 = left.M44 - right.M44;
            result = r;
        }

        [ReplaceMethodNative]
        public static void Scale(ref Matrix m, float scalar, out Matrix result) {
            Matrix r;
            r.M11 = m.M11 * scalar;
            r.M12 = m.M12 * scalar;
            r.M13 = m.M13 * scalar;
            r.M14 = m.M14 * scalar;

            r.M21 = m.M21 * scalar;
            r.M22 = m.M22 * scalar;
            r.M23 = m.M23 * scalar;
            r.M24 = m.M24 * scalar;

            r.M31 = m.M31 * scalar;
            r.M32 = m.M32 * scalar;
            r.M33 = m.M33 * scalar;
            r.M34 = m.M34 * scalar;

            r.M41 = m.M41 * scalar;
            r.M42 = m.M42 * scalar;
            r.M43 = m.M43 * scalar;
            r.M44 = m.M44 * scalar;
            result = r;
        }

        [ReplaceMethodNative]
        public static void Multiply(ref Matrix left, ref Matrix right, out Matrix result) {
            Matrix r;
            r.M11 = (left.M11 * right.M11) + (left.M12 * right.M21) + (left.M13 * right.M31) + (left.M14 * right.M41);
            r.M12 = (left.M11 * right.M12) + (left.M12 * right.M22) + (left.M13 * right.M32) + (left.M14 * right.M42);
            r.M13 = (left.M11 * right.M13) + (left.M12 * right.M23) + (left.M13 * right.M33) + (left.M14 * right.M43);
            r.M14 = (left.M11 * right.M14) + (left.M12 * right.M24) + (left.M13 * right.M34) + (left.M14 * right.M44);
            r.M21 = (left.M21 * right.M11) + (left.M22 * right.M21) + (left.M23 * right.M31) + (left.M24 * right.M41);
            r.M22 = (left.M21 * right.M12) + (left.M22 * right.M22) + (left.M23 * right.M32) + (left.M24 * right.M42);
            r.M23 = (left.M21 * right.M13) + (left.M22 * right.M23) + (left.M23 * right.M33) + (left.M24 * right.M43);
            r.M24 = (left.M21 * right.M14) + (left.M22 * right.M24) + (left.M23 * right.M34) + (left.M24 * right.M44);
            r.M31 = (left.M31 * right.M11) + (left.M32 * right.M21) + (left.M33 * right.M31) + (left.M34 * right.M41);
            r.M32 = (left.M31 * right.M12) + (left.M32 * right.M22) + (left.M33 * right.M32) + (left.M34 * right.M42);
            r.M33 = (left.M31 * right.M13) + (left.M32 * right.M23) + (left.M33 * right.M33) + (left.M34 * right.M43);
            r.M34 = (left.M31 * right.M14) + (left.M32 * right.M24) + (left.M33 * right.M34) + (left.M34 * right.M44);
            r.M41 = (left.M41 * right.M11) + (left.M42 * right.M21) + (left.M43 * right.M31) + (left.M44 * right.M41);
            r.M42 = (left.M41 * right.M12) + (left.M42 * right.M22) + (left.M43 * right.M32) + (left.M44 * right.M42);
            r.M43 = (left.M41 * right.M13) + (left.M42 * right.M23) + (left.M43 * right.M33) + (left.M44 * right.M43);
            r.M44 = (left.M41 * right.M14) + (left.M42 * right.M24) + (left.M43 * right.M34) + (left.M44 * right.M44);
            result = r;
        }
    }
}

