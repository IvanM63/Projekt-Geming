#include "SATCollision.h"


bool Engine::SATCollision::CheckCollision(RectVertexArray& vecs_box1, RectVertexArray& vecs_box2)
{
	//prepare the normals
	RectVertexArray normals_box1 = GetNormals(vecs_box1);
	RectVertexArray normals_box2 = GetNormals(vecs_box2);

	//results of P, Q
	Result result_P1 = getMinMax(vecs_box1, normals_box1[1]);
	Result result_P2 = getMinMax(vecs_box2, normals_box1[1]);
	Result result_Q1 = getMinMax(vecs_box1, normals_box1[0]);
	Result result_Q2 = getMinMax(vecs_box2, normals_box1[0]);

	//results of R, S
	Result result_R1 = getMinMax(vecs_box1, normals_box2[1]);
	Result result_R2 = getMinMax(vecs_box2, normals_box2[1]);
	Result result_S1 = getMinMax(vecs_box1, normals_box2[0]);
	Result result_S2 = getMinMax(vecs_box2, normals_box2[0]);

	bool separate_P = result_P1.max_proj < result_P2.min_proj || result_P2.max_proj < result_P1.min_proj;
	bool separate_Q = result_Q1.max_proj < result_Q2.min_proj || result_Q2.max_proj < result_Q1.min_proj;
	bool separate_R = result_R1.max_proj < result_R2.min_proj || result_R2.max_proj < result_R1.min_proj;
	bool separate_S = result_S1.max_proj < result_S2.min_proj || result_S2.max_proj < result_S1.min_proj;


	return !(separate_P || separate_Q || separate_R || separate_S);
}

Engine::Result Engine::SATCollision::getMinMax(RectVertexArray& vecs_box, vec2& axis)
{
	float min_proj_box = dotProduct(vecs_box[0], axis);
	float min_dot_box = 1;
	float max_proj_box = dotProduct(vecs_box[0], axis);
	float max_dot_box = 1;
	for (int j = 1; j < vecs_box.size(); j++) {
		float curr_proj = dotProduct(vecs_box[j], axis);
		//select the maximum projection on axis to corresponding box corners
		if (min_proj_box > curr_proj) {
			min_proj_box = curr_proj;
			min_dot_box = j;
		}                               
		//select the minimum projection on axis to corresponding box corners
		if (curr_proj > max_proj_box) {
			max_proj_box = curr_proj;
			max_dot_box = j;
		}
	}

	Result res;
	res.min_proj = min_proj_box;
	res.max_proj = max_proj_box;
	res.min_index = min_dot_box;
	res.max_index = max_dot_box;
	return res;
}

RectVertexArray Engine::SATCollision::GetNormals(RectVertexArray& dots)
{
	RectVertexArray normals;
	for (int i = 0; i < dots.size() - 1; i++) {
		normals[i] = GetNormal(vec2(dots[i + 1].x - dots[i].x,
			dots[i + 1].y - dots[i].y));
	}

	normals[dots.size() - 1] = GetNormal(vec2(dots[0].x - dots[dots.size() - 1].x,
		dots[0].y - dots[dots.size() - 1].y));

	return normals;
}

vec2 Engine::SATCollision::GetNormal(const vec2& v)
{
	return vec2(-v.y, v.x);
}

float Engine::SATCollision::dotProduct(const vec2& a, const vec2& b)
{
	return a.x * b.x + a.y * b.y;
}