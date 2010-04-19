/*
* Copyright (c) 2007-2010 SlimGen Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.IO;

namespace SlimGen
{
    public enum Platform
    {
        X86,
        X64
    }

    public class MethodReplacement
    {
        public MethodBase Method
        {
            get;
            private set;
        }

        public Platform Platform
        {
            get;
            private set;
        }

        public InstructionSets InstructionSet
        {
            get;
            private set;
        }

        public byte[][] CompiledData
        {
            get;
            private set;
        }

        public MethodReplacement(MethodBase method, Platform platform, InstructionSets instructionSet, byte[][] compiledData)
        {
            if (method == null)
                throw new ArgumentNullException("method");
            if (compiledData == null || compiledData.Length == 0)
                throw new ArgumentNullException("compiledData");

            foreach (var chunk in compiledData)
            {
                if (chunk == null || chunk.Length == 0)
                    throw new ArgumentException("Data chunk is null or empty.");
            }

            Method = method;
            Platform = platform;
            InstructionSet = instructionSet;
            CompiledData = compiledData;
        }

        public void Write(StreamWriter writer)
        {
            writer.WriteLine(Method.DeclaringType.Assembly.FullName);
            writer.WriteLine(GetMethodSignature(Method));
            writer.WriteLine(CompiledData.Length);

            foreach (var chunk in CompiledData)
            {
                writer.WriteLine(chunk.Length);
                writer.BaseStream.Write(chunk, 0, chunk.Length);
            }
        }

        static string GetMethodSignature(MethodBase method)
        {
            var builder = new StringBuilder();
            builder.Append(method.Name);
            builder.Append("(");

            var parameters = method.GetParameters();
            foreach (var parameter in parameters)
            {
                if (parameter.IsOut)
                    builder.Append("ref ");

                builder.Append(parameter.ParameterType.FullName);
                builder.Append(", ");
            }

            if (parameters.Length != 0)
                builder.Length -= 2;

            builder.Append(")");
            return builder.ToString();
        }
    }
}
