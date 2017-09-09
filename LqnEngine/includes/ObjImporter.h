#ifndef OBJIMPORTER_H
#define OBJIMPORTER_H
#include "ImportExport.h"
#include <vector>
#include <fstream>
#include "VertexUV.h"

#include <d3dx9.h>
#pragma comment (lib,"d3dx9.lib")
class LQN_API ObjImporter {
public:
	static bool LoadOBJ(
		const char * path,
		std::vector < VertexUV > ** out_vertices,
		std::vector < short > ** out_indices);
};
#endif