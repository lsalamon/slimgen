using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace SlimMath {
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector {
        public float X, Y, Z, W;
    }
}
