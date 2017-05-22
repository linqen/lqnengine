#ifndef VERTEX_H
#define VERTEX_H
using namespace std;

#include "ImportExport.h"
#include <d3d9.h>

struct LQN_API Vertex {
	FLOAT x, y, z;
	DWORD color;    // from the D3DFVF_DIFFUSE flag
	static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

#endif