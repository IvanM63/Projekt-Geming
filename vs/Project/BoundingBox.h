#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <GLM/glm.hpp>
#include <array>
#include "SATCollision.h"

using namespace glm;
using namespace std;
using RectVertexArray = array<vec2, 4>;

namespace Engine {
	class BoundingBox {
	public:
		bool CollideWith(BoundingBox* other);
		void SetVertices(vec2 p1, vec2 p2, vec2 p3, vec2 p4);
		RectVertexArray GetVertices();
	private:
		RectVertexArray vertices;
	};
}

#endif

