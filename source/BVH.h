#pragma once

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>

#include "Scene.h"

struct BVHPrimitive
{
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 centroid;
	int index; // index into primitives array
};
struct BVHNode
{
	glm::vec3 min;
	glm::vec3 max;
	BVHNode* left;
	BVHNode* right;
	int split_axis;
	int prim_start;
	int prim_count;

	void initLeaf(int start, int count, glm::vec3& min, glm::vec3& max)
	{
		prim_start = start;
		prim_count = count;
		this->min = min;
		this->max = max;
		left = nullptr;
		right = nullptr;
	}
	void initInterior(int axis, BVHNode* left, BVHNode* right)
	{
		this->left = left;
		this->right = right;
		min = glm::vec3(
			glm::min(left->min.x, right->min.x),
			glm::min(left->min.y, right->min.y),
			glm::min(left->min.z, right->min.z)
		);
		max = glm::vec3(
			glm::max(left->max.x, right->max.x),
			glm::max(left->max.y, right->max.y),
			glm::max(left->max.z, right->max.z)
		);
		split_axis = axis;
		prim_count = 0;
	}
	~BVHNode()
	{
		if(left != NULL)
			delete(left);
		if(right != NULL)
			delete(right);
	}
};

enum BVHSplitMode
{
	MIDPOINT,
	EQUAL_COUNTS
};

struct BVH
{
	Scene* scene;

	BVHSplitMode mode;

	bool is_built;

	void computeAABB(BVHPrimitive& primitive)
	{
		glm::vec3 min = glm::vec3(99999.9f);
		glm::vec3 max = glm::vec3(-99999.9f);

		glm::vec3 vertex = scene->scene_data.vertices[scene->primitives[primitive.index].vertex_a];
		min.x = glm::min(min.x, vertex.x);
		min.y = glm::min(min.y, vertex.y);
		min.z = glm::min(min.z, vertex.z);
		max.x = glm::max(max.x, vertex.x);
		max.y = glm::max(max.y, vertex.y);
		max.z = glm::max(max.z, vertex.z);

		vertex = scene->scene_data.vertices[scene->primitives[primitive.index].vertex_b];
		min.x = glm::min(min.x, vertex.x);
		min.y = glm::min(min.y, vertex.y);
		min.z = glm::min(min.z, vertex.z);
		max.x = glm::max(max.x, vertex.x);
		max.y = glm::max(max.y, vertex.y);
		max.z = glm::max(max.z, vertex.z);

		vertex = scene->scene_data.vertices[scene->primitives[primitive.index].vertex_c];
		min.x = glm::min(min.x, vertex.x);
		min.y = glm::min(min.y, vertex.y);
		min.z = glm::min(min.z, vertex.z);
		max.x = glm::max(max.x, vertex.x);
		max.y = glm::max(max.y, vertex.y);
		max.z = glm::max(max.z, vertex.z);

		primitive.min = min;
		primitive.max = max;
	}

public:
	BVH(Scene* scene) : scene(scene), mode(BVHSplitMode::MIDPOINT), is_built(false)
	{
		
	}
	void createBVH()
	{
		std::vector<BVHPrimitive> primitive_info(scene->primitives.size());
		std::vector<Primitive> ordered_primitives;
		for (unsigned int i = 0; i < scene->primitives.size(); ++i)
		{
			BVHPrimitive bvh_primitive;
			bvh_primitive.index = i;
			computeAABB(bvh_primitive);
			bvh_primitive.centroid = 0.5f * bvh_primitive.min + 0.5f * bvh_primitive.max;
			primitive_info[i] = bvh_primitive;
		}

		int total_nodes = 0;
		BVHNode* root = recursiveBuild(primitive_info, 0, primitive_info.size(), &total_nodes, ordered_primitives);
		scene->primitives.swap(ordered_primitives); // swap old primitives with new

		scene->nodes.resize(total_nodes);
		int offset = 0;
		flattenBVHTree(root, &offset);

		is_built = true;
	}
	
