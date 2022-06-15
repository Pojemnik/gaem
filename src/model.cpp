#include "model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Model::Model(std::string path)
{
	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = "./";

	tinyobj::ObjReader reader;
	_data[BufferType::VERTEX] = std::vector<float>();
	_data[BufferType::NORMAL] = std::vector<float>();
	_data[BufferType::TEXCOORD] = std::vector<float>();

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

	for (size_t s = 0; s < shapes.size(); s++) {
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

			for (size_t v = 0; v < fv; v++) {
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
				_data[BufferType::VERTEX].push_back(vx);
				_data[BufferType::VERTEX].push_back(vy);
				_data[BufferType::VERTEX].push_back(vz);
				_data[BufferType::VERTEX].push_back(1);

				if (idx.normal_index >= 0)
				{
					tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
					tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
					tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
					_data[BufferType::NORMAL].push_back(nx);
					_data[BufferType::NORMAL].push_back(ny);
					_data[BufferType::NORMAL].push_back(nz);
				}

				if (idx.texcoord_index >= 0)
				{
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
					_data[BufferType::TEXCOORD].push_back(tx);
					_data[BufferType::TEXCOORD].push_back(ty);
				}
			}
			index_offset += fv;
		}
	}
	_sizes.insert({ BufferType::VERTEX, 4 });
	_sizes.insert({ BufferType::NORMAL, 3 });
	_sizes.insert({ BufferType::TEXCOORD, 2 });
}

const std::vector<float>& Model::getVector(BufferType type) const
{
	return _data.at(type);
}

int Model::getSize(BufferType type) const
{
	return _sizes.at(type);
}

int Model::getLength(BufferType type) const
{
	return getVector(type).size();
}
