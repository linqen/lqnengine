#ifndef VERTEXUV_H
#define VERTEXUV_H
using namespace std;

#include "ImportExport.h"
//#include <Windows.h>
#include <d3d9.h>

struct LQN_API VertexUV {
	FLOAT x, y, z, rhw;
	FLOAT u, v;
	static const DWORD fvf = D3DFVF_XYZRHW | D3DFVF_TEX1;

	VertexUV(float px,float py,float pz,float pu, float pv) {
		x = px;
		y = py;
		z = pz;
		u = pu;
		v = pv;
		rhw = 1.0f;
	}
};

#endif