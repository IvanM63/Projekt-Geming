#ifndef SHADER_H
#define SHADER_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLM/detail/type_mat.hpp>
#include <GLM/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

namespace Engine {
	class Shader
	{
	public:
		Shader(string vertex_path, string fragment_path);
		~Shader();
	    void Build();
		void Use();
		GLuint GetId();
		void setInt(int i, string str);
		void setFloat(float i, string str);
		void setMat4(mat4 mat, string str);
		void setVec3(vec3 data, string str);
		
	private:
		string vertexPath, fragmentPath;
		GLuint programId;
		void Validate(GLuint shader_id, string type);
	};
}

#endif