	BVHNode* recursiveBuild(std::vector<BVHPrimitive>& primitive_info,
						    int start,
							int end,
							int* total_nodes,
							std::vector<Primitive>& ordered_primitives)
	{
		// create new node
		BVHNode* node = new BVHNode();
		(*total_nodes)++;
		
		// compute bounds of all primitives
		glm::vec3 min = primitive_info[start].min;
		glm::vec3 max = primitive_info[start].max;
		for (int i = start; i < end; ++i)
		{
			min.x = glm::min(min.x, primitive_info[i].min.x);
			min.y = glm::min(min.y, primitive_info[i].min.y);
			min.z = glm::min(min.z, primitive_info[i].min.z);

			max.x = glm::max(max.x, primitive_info[i].max.x);
			max.y = glm::max(max.y, primitive_info[i].max.y);
			max.z = glm::max(max.z, primitive_info[i].max.z);
		}

		int n_primitives = end - start;
		if (n_primitives <= 2)
		{
			// create leaf node
			int first_primitive_offset = ordered_primitives.size();
			for (int i = start; i < end; ++i)
			{
				int primitive_number = primitive_info[i].index;
				ordered_primitives.push_back(scene->primitives[primitive_number]);
			}
			node->initLeaf(first_primitive_offset, n_primitives, min, max);
			return node;
		}
		else
		{
			// compute bound of primitive centroids
			glm::vec3 centroid_bounds_min = primitive_info[start].centroid;
			glm::vec3 centroid_bounds_max = primitive_info[start].centroid;
			for (int i = start; i < end; ++i)
			{
				centroid_bounds_min.x = glm::min(centroid_bounds_min.x, primitive_info[i].centroid.x);
				centroid_bounds_min.y = glm::min(centroid_bounds_min.y, primitive_info[i].centroid.y);
				centroid_bounds_min.z = glm::min(centroid_bounds_min.z, primitive_info[i].centroid.z);

				centroid_bounds_max.x = glm::max(centroid_bounds_max.x, primitive_info[i].centroid.x);
				centroid_bounds_max.y = glm::max(centroid_bounds_max.y, primitive_info[i].centroid.y);
				centroid_bounds_max.z = glm::max(centroid_bounds_max.z, primitive_info[i].centroid.z);
			}

			// choose split dimension dim
			float curr_extent = centroid_bounds_max.x - centroid_bounds_min.x;
			int dim = 0;
			if (centroid_bounds_max.y - centroid_bounds_min.y > curr_extent)
			{
				dim = 1;
				curr_extent = centroid_bounds_max.y - centroid_bounds_min.y;
			}
			if (centroid_bounds_max.z - centroid_bounds_min.z > curr_extent)
			{
				dim = 2;
			}

			// partition primitives into two sets
			int mid = (start + end) / 2;
			if (centroid_bounds_max[dim] == centroid_bounds_min[dim]) // all centroid points are in the same position
			{
				// create leaf node
				std::cout << "here" << std::endl;
				int first_primitive_offset = ordered_primitives.size();
				for (int i = start; i < end; ++i)
				{
					int primitive_number = primitive_info[i].index;
					ordered_primitives.push_back(scene->primitives[primitive_number]);
				}
				node->initLeaf(first_primitive_offset, n_primitives, min, max);
				return node;
			}
			else
			{
				// partition primitives based on split method
				switch (mode)
				{
				case BVHSplitMode::MIDPOINT:
				{
					float pmid = (centroid_bounds_min[dim] + centroid_bounds_max[dim]) * 0.5f;
					BVHPrimitive* mid_ptr = std::partition(&primitive_info[start], &primitive_info[end - 1], [dim, pmid](const BVHPrimitive& pi) {
						return pi.centroid[dim] < pmid;
					});
					mid = mid_ptr - &primitive_info[0];
					if (mid != start && mid != end)
						break;
				}
				[[fallthrough]];
				case BVHSplitMode::EQUAL_COUNTS:
				{
					mid = (start + end) / 2;
					std::nth_element(&primitive_info[start], &primitive_info[mid], &primitive_info[end - 1] + 1, [dim](const BVHPrimitive& a, const BVHPrimitive& b) {
						return a.centroid[dim] < b.centroid[dim];
					});
					break;
				}
				}

				// build children
				node->initInterior(dim,
					recursiveBuild(primitive_info, start, mid, total_nodes, ordered_primitives),
					recursiveBuild(primitive_info, mid,   end, total_nodes, ordered_primitives));
			}
		}

		return node;
	}

	int flattenBVHTree(BVHNode* node, int* offset)
	{
		LinearBVHNode* linear_node = &scene->nodes[*offset];
		linear_node->min = glm::vec4(node->min, 0.0f);
		linear_node->max = glm::vec4(node->max, 0.0f);
		int my_offset = (*offset)++;
		if (node->prim_count > 0) // create flattened leaf node
		{
			linear_node->prim_index = node->prim_start;
			linear_node->prim_count = node->prim_count;
		}
		else // create flattened interior node
		{
			linear_node->axis = node->split_axis;
			linear_node->prim_count = 0;
			flattenBVHTree(node->left, offset);
			linear_node->left = flattenBVHTree(node->right, offset);
		}
		return my_offset;
	}
};