#ifndef VERTEX_H
#define VERTEX_H
using namespace std;

#include "ImportExport.h"
#include <Windows.h>
#include <d3d9.h>

struct LQN_API Vertex {
	FLOAT x, y, z,rhw;
	DWORD color;    // from the D3DFVF_DIFFUSE flag
	static const DWORD fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};

#endif