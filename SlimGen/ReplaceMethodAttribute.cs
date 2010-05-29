using System;
using System.Collections.Generic;
using System.Text;

namespace SlimGen
{
    [AttributeUsage(AttributeTargets.Method, AllowMultiple = true, Inherited = false)]
    public class ReplaceMethodAttribute : Attribute
    {
        public string[] DataFiles { get; set; }
        public InstructionSets InstructionSet { get; set; }
        public Platform Platform { get; set; }
    }
}
