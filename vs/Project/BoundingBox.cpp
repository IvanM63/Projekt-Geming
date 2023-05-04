#include "BoundingBox.h"


bool Engine::BoundingBox::CollideWith(BoundingBox* other)
{
	return SATCollision::CheckCollision(this->GetVertices(), other->GetVertices());
}

void Engine::BoundingBox::SetVertices(vec2 p1, vec2 p2, vec2 p3, vec2 p4)
{
	vertices[0] = p1;
	vertices[1] = p2;
	vertices[2] = p3;
	vertices[3] = p4;
}


RectVertexArray Engine::BoundingBox::GetVertices()
{
	return vertices;
}

