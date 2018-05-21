#include "../includes/ObjImporter.h"

//string LogFile::m_filePath = "DefaultLog.txt";
//ofstream LogFile::fout;

struct VertexId {
	int vId;
	int uvId;
	int normalId;
};

bool ObjImporter::LoadOBJ(
	const char * path,
	std::vector < VertexUV > ** out_vertices,
	std::vector < short > ** out_indices) {

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< D3DXVECTOR3 > temp_vertices;
	std::vector< D3DXVECTOR2 > temp_uvs;
	std::vector< D3DXVECTOR3 > temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1) {

		char lineHeader[128];
		// Lee la primera palabra de la línea
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File, es decir, el final del archivo. Se finaliza el ciclo.

				   // else : analizar el lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			D3DXVECTOR3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);

		}
		else if (strcmp(lineHeader, "vt") == 0) {
			D3DXVECTOR2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);

		}
		else if (strcmp(lineHeader, "vn") == 0) {
			D3DXVECTOR3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);

		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

	}
	vector<VertexId> vertexIds;
	(*out_indices)  = new vector<short>();
	
	for (size_t i = 0; i < uvIndices.size(); i++)
	{
		//id will be used as a flag in case that the vertex isn't inserted, if the vertex 
		//was inserted before, id will have the value of that 
		int id = -1;
		int vertexIndex, uvIndex, normalIndex;
		vertexIndex = vertexIndices[i];
		uvIndex = uvIndices[i];
		normalIndex = normalIndices[i];
		for (size_t j = 0; j < vertexIds.size(); j++)
		{
			if (vertexIds[j].vId == vertexIndex&&
				vertexIds[j].uvId == uvIndex&&
				vertexIds[j].normalId == normalIndex) {
				id = j;
				break;
			}
		}
		if (id == -1) {
			VertexId vertexToInsert;
			vertexToInsert.vId = vertexIndex;
			vertexToInsert.uvId = uvIndex;
			vertexToInsert.normalId = normalIndex;

			vertexIds.push_back(vertexToInsert);
			id = vertexIds.size() - 1;

		}
		(*out_indices)->push_back(id);
	}
	(*out_vertices) = new vector<VertexUV>();

	for (size_t i = 0; i < vertexIds.size(); i++)
	{
		int vertexIndex, uvIndex, normalIndex;
		vertexIndex = vertexIds[i].vId;
		uvIndex = vertexIds[i].uvId;
		normalIndex = vertexIds[i].normalId;
		VertexUV vertexUV(temp_vertices[vertexIndex - 1].x,
			temp_vertices[vertexIndex - 1].y,
			temp_vertices[vertexIndex - 1].z,
			temp_uvs[uvIndex - 1].x,
			temp_uvs[uvIndex - 1].y,
			temp_normals[normalIndex - 1].x,
			temp_normals[normalIndex - 1].y,
			temp_normals[normalIndex - 1].z);
		(*out_vertices)->push_back(vertexUV);
	}
	return true;
}
