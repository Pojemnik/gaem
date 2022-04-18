#include "model.h"

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
				_indices.vertex.push_back(idx.vertex_index);
				_indices.normal.push_back(idx.normal_index);
				_indices.tex.push_back(idx.texcoord_index);

				tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
				_vertices.push_back(glm::vec3(vx, vy, vz));

				if (idx.normal_index >= 0)
				{
					tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
					tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
					tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
					_normal.push_back(glm::vec3(nx, ny, nz));
				}

				if (idx.texcoord_index >= 0)
				{
					tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
					_texcoord.push_back(glm::vec2(tx, ty));
				}
			}
			index_offset += fv;
		}
	}
}
