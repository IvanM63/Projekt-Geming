#include "Sprite.h"


using namespace Engine;


Sprite::Sprite(Texture* texture, Shader* shader, Quad* quad)
{
	this->texture = texture;
	this->quad = quad;
	this->shader = shader;
	this->width = texture->GetWidth();
	this->height = texture->GetHeight();
	this->boundingBox = new BoundingBox();
	SetBoundingBoxSize(GetScaleWidth(), GetScaleHeight());
}

Sprite::~Sprite()
{
	delete boundingBox;
	delete currentAnim;
}

void Sprite::Draw()
{
	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Bind texture
	texture->Bind();
	UpdateShaderData();
	// Draw Quad
	quad->Draw();
	// Unbind texture
	texture->UnBind();
	// Disable transparency
	glDisable(GL_BLEND);
}


void Engine::Sprite::Update(float deltaTime)
{
	int n = GetTotalFrames();
	if (!enableAnimation || currentAnim == NULL || n == 1)
		return;

	frameDuration += deltaTime;

	if (frameDuration >= maxFrameDuration) {
		frameDuration = 0;
		frameIndex = (frameIndex < currentAnim->startFrameIndex || frameIndex >= currentAnim->endFrameIndex) ? currentAnim->startFrameIndex : frameIndex + 1;
	}
}

void Engine::Sprite::AddAnimation(string name, int startFrameIndex, int endFrameIndex)
{
	AnimData* a = new AnimData();
	a->name = name;
	a->startFrameIndex = startFrameIndex;
	a->endFrameIndex = endFrameIndex;
	animationData.push_back(a);
}

void Engine::Sprite::PlayAnim(string name)
{
	enableAnimation = true;
	if (currentAnim != NULL && name == currentAnim->name)return;
	currentAnim = GetAnimData(name);
}

void Engine::Sprite::SetFlipHorizontal(bool flipHorizontal)
{
	this->flipHorizontal = flipHorizontal;
}

void Engine::Sprite::SetFlipVertical(bool flipVertical)
{
	this->flipVertical = flipVertical;
}


void Engine::Sprite::SetAnimationDuration(float maxFrameDuration)
{
	this->maxFrameDuration = maxFrameDuration;
}

void Engine::Sprite::SetEnableAnimation(bool enableAnimation)
{
	this->enableAnimation = enableAnimation;
}

void Sprite::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Sprite::SetRotation(float degree)
{
	this->degree = degree;
}

void Engine::Sprite::SetNumXFrames(int numXFrames)
{
	this->numXFrames = numXFrames;
}

void Engine::Sprite::SetNumYFrames(int numYFrames)
{
	this->numYFrames = numYFrames;
}

int Engine::Sprite::GetTotalFrames()
{
	return numXFrames * numYFrames;
}

float Sprite::GetRotation()
{
	return this->degree;
}

void Sprite::SetScale(float s)
{
	this->s = abs(s);
	SetBoundingBoxSize(GetScaleWidth(), GetScaleHeight());
}

float Engine::Sprite::GetScale()
{
	return this->s;
}

void Sprite::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
	SetBoundingBoxSize(GetScaleWidth(), GetScaleHeight());
}

float Sprite::GetScaleWidth()
{
	return (s * width) / numXFrames;
}

float Sprite::GetScaleHeight()
{
	return (s * height) / numYFrames;
}

BoundingBox* Sprite::GetBoundingBox()
{
	float x = position.x;
	float y = position.y;
	float w = boundingBoxSize.x, h = boundingBoxSize.y;
	float dx = GetScaleWidth() - boundingBoxSize.x;
	x += 0.5 * dx;
	vec2 p1 = GetRotatedPoint(x + w, y);
	vec2 p2 = GetRotatedPoint(x + w, y + h);
	vec2 p3 = GetRotatedPoint(x, y + h);
	vec2 p4 = GetRotatedPoint(x, y);
	boundingBox->SetVertices(p1, p2, p3, p4);

	return boundingBox;
}

vec2 Engine::Sprite::GetPosition()
{
	return position;
}



mat4 Sprite::CreateTransform()
{
	mat4 transform = mat4();
	// Translate Sprite
	float x = position.x;
	float y = position.y;
	float w = GetScaleWidth(), h = GetScaleHeight();
	transform = translate(transform, vec3(x, y, 0.0f));
	// Rotate sprite at center
	transform = translate(transform, vec3(0.5f * w, 0.5f * h, 0.0f));
	transform = rotate(transform, radians(degree), vec3(0.0f, 0.0f, 1.0f));
	transform = translate(transform, vec3(-0.5f * w, -0.5f * h, 0.0f));
	// Scale sprite
	float sx = flipHorizontal ? -1 : 1;
	float sy = flipVertical ? -1 : 1;
	float tx = flipHorizontal ? w : 0;
	float ty = flipVertical ? h : 0;
	transform = translate(transform, vec3(tx, ty, 0.0f));
	transform = scale(transform, vec3(sx * w, sy * h, 1));

	return transform;
}

void Engine::Sprite::UpdateShaderData()
{
	shader->Use();
	shader->setInt(numXFrames, "nx");
	shader->setInt(numYFrames, "ny");
	shader->setInt(frameIndex, "frameIndex");
	shader->setMat4(CreateTransform(), "model");
}

AnimData* Engine::Sprite::GetAnimData(string name)
{
	for (AnimData* a : animationData)
		if (name == a->name) return a;
	return NULL;
}

vec2 Engine::Sprite::GetRotatedPoint(float x, float y)
{
	float rad = glm::radians(degree);
	float sinx = glm::sin(rad);
	float cosx = glm::cos(rad);
	float w = GetScaleWidth(), h = GetScaleHeight();
	float cx = position.x + (w * 0.5f);
	float cy = position.y + (h * 0.5f);

	return vec2((x - cx) * cosx - (y - cy) * sinx + cx,
		(x - cx) * sinx + (y - cy) * cosx + cy);
}

void Engine::Sprite::SetBoundingBoxSize(float w, float h)
{
	boundingBoxSize.x = w;
	boundingBoxSize.y = h;
}

vec2 Engine::Sprite::GetBoundingBoxCenter()
{
	float x_sum = 0, y_sum = 0;

	for (int i = 0; i < 4; i++) {
		x_sum += boundingBox->vertices[i].x;
		y_sum += boundingBox->vertices[i].y;
	}

	float center_x = x_sum / 4;
	float center_y = y_sum / 4;

	return vec2(center_x, center_y);
}



