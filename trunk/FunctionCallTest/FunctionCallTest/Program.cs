using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.CompilerServices;

namespace FunctionCallTest
{
    class Program
    {
        static void Main(string[] args)
        {
            PrimitiveTypes.NoParams();

            PrimitiveTypes.ByteParam1(1);
            PrimitiveTypes.ByteParam2(1, 2);
            PrimitiveTypes.ByteParam3(1, 2, 3);
            PrimitiveTypes.ByteParam4(1, 2, 3, 4);
            PrimitiveTypes.ByteParam5(1, 2, 3, 4, 5);
            PrimitiveTypes.ByteParam6(1, 2, 3, 4, 5, 6);
            PrimitiveTypes.ByteParam7(1, 2, 3, 4, 5, 6, 7);
            PrimitiveTypes.ByteParam8(1, 2, 3, 4, 5, 6, 7, 8);

            PrimitiveTypes.IntParam1(1);
            PrimitiveTypes.IntParam2(1, 2);
            PrimitiveTypes.IntParam3(1, 2, 3);
            PrimitiveTypes.IntParam4(1, 2, 3, 4);
            PrimitiveTypes.IntParam5(1, 2, 3, 4, 5);
            PrimitiveTypes.IntParam6(1, 2, 3, 4, 5, 6);
            PrimitiveTypes.IntParam7(1, 2, 3, 4, 5, 6, 7);
            PrimitiveTypes.IntParam8(1, 2, 3, 4, 5, 6, 7, 8);

            PrimitiveTypes.FloatParam1(1);
            PrimitiveTypes.FloatParam2(1, 2);
            PrimitiveTypes.FloatParam3(1, 2, 3);
            PrimitiveTypes.FloatParam4(1, 2, 3, 4);
            PrimitiveTypes.FloatParam5(1, 2, 3, 4, 5);
            PrimitiveTypes.FloatParam6(1, 2, 3, 4, 5, 6);
            PrimitiveTypes.FloatParam7(1, 2, 3, 4, 5, 6, 7);
            PrimitiveTypes.FloatParam8(1, 2, 3, 4, 5, 6, 7, 8);

            PrimitiveTypes.DecimalParam1(1);
            PrimitiveTypes.DecimalParam2(1, 2);
            PrimitiveTypes.DecimalParam3(1, 2, 3);
            PrimitiveTypes.DecimalParam4(1, 2, 3, 4);
            PrimitiveTypes.DecimalParam5(1, 2, 3, 4, 5);
            PrimitiveTypes.DecimalParam6(1, 2, 3, 4, 5, 6);
            PrimitiveTypes.DecimalParam7(1, 2, 3, 4, 5, 6, 7);
            PrimitiveTypes.DecimalParam8(1, 2, 3, 4, 5, 6, 7, 8);

            int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5, i6 = 6, i7 = 7, i8 = 8;

            PrimitiveTypes.IntRefParam1(ref i1);
            PrimitiveTypes.IntRefParam2(ref i1, ref i2);
            PrimitiveTypes.IntRefParam3(ref i1, ref i2, ref i3);
            PrimitiveTypes.IntRefParam4(ref i1, ref i2, ref i3, ref i4);
            PrimitiveTypes.IntRefParam5(ref i1, ref i2, ref i3, ref i4, ref i5);
            PrimitiveTypes.IntRefParam6(ref i1, ref i2, ref i3, ref i4, ref i5, ref i6);
            PrimitiveTypes.IntRefParam7(ref i1, ref i2, ref i3, ref i4, ref i5, ref i6, ref i7);
            PrimitiveTypes.IntRefParam8(ref i1, ref i2, ref i3, ref i4, ref i5, ref i6, ref i7, ref i8);

            float f1 = 1, f2 = 2, f3 = 3, f4 = 4, f5 = 5, f6 = 6, f7 = 7, f8 = 8;

            PrimitiveTypes.RefFloatParam1(ref f1);
            PrimitiveTypes.RefFloatParam2(ref f1, ref f2);
            PrimitiveTypes.RefFloatParam3(ref f1, ref f2, ref f3);
            PrimitiveTypes.RefFloatParam4(ref f1, ref f2, ref f3, ref f4);
            PrimitiveTypes.RefFloatParam5(ref f1, ref f2, ref f3, ref f4, ref f5);
            PrimitiveTypes.RefFloatParam6(ref f1, ref f2, ref f3, ref f4, ref f5, ref f6);
            PrimitiveTypes.RefFloatParam7(ref f1, ref f2, ref f3, ref f4, ref f5, ref f6, ref f7);
            PrimitiveTypes.RefFloatParam8(ref f1, ref f2, ref f3, ref f4, ref f5, ref f6, ref f7, ref f8);

            PrimitiveTypes.StringParam1("1");
            PrimitiveTypes.StringParam2("1", "2");
            PrimitiveTypes.StringParam3("1", "2", "3");
            PrimitiveTypes.StringParam4("1", "2", "3", "4");
            PrimitiveTypes.StringParam5("1", "2", "3", "4", "5");
            PrimitiveTypes.StringParam6("1", "2", "3", "4", "5", "6");
            PrimitiveTypes.StringParam7("1", "2", "3", "4", "5", "6", "7");
            PrimitiveTypes.StringParam8("1", "2", "3", "4", "5", "6", "7", "8");

            string s1 = "1", s2 = "2", s3 = "3", s4 = "4", s5 = "5", s6 = "6", s7 = "7", s8 = "8";

            PrimitiveTypes.RefStringParam1(ref s1);
            PrimitiveTypes.RefStringParam2(ref s1, ref s2);
            PrimitiveTypes.RefStringParam3(ref s1, ref s2, ref s3);
            PrimitiveTypes.RefStringParam4(ref s1, ref s2, ref s3, ref s4);
            PrimitiveTypes.RefStringParam5(ref s1, ref s2, ref s3, ref s4, ref s5);
            PrimitiveTypes.RefStringParam6(ref s1, ref s2, ref s3, ref s4, ref s5, ref s6);
            PrimitiveTypes.RefStringParam7(ref s1, ref s2, ref s3, ref s4, ref s5, ref s6, ref s7);
            PrimitiveTypes.RefStringParam8(ref s1, ref s2, ref s3, ref s4, ref s5, ref s6, ref s7, ref s8);

            PrimitiveTypes.IntArrayParam1(new int[] { 1 });
            PrimitiveTypes.IntArrayParam2(new int[] { 1 }, new int[] { 2 });
            PrimitiveTypes.IntArrayParam3(new int[] { 1 }, new int[] { 2 }, new int[] { 3 });
            PrimitiveTypes.IntArrayParam4(new int[] { 1 }, new int[] { 2 }, new int[] { 3 }, new int[] { 4 });
            PrimitiveTypes.IntArrayParam5(new int[] { 1 }, new int[] { 2 }, new int[] { 3 }, new int[] { 4 }, new int[] { 5 });
            PrimitiveTypes.IntArrayParam6(new int[] { 1 }, new int[] { 2 }, new int[] { 3 }, new int[] { 4 }, new int[] { 5 }, new int[] { 6 });
            PrimitiveTypes.IntArrayParam7(new int[] { 1 }, new int[] { 2 }, new int[] { 3 }, new int[] { 4 }, new int[] { 5 }, new int[] { 6 }, new int[] { 7 });
            PrimitiveTypes.IntArrayParam8(new int[] { 1 }, new int[] { 2 }, new int[] { 3 }, new int[] { 4 }, new int[] { 5 }, new int[] { 6 }, new int[] { 7 }, new int[] { 8 });

            PrimitiveTypes.FloatArrayParam1(new float[] { 1 });
            PrimitiveTypes.FloatArrayParam2(new float[] { 1 }, new float[] { 2 });
            PrimitiveTypes.FloatArrayParam3(new float[] { 1 }, new float[] { 2 }, new float[] { 3 });
            PrimitiveTypes.FloatArrayParam4(new float[] { 1 }, new float[] { 2 }, new float[] { 3 }, new float[] { 4 });
            PrimitiveTypes.FloatArrayParam5(new float[] { 1 }, new float[] { 2 }, new float[] { 3 }, new float[] { 4 }, new float[] { 5 });
            PrimitiveTypes.FloatArrayParam6(new float[] { 1 }, new float[] { 2 }, new float[] { 3 }, new float[] { 4 }, new float[] { 5 }, new float[] { 6 });
            PrimitiveTypes.FloatArrayParam7(new float[] { 1 }, new float[] { 2 }, new float[] { 3 }, new float[] { 4 }, new float[] { 5 }, new float[] { 6 }, new float[] { 7 });
            PrimitiveTypes.FloatArrayParam8(new float[] { 1 }, new float[] { 2 }, new float[] { 3 }, new float[] { 4 }, new float[] { 5 }, new float[] { 6 }, new float[] { 7 }, new float[] { 8 });

            int[] ia1 = new int[] {1}, ia2 = new int[] {2}, ia3 = new int[] {3}, ia4 = new int[] {4}, ia5 = new int[] {5}, ia6 = new int[] {6}, ia7 = new int[] {7}, ia8 = new int[] {8};

            PrimitiveTypes.RefIntArrayParam1(ref ia1);
            PrimitiveTypes.RefIntArrayParam2(ref ia1, ref ia2);
            PrimitiveTypes.RefIntArrayParam3(ref ia1, ref ia2, ref ia3);
            PrimitiveTypes.RefIntArrayParam4(ref ia1, ref ia2, ref ia3, ref ia4);
            PrimitiveTypes.RefIntArrayParam5(ref ia1, ref ia2, ref ia3, ref ia4, ref ia5);
            PrimitiveTypes.RefIntArrayParam6(ref ia1, ref ia2, ref ia3, ref ia4, ref ia5, ref ia6);
            PrimitiveTypes.RefIntArrayParam7(ref ia1, ref ia2, ref ia3, ref ia4, ref ia5, ref ia6, ref ia7);
            PrimitiveTypes.RefIntArrayParam8(ref ia1, ref ia2, ref ia3, ref ia4, ref ia5, ref ia6, ref ia7, ref ia8);

            float[] fa1 = new float[] { 1 }, fa2 = new float[] { 2 }, fa3 = new float[] { 3 }, fa4 = new float[] { 4 }, fa5 = new float[] { 5 }, fa6 = new float[] { 6 }, fa7 = new float[] { 7 }, fa8 = new float[] { 8 };

            PrimitiveTypes.RefFloatArrayParam1(ref fa1);
            PrimitiveTypes.RefFloatArrayParam2(ref fa1, ref fa2);
            PrimitiveTypes.RefFloatArrayParam3(ref fa1, ref fa2, ref fa3);
            PrimitiveTypes.RefFloatArrayParam4(ref fa1, ref fa2, ref fa3, ref fa4);
            PrimitiveTypes.RefFloatArrayParam5(ref fa1, ref fa2, ref fa3, ref fa4, ref fa5);
            PrimitiveTypes.RefFloatArrayParam6(ref fa1, ref fa2, ref fa3, ref fa4, ref fa5, ref fa6);
            PrimitiveTypes.RefFloatArrayParam7(ref fa1, ref fa2, ref fa3, ref fa4, ref fa5, ref fa6, ref fa7);
            PrimitiveTypes.RefFloatArrayParam8(ref fa1, ref fa2, ref fa3, ref fa4, ref fa5, ref fa6, ref fa7, ref fa8);

            AllValues v = new AllValues { X = 4, Y = 2.3f, Z = -1, W = 4.9 };
            UserTypes.AllValuesParam1(v);
            UserTypes.AllValuesParam2(v, v);
            UserTypes.AllValuesParam3(v, v, v);
            UserTypes.AllValuesParam4(v, v, v, v);
            UserTypes.AllValuesParam5(v, v, v, v, v);
            UserTypes.AllValuesParam6(v, v, v, v, v, v);
            UserTypes.AllValuesParam7(v, v, v, v, v, v, v);
            UserTypes.AllValuesParam8(v, v, v, v, v, v, v, v);

            SomeRef r = new SomeRef { Array = new byte[10], C = new UserClass { Blah = 5, Foo = "SDF" }, X = 10, Y = "Hello" };
            UserTypes.SomeRefParam1(r);
            UserTypes.SomeRefParam2(r, r);
            UserTypes.SomeRefParam3(r, r, r);
            UserTypes.SomeRefParam4(r, r, r, r);
            UserTypes.SomeRefParam5(r, r, r, r, r);
            UserTypes.SomeRefParam6(r, r, r, r, r, r);
            UserTypes.SomeRefParam7(r, r, r, r, r, r, r);
            UserTypes.SomeRefParam8(r, r, r, r, r, r, r, r);

            UserTypes.AllValuesRefParam1(ref v);
            UserTypes.AllValuesRefParam2(ref v, ref v);
            UserTypes.AllValuesRefParam3(ref v, ref v, ref v);
            UserTypes.AllValuesRefParam4(ref v, ref v, ref v, ref v);
            UserTypes.AllValuesRefParam5(ref v, ref v, ref v, ref v, ref v);
            UserTypes.AllValuesRefParam6(ref v, ref v, ref v, ref v, ref v, ref v);
            UserTypes.AllValuesRefParam7(ref v, ref v, ref v, ref v, ref v, ref v, ref v);
            UserTypes.AllValuesRefParam8(ref v, ref v, ref v, ref v, ref v, ref v, ref v, ref v);

            UserTypes.SomeRefRefParam1(ref r);
            UserTypes.SomeRefRefParam2(ref r, ref r);
            UserTypes.SomeRefRefParam3(ref r, ref r, ref r);
            UserTypes.SomeRefRefParam4(ref r, ref r, ref r, ref r);
            UserTypes.SomeRefRefParam5(ref r, ref r, ref r, ref r, ref r);
            UserTypes.SomeRefRefParam6(ref r, ref r, ref r, ref r, ref r, ref r);
            UserTypes.SomeRefRefParam7(ref r, ref r, ref r, ref r, ref r, ref r, ref r);
            UserTypes.SomeRefRefParam8(ref r, ref r, ref r, ref r, ref r, ref r, ref r, ref r);

            UserClass c = new UserClass { Blah = -8, Foo = "lolz" };
            UserTypes.UserClassParam1(c);
            UserTypes.UserClassParam2(c, c);
            UserTypes.UserClassParam3(c, c, c);
            UserTypes.UserClassParam4(c, c, c, c);
            UserTypes.UserClassParam5(c, c, c, c, c);
            UserTypes.UserClassParam6(c, c, c, c, c, c);
            UserTypes.UserClassParam7(c, c, c, c, c, c, c);
            UserTypes.UserClassParam8(c, c, c, c, c, c, c, c);

            UserTypes.UserClassRefParam1(ref c);
            UserTypes.UserClassRefParam2(ref c, ref c);
            UserTypes.UserClassRefParam3(ref c, ref c, ref c);
            UserTypes.UserClassRefParam4(ref c, ref c, ref c, ref c);
            UserTypes.UserClassRefParam5(ref c, ref c, ref c, ref c, ref c);
            UserTypes.UserClassRefParam6(ref c, ref c, ref c, ref c, ref c, ref c);
            UserTypes.UserClassRefParam7(ref c, ref c, ref c, ref c, ref c, ref c, ref c);
            UserTypes.UserClassRefParam8(ref c, ref c, ref c, ref c, ref c, ref c, ref c, ref c);

            ReturnValues.ByteReturn();
            ReturnValues.IntReturn();
            ReturnValues.FloatReturn();
            ReturnValues.DecimalReturn();
            ReturnValues.StringReturn();
            ReturnValues.IntArrayReturn();
            ReturnValues.FloatArrayReturn();
            ReturnValues.DecimalArrayReturn();
            ReturnValues.StringArrayReturn();
            ReturnValues.IntReturnWithIntRef(ref i1);
            ReturnValues.IntReturnWithFloatRef(ref f1);
            ReturnValues.IntReturnWithStringRef(ref s1);
            ReturnValues.IntArrayReturnWithIntRef(ref i1); 
            ReturnValues.FloatReturnWithIntRef(ref i1);
            ReturnValues.FloatReturnWithFloatRef(ref f1);
            ReturnValues.FloatReturnWithStringRef(ref s1); 
            ReturnValues.FloatArrayReturnWithIntRef(ref i1);
            ReturnValues.StringReturnWithIntRef(ref i1);
            ReturnValues.StringReturnWithFloatRef(ref f1); 
            ReturnValues.StringReturnWithStringRef(ref s1);
            ReturnValues.StringArrayReturnWithIntRef(ref i1);
            ReturnValues.AllValuesReturn();
            ReturnValues.SomeRefReturn();
            ReturnValues.UserClassReturn();
            ReturnValues.AllValuesArrayReturn();
            ReturnValues.SomeRefArrayReturn();
            ReturnValues.UserClassArrayReturn();
            ReturnValues.AllValuesReturnWithIntRef(ref i1);
            ReturnValues.AllValuesReturnWithStringRef(ref s1);
            ReturnValues.AllValuesArrayReturnWithIntRef(ref i1);
            ReturnValues.SomeRefReturnWithIntRef(ref i1);
            ReturnValues.SomeRefReturnWithStringRef(ref s1);
            ReturnValues.SomeRefArrayReturnWithIntRef(ref i1);
            ReturnValues.UserClassReturnWithIntRef(ref i1);
            ReturnValues.UserClassReturnWithStringRef(ref s1);
            ReturnValues.UserClassArrayReturnWithIntRef(ref i1);
        }
    }

