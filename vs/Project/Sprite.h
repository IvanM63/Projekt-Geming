#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Quad.h"
#include "BoundingBox.h"
#include <GLM/gtc/matrix_transform.hpp>

using namespace glm;

namespace Engine {
	struct AnimData {
		string name;
		int startFrameIndex, endFrameIndex;
	};

	class Sprite
	{
	public:
		Sprite(Texture* texture, Shader* shader, Quad* quad);
		~Sprite();
		void Draw();
		void Update(float deltaTime);
		void AddAnimation(string name, int startFrameIndex, int endFrameIndex);
		void PlayAnim(string name);
		void SetFlipHorizontal(bool flipHorizontal);
		void SetFlipVertical(bool flipVertical);
		void SetAnimationDuration(float maxFrameDuration);
		void SetEnableAnimation(bool enableAnimation);
		void SetPosition(float x, float y);
		void SetRotation(float degree);
		void SetNumXFrames(int numXFrames);
		void SetNumYFrames(int numYFrames);
		int GetTotalFrames();
		float GetRotation();
		void SetScale(float s);
		float GetScale();
		void SetSize(float width, float height);
		float GetScaleWidth();
		float GetScaleHeight();
		BoundingBox* GetBoundingBox();
		vec2 GetPosition();
		vec2 GetRotatedPoint(float x, float y);
		void SetBoundingBoxSize(float w, float h);
	private:
		BoundingBox* boundingBox;
		vec4 min;
		Shader* shader;
		Quad* quad;
		Texture* texture;
		float width = 0, height = 0, s = 1, degree = 0, frameDuration = 0, maxFrameDuration = 80;
		bool flipHorizontal = false, flipVertical = false, enableAnimation = false;
		int numXFrames = 1, numYFrames = 1, frameIndex = 0;
		mat4 CreateTransform();
		void UpdateShaderData();
		AnimData* GetAnimData(string name);
		vec2 position, boundingBoxSize;
		vector<AnimData*> animationData;
		AnimData* currentAnim = NULL;
		
	};
}

#endif

