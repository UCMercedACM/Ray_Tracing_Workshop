#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

struct Material
{
	float roughness;
	float metal;
	float emission = 1.0f;
	float b;
	glm::vec4 albedo;
	// glm::vec3 emission;
	// float emission_strength;
};

class MaterialLoader
{
	Material* curr_material = NULL;

	Material* createMaterial(std::vector<Material>* materials)
	{
		materials->emplace_back(Material());
		return &(*materials)[materials->size() - 1];
	}

public:
	MaterialLoader()
	{

	}
	~MaterialLoader()
	{

	}

	void loadMaterials(const std::string& path, std::vector<Material>* materials, std::vector<std::string>* material_names)
	{
		std::string text;
		std::ifstream file("../source/" + path);

		while (std::getline(file, text))
		{
			unsigned int token_length = 0;
			std::string tokens[10];

			std::stringstream ss(text);
			while (ss >> tokens[token_length])
			{
				token_length++;
			}

			if (tokens[0] == "newmtl")
			{
				curr_material = createMaterial(materials);
				material_names->push_back(tokens[1]);
			}
			else if (tokens[0] == "Kd")
			{
				float r = std::stof(tokens[1]);
				float g = std::stof(tokens[2]);
				float b = std::stof(tokens[3]);
				curr_material->albedo = glm::vec4(r, g, b, 1.0f);
			}
		}
	}
};