    class UserClass
    {
        public int Blah;
        public string Foo;
    }

    struct AllValues
    {
        public int X;
        public float Y;
        public int Z;
        public double W;
    }

    struct SomeRef
    {
        public int X;
        public string Y;
        public UserClass C;
        public byte[] Array;
    }

    static class PrimitiveTypes
    {
        [MethodImpl(MethodImplOptions.NoInlining)] public static void NoParams() { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void ByteParam1(byte a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void ByteParam2(byte a, byte b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void ByteParam3(byte a, byte b, byte c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void ByteParam4(byte a, byte b, byte c, byte d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void ByteParam5(byte a, byte b, byte c, byte d, byte e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void ByteParam6(byte a, byte b, byte c, byte d, byte e, byte f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void ByteParam7(byte a, byte b, byte c, byte d, byte e, byte f, byte g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void ByteParam8(byte a, byte b, byte c, byte d, byte e, byte f, byte g, byte h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntParam1(int a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntParam2(int a, int b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntParam3(int a, int b, int c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntParam4(int a, int b, int c, int d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntParam5(int a, int b, int c, int d, int e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntParam6(int a, int b, int c, int d, int e, int f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntParam7(int a, int b, int c, int d, int e, int f, int g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntParam8(int a, int b, int c, int d, int e, int f, int g, int h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatParam1(float a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatParam2(float a, float b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatParam3(float a, float b, float c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatParam4(float a, float b, float c, float d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatParam5(float a, float b, float c, float d, float e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatParam6(float a, float b, float c, float d, float e, float f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatParam7(float a, float b, float c, float d, float e, float f, float g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatParam8(float a, float b, float c, float d, float e, float f, float g, float h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void DecimalParam1(decimal a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void DecimalParam2(decimal a, decimal b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void DecimalParam3(decimal a, decimal b, decimal c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void DecimalParam4(decimal a, decimal b, decimal c, decimal d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void DecimalParam5(decimal a, decimal b, decimal c, decimal d, decimal e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void DecimalParam6(decimal a, decimal b, decimal c, decimal d, decimal e, decimal f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void DecimalParam7(decimal a, decimal b, decimal c, decimal d, decimal e, decimal f, decimal g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void DecimalParam8(decimal a, decimal b, decimal c, decimal d, decimal e, decimal f, decimal g, decimal h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntRefParam1(ref int a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntRefParam2(ref int a, ref int b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntRefParam3(ref int a, ref int b, ref int c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntRefParam4(ref int a, ref int b, ref int c, ref int d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntRefParam5(ref int a, ref int b, ref int c, ref int d, ref int e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntRefParam6(ref int a, ref int b, ref int c, ref int d, ref int e, ref int f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntRefParam7(ref int a, ref int b, ref int c, ref int d, ref int e, ref int f, ref int g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntRefParam8(ref int a, ref int b, ref int c, ref int d, ref int e, ref int f, ref int g, ref int h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatParam1(ref float a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatParam2(ref float a, ref float b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatParam3(ref float a, ref float b, ref float c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatParam4(ref float a, ref float b, ref float c, ref float d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatParam5(ref float a, ref float b, ref float c, ref float d, ref float e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatParam6(ref float a, ref float b, ref float c, ref float d, ref float e, ref float f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatParam7(ref float a, ref float b, ref float c, ref float d, ref float e, ref float f, ref float g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatParam8(ref float a, ref float b, ref float c, ref float d, ref float e, ref float f, ref float g, ref float h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void StringParam1(string a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void StringParam2(string a, string b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void StringParam3(string a, string b, string c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void StringParam4(string a, string b, string c, string d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void StringParam5(string a, string b, string c, string d, string e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void StringParam6(string a, string b, string c, string d, string e, string f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void StringParam7(string a, string b, string c, string d, string e, string f, string g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void StringParam8(string a, string b, string c, string d, string e, string f, string g, string h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefStringParam1(ref string a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefStringParam2(ref string a, ref string b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefStringParam3(ref string a, ref string b, ref string c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefStringParam4(ref string a, ref string b, ref string c, ref string d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefStringParam5(ref string a, ref string b, ref string c, ref string d, ref string e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefStringParam6(ref string a, ref string b, ref string c, ref string d, ref string e, ref string f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefStringParam7(ref string a, ref string b, ref string c, ref string d, ref string e, ref string f, ref string g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefStringParam8(ref string a, ref string b, ref string c, ref string d, ref string e, ref string f, ref string g, ref string h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntArrayParam1(int[] a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntArrayParam2(int[] a, int[] b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntArrayParam3(int[] a, int[] b, int[] c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntArrayParam4(int[] a, int[] b, int[] c, int[] d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntArrayParam5(int[] a, int[] b, int[] c, int[] d, int[] e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntArrayParam6(int[] a, int[] b, int[] c, int[] d, int[] e, int[] f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntArrayParam7(int[] a, int[] b, int[] c, int[] d, int[] e, int[] f, int[] g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void IntArrayParam8(int[] a, int[] b, int[] c, int[] d, int[] e, int[] f, int[] g, int[] h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefIntArrayParam1(ref int[] a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefIntArrayParam2(ref int[] a, ref int[] b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefIntArrayParam3(ref int[] a, ref int[] b, ref int[] c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefIntArrayParam4(ref int[] a, ref int[] b, ref int[] c, ref int[] d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefIntArrayParam5(ref int[] a, ref int[] b, ref int[] c, ref int[] d, ref int[] e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefIntArrayParam6(ref int[] a, ref int[] b, ref int[] c, ref int[] d, ref int[] e, ref int[] f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefIntArrayParam7(ref int[] a, ref int[] b, ref int[] c, ref int[] d, ref int[] e, ref int[] f, ref int[] g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefIntArrayParam8(ref int[] a, ref int[] b, ref int[] c, ref int[] d, ref int[] e, ref int[] f, ref int[] g, ref int[] h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatArrayParam1(float[] a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatArrayParam2(float[] a, float[] b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatArrayParam3(float[] a, float[] b, float[] c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatArrayParam4(float[] a, float[] b, float[] c, float[] d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatArrayParam5(float[] a, float[] b, float[] c, float[] d, float[] e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatArrayParam6(float[] a, float[] b, float[] c, float[] d, float[] e, float[] f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatArrayParam7(float[] a, float[] b, float[] c, float[] d, float[] e, float[] f, float[] g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void FloatArrayParam8(float[] a, float[] b, float[] c, float[] d, float[] e, float[] f, float[] g, float[] h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatArrayParam1(ref float[] a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatArrayParam2(ref float[] a, ref float[] b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatArrayParam3(ref float[] a, ref float[] b, ref float[] c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatArrayParam4(ref float[] a, ref float[] b, ref float[] c, ref float[] d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatArrayParam5(ref float[] a, ref float[] b, ref float[] c, ref float[] d, ref float[] e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatArrayParam6(ref float[] a, ref float[] b, ref float[] c, ref float[] d, ref float[] e, ref float[] f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatArrayParam7(ref float[] a, ref float[] b, ref float[] c, ref float[] d, ref float[] e, ref float[] f, ref float[] g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void RefFloatArrayParam8(ref float[] a, ref float[] b, ref float[] c, ref float[] d, ref float[] e, ref float[] f, ref float[] g, ref float[] h) { }
    }

    static class UserTypes
    {
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesParam1(AllValues a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesParam2(AllValues a, AllValues b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesParam3(AllValues a, AllValues b, AllValues c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesParam4(AllValues a, AllValues b, AllValues c, AllValues d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesParam5(AllValues a, AllValues b, AllValues c, AllValues d, AllValues e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesParam6(AllValues a, AllValues b, AllValues c, AllValues d, AllValues e, AllValues f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesParam7(AllValues a, AllValues b, AllValues c, AllValues d, AllValues e, AllValues f, AllValues g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesParam8(AllValues a, AllValues b, AllValues c, AllValues d, AllValues e, AllValues f, AllValues g, AllValues h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefParam1(SomeRef a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefParam2(SomeRef a, SomeRef b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefParam3(SomeRef a, SomeRef b, SomeRef c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefParam4(SomeRef a, SomeRef b, SomeRef c, SomeRef d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefParam5(SomeRef a, SomeRef b, SomeRef c, SomeRef d, SomeRef e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefParam6(SomeRef a, SomeRef b, SomeRef c, SomeRef d, SomeRef e, SomeRef f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefParam7(SomeRef a, SomeRef b, SomeRef c, SomeRef d, SomeRef e, SomeRef f, SomeRef g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefParam8(SomeRef a, SomeRef b, SomeRef c, SomeRef d, SomeRef e, SomeRef f, SomeRef g, SomeRef h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesRefParam1(ref AllValues a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesRefParam2(ref AllValues a, ref AllValues b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesRefParam3(ref AllValues a, ref AllValues b, ref AllValues c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesRefParam4(ref AllValues a, ref AllValues b, ref AllValues c, ref AllValues d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesRefParam5(ref AllValues a, ref AllValues b, ref AllValues c, ref AllValues d, ref AllValues e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesRefParam6(ref AllValues a, ref AllValues b, ref AllValues c, ref AllValues d, ref AllValues e, ref AllValues f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesRefParam7(ref AllValues a, ref AllValues b, ref AllValues c, ref AllValues d, ref AllValues e, ref AllValues f, ref AllValues g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void AllValuesRefParam8(ref AllValues a, ref AllValues b, ref AllValues c, ref AllValues d, ref AllValues e, ref AllValues f, ref AllValues g, ref AllValues h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefRefParam1(ref SomeRef a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefRefParam2(ref SomeRef a, ref SomeRef b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefRefParam3(ref SomeRef a, ref SomeRef b, ref SomeRef c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefRefParam4(ref SomeRef a, ref SomeRef b, ref SomeRef c, ref SomeRef d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefRefParam5(ref SomeRef a, ref SomeRef b, ref SomeRef c, ref SomeRef d, ref SomeRef e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefRefParam6(ref SomeRef a, ref SomeRef b, ref SomeRef c, ref SomeRef d, ref SomeRef e, ref SomeRef f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefRefParam7(ref SomeRef a, ref SomeRef b, ref SomeRef c, ref SomeRef d, ref SomeRef e, ref SomeRef f, ref SomeRef g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void SomeRefRefParam8(ref SomeRef a, ref SomeRef b, ref SomeRef c, ref SomeRef d, ref SomeRef e, ref SomeRef f, ref SomeRef g, ref SomeRef h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassParam1(UserClass a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassParam2(UserClass a, UserClass b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassParam3(UserClass a, UserClass b, UserClass c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassParam4(UserClass a, UserClass b, UserClass c, UserClass d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassParam5(UserClass a, UserClass b, UserClass c, UserClass d, UserClass e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassParam6(UserClass a, UserClass b, UserClass c, UserClass d, UserClass e, UserClass f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassParam7(UserClass a, UserClass b, UserClass c, UserClass d, UserClass e, UserClass f, UserClass g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassParam8(UserClass a, UserClass b, UserClass c, UserClass d, UserClass e, UserClass f, UserClass g, UserClass h) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassRefParam1(ref UserClass a) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassRefParam2(ref UserClass a, ref UserClass b) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassRefParam3(ref UserClass a, ref UserClass b, ref UserClass c) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassRefParam4(ref UserClass a, ref UserClass b, ref UserClass c, ref UserClass d) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassRefParam5(ref UserClass a, ref UserClass b, ref UserClass c, ref UserClass d, ref UserClass e) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassRefParam6(ref UserClass a, ref UserClass b, ref UserClass c, ref UserClass d, ref UserClass e, ref UserClass f) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassRefParam7(ref UserClass a, ref UserClass b, ref UserClass c, ref UserClass d, ref UserClass e, ref UserClass f, ref UserClass g) { }
        [MethodImpl(MethodImplOptions.NoInlining)] public static void UserClassRefParam8(ref UserClass a, ref UserClass b, ref UserClass c, ref UserClass d, ref UserClass e, ref UserClass f, ref UserClass g, ref UserClass h) { }
    }

    static class ReturnValues
    {
        [MethodImpl(MethodImplOptions.NoInlining)] public static byte ByteReturn() { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static int IntReturn() { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static float FloatReturn() { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static decimal DecimalReturn() { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static string StringReturn() { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static int[] IntArrayReturn() { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static float[] FloatArrayReturn() { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static decimal[] DecimalArrayReturn() { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static string[] StringArrayReturn() { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static int IntReturnWithIntRef(ref int a) { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static int IntReturnWithFloatRef(ref float a) { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static int IntReturnWithStringRef(ref string a) { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static int[] IntArrayReturnWithIntRef(ref int a) { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static float FloatReturnWithIntRef(ref int a) { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static float FloatReturnWithFloatRef(ref float a) { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static float FloatReturnWithStringRef(ref string a) { return 0; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static float[] FloatArrayReturnWithIntRef(ref int a) { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static string StringReturnWithIntRef(ref int a) { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static string StringReturnWithFloatRef(ref float a) { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static string StringReturnWithStringRef(ref string a) { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static string[] StringArrayReturnWithIntRef(ref int a) { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static AllValues AllValuesReturn() { return new AllValues(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static SomeRef SomeRefReturn() { return new SomeRef(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static UserClass UserClassReturn() { return new UserClass(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static AllValues[] AllValuesArrayReturn() { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static SomeRef[] SomeRefArrayReturn() { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static UserClass[] UserClassArrayReturn() { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static AllValues AllValuesReturnWithIntRef(ref int a) { return new AllValues(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static AllValues AllValuesReturnWithStringRef(ref string a) { return new AllValues(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static AllValues[] AllValuesArrayReturnWithIntRef(ref int a) { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static SomeRef SomeRefReturnWithIntRef(ref int a) { return new SomeRef(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static SomeRef SomeRefReturnWithStringRef(ref string a) { return new SomeRef(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static SomeRef[] SomeRefArrayReturnWithIntRef(ref int a) { return null; }
        [MethodImpl(MethodImplOptions.NoInlining)] public static UserClass UserClassReturnWithIntRef(ref int a) { return new UserClass(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static UserClass UserClassReturnWithStringRef(ref string a) { return new UserClass(); }
        [MethodImpl(MethodImplOptions.NoInlining)] public static UserClass[] UserClassArrayReturnWithIntRef(ref int a) { return null; }
    }
}
