#include <iostream>
#include <windows.h>
#include <xnamath.h>
#include <cstdlib>
#include <locale>
#include <iterator>

const int MatrixCount = 100000;
const int TestCount = 100;

void FillWithRandom(XMMATRIX* ptr) {
	for(int i = 0; i < MatrixCount; ++i) {
		ptr[i]._11 = rand() / (float)RAND_MAX;
		ptr[i]._12 = rand() / (float)RAND_MAX;
		ptr[i]._13 = rand() / (float)RAND_MAX;
		ptr[i]._14 = rand() / (float)RAND_MAX;

		ptr[i]._21 = rand() / (float)RAND_MAX;
		ptr[i]._22 = rand() / (float)RAND_MAX;
		ptr[i]._23 = rand() / (float)RAND_MAX;
		ptr[i]._24 = rand() / (float)RAND_MAX;

		ptr[i]._31 = rand() / (float)RAND_MAX;
		ptr[i]._32 = rand() / (float)RAND_MAX;
		ptr[i]._33 = rand() / (float)RAND_MAX;
		ptr[i]._34 = rand() / (float)RAND_MAX;

		ptr[i]._41 = rand() / (float)RAND_MAX;
		ptr[i]._42 = rand() / (float)RAND_MAX;
		ptr[i]._43 = rand() / (float)RAND_MAX;
		ptr[i]._44 = rand() / (float)RAND_MAX;
	}
}

int main() {
	XMMATRIX* left = new XMMATRIX[MatrixCount];
	XMMATRIX* right = new XMMATRIX[MatrixCount];
	XMMATRIX* dest = new XMMATRIX[MatrixCount];

	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
	LARGE_INTEGER sum = {};
	QueryPerformanceFrequency(&freq);
	FillWithRandom(left);
	FillWithRandom(right);

	
	for(int i = 0; i < TestCount; ++i) {
		QueryPerformanceCounter(&start);
		for(int j = 0; j < MatrixCount; ++j) {
			dest[j] = XMMatrixMultiply(left[j], right[j]);
		}
		QueryPerformanceCounter(&stop);
		sum.QuadPart += (stop.QuadPart - start.QuadPart);
		std::cout<<"Tick count: "<<(stop.QuadPart - start.QuadPart)<<std::endl;
	}

	std::cout<<"Total tick count: "<<sum.QuadPart<<std::endl;
	delete [] left;
	delete [] right;
	delete [] dest;
}