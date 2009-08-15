/*
* Copyright (c) 2007-2009 SlimGen Group
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
using System.Xml.Serialization;
using System.Collections.Generic;

namespace SlimGen
{
    [Serializable]
    public enum PlatformSpecifier
    {
        X86,
        X64
    }

    [Serializable]
    public enum InstructionSetSpecifier
    {
        Default,
        MMX,
        SSE,
        SSE2,
        SSE3,
        SSSE3,
        SSE41,
        SSE42
    }

    [Serializable]
    public class Platform
    {
        [XmlAttribute("type")]
        public PlatformSpecifier Type;

        [XmlElement("method")]
        public List<Method> Methods;

        public Platform(PlatformSpecifier type)
        {
            Type = type;
            Methods = new List<Method>();
        }

        Platform()
        {
        }
    }

    [Serializable]
    public class Method
    {
        [XmlAttribute("name")]
        public string Name;

        [XmlAttribute("token")]
        public string Signature;

        [XmlElement("instructionSet")]
        public List<InstructionSet> InstructionSets;

        public Method(string name, string signature)
        {
            Name = name;
            Signature = signature;

            InstructionSets = new List<InstructionSet>();
        }

        Method()
        {
        }
    }

    [Serializable]
    public class InstructionSet
    {
        [XmlAttribute("type")]
        public InstructionSetSpecifier Type;

        [XmlAttribute("chunkCount")]
        public int ChunkCount;

        [XmlElement("codeChunk")]
        public List<CodeChunk> CodeChunks;
    }

    [Serializable]
    public class CodeChunk
    {
        [XmlAttribute("filename")]
        public string FileName;
    }
}
