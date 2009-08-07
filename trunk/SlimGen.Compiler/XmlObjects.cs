using System;
using System.Xml.Serialization;

namespace SlimGen.Compiler {
	[Serializable]
	public enum PlatformSpecifier : int {
		X86,
		X64
	}
	[Serializable]
	public enum InstructionSetSpecifier : int {
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
	[XmlType("slimgen.build")]
	public class Build {
		[XmlElement("platform")]
		public Platform[] Platforms;
	}

	[Serializable]
	public class Platform {
		[XmlAttribute("type")]
		public PlatformSpecifier Type;
		[XmlElement("method")]
		public Method[] Methods;
	}

	[Serializable]
	public class Method {
		[XmlAttribute("name")]
		public string Name;
		[XmlAttribute("token")]
		public int TokenId;
		[XmlElement("instructionSet")]
		public InstructionSet[] InstructionSets;
	}

	[Serializable]
	public class InstructionSet {
		[XmlAttribute("type")]
		public InstructionSetSpecifier Type;
		[XmlAttribute("chunkCount")]
		public int ChunkCount;
		[XmlElement("codeChunk")]
		public CodeChunk[] CodeChunks;
	}

	[Serializable]
	public class CodeChunk {
		[XmlAttribute("filename")]
		public string FileName;
	}
}
