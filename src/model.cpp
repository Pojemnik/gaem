#include "model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Model::Model(std::string path)
{
	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = "./";

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(path, reader_config))
	{
		if (!reader.Error().empty())
		{
			std::cerr << "Object loading error: " << reader.Error();
		}
		exit(1);
	}

	if (!reader.Warning().empty())
	{
		std::cout << "Object loading error: " << reader.Warning();
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	for (size_t s = 0; s < shapes.size(); s++) {
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

			for (size_t v = 0; v < fv; v++) {
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
				_vertices.push_back(vx);
				_vertices.push_back(vy);
				_vertices.push_back(vz);
				_vertices.push_back(1);

				if (idx.normal_index >= 0)
				{
					tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
					tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
					tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
					_normals.push_back(nx);
					_normals.push_back(ny);
					_normals.push_back(nz);
				}

				if (idx.texcoord_index >= 0)
				{
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
					_texcoords.push_back(tx);
					_texcoords.push_back(ty);
				}
			}
			index_offset += fv;
		}
	}
	_verticesSize = _vertices.size() / 4;
	_normalsSize = _normals.size() / 3;
	_texcoordsSize = _texcoords.size() / 2;
}

const std::vector<float>& Model::getVertices() const
{
	return _vertices;
}

const std::vector<float>& Model::getNormals() const
{
	return _normals;
}

const int Model::getVerticesSize() const
{
	return _verticesSize;
}

const int Model::getNormalsSize() const
{
	return _normalsSize;
}

const int Model::getTexCoordsSize() const
{
	return _texcoordsSize;
}
