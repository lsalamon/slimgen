namespace SlimGen {
	struct CPUFeatureSupport {
		bool MMX;
		bool SSE;
		bool SSE2;
		bool SSE3;
		bool SSSE3;
		bool SSE41;
		bool SSE42;
		bool SSE4A;

		bool FromName(std::wstring const& name);
	};

	int ValueFromName(std::wstring const& name);
	CPUFeatureSupport GetMaxCPUFeatureSupported();
}