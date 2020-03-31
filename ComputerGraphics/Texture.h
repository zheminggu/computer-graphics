#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vector3.h"
class Vector3;
class Texture
{
public:
	Texture();
	~Texture();

	void OpenTexture(const char* fileName);
	Vector3 GetColor(Vector3& vector);
	Vector3 GetColor(Vector4& vector);
	Vector3 GetNormal(Vector3& vector);
private:
	float* textureR;
	float* textureG;
	float *textureB;
	int width;
	int height;
};



#endif