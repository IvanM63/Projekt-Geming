#ifndef SATCOLLISION_H
#define SATCOLLISION_H

#include <GLM/glm.hpp>
#include <array>
#include <limits>

using namespace glm;
using namespace std;
static const float NORMAL_TOLERANCE = 0.0001f;
using RectVertexArray = array<vec2, 4>;

namespace Engine {
	struct Result {
		float min_proj, max_proj, min_index, max_index;
	};
	class SATCollision
	{
	public:
		static bool CheckCollision(RectVertexArray& vecs_box1, RectVertexArray& vecs_box2);
	private:
		static Result getMinMax(RectVertexArray& vecs_box, vec2& axis);
		static RectVertexArray GetNormals(RectVertexArray& dots);
		static vec2 GetNormal(const vec2& v);
		static float dotProduct(const vec2& a, const vec2& b);
	};

}
#endif