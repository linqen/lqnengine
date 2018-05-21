#ifndef VERTEXUV_H
#define VERTEXUV_H
using namespace std;

#include "ImportExport.h"
#include <d3d9.h>

struct LQN_API VertexUV {
	float x, y, z = 0;
	float nx, ny, nz = 0;
	DWORD color= D3DCOLOR_ARGB(255,255, 255, 255);
	float u, v = 0;

	static const DWORD fvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;

public :
	VertexUV() {}
	VertexUV(float rX, float rY, float rZ, float rNx, float rNy, float rNz, float rU, float rV) {
		x = rX;
		y = rY;
		z = rZ;
		nx = rNx;
		ny = rNy;
		nz = rNz;
		u = rU;
		v = rV;
	}

	void setCoordinates(float rX, float rY, float rZ) {
		x = rX;
		y = rY;
		z = rZ;
	}

	void setUV(float rU, float rV) {
		u = rU;
		v = rV;
	}

	void setNormals(float rNx, float rNy, float rNz) {
		nx = rNx;
		ny = rNy;
		nz = rNz;
	}
};

#endif