#ifndef VERTEXUV_H
#define VERTEXUV_H
using namespace std;

#include "ImportExport.h"
#include <d3d9.h>

struct LQN_API VertexUV {
	FLOAT x, y, z;
	FLOAT u, v;
	static const DWORD fvf = D3DFVF_XYZ | D3DFVF_TEX1;
};

#endif