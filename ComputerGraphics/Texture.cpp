#include "Texture.h"
#include "FreeImage.h"
#include "Debug.h"
#include "Draw.h"
#include <math.h>
#include "Math.h"

Texture::Texture()
{

}

Texture::~Texture()
{
}

void Texture::OpenTexture(const char* fileName)
{
	FIBITMAP* tempImg = FreeImage_Load(FreeImage_GetFileType(fileName, 0), fileName);
	FIBITMAP* img = FreeImage_ConvertTo32Bits(tempImg);

	FreeImage_Unload(tempImg);

	int w = FreeImage_GetWidth(img);
	int h = FreeImage_GetHeight(img);
	//int scanW = FreeImage_GetPitch(img);
	this->width = w;
	this->height = h;
	//BYTE* byteImg = new BYTE[h * scanW];
	//FreeImage_ConvertToRawBits(byteImg, img, scanW, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);
	this->textureR = new float[w * h];
	this->textureG = new float[w * h];
	this->textureB = new float[w * h];
	int bytespp = FreeImage_GetLine(img) / FreeImage_GetWidth(img);
	for (unsigned y = 0; y < FreeImage_GetHeight(img); y++) {
		BYTE* bits = FreeImage_GetScanLine(img, y);
		for (unsigned x = 0; x < FreeImage_GetWidth(img); x++) {
			// Set pixel color to green with a transparency of 128
			this->textureR[y * w + x] = (float)bits[FI_RGBA_RED];
			this->textureG[y * w + x] = (float)bits[FI_RGBA_GREEN];
			this->textureB[y * w + x] = (float)bits[FI_RGBA_BLUE];
			// jump to next pixel
			bits += bytespp;
		}
	}
	
	//Debug::Log("Finish loading");
	FreeImage_Unload(img);


	//delete byteImg;
}

Vector3 Texture::GetColor(Vector3& vector)
{
	float u = 0.5-atan2f(vector.GetZ(),vector.GetX())/(2*PI);
	float v = 0.5-asinf(vector.GetY())/PI;

	u *= this->width;
	v *= this->height;
	int start_u = (int)u;
	int start_v = (int)v;
	if (start_u == this->width) {
		start_u--;
	}
	if (start_v == this->height) {
		start_v--;
	}
	float percent_v = v - (float)start_v;
	float R_s = lerp(this->textureR[start_u* width +start_v], this->textureR[start_u* width + start_v + 1], percent_v);
	float G_s = lerp(textureG[start_u * width + start_v], textureG[start_u * width + start_v + 1], percent_v);
	float B_s = lerp(textureB[start_u * width + start_v], textureB[start_u * width + start_v + 1], percent_v);
	float R_e = lerp(textureR[(start_u + 1) * width + start_v], textureR[(start_u + 1) * width + start_v + 1], percent_v);
	float G_e = lerp(textureG[(start_u + 1) * width + start_v], textureG[(start_u + 1) * width + start_v + 1], percent_v);
	float B_e = lerp(textureB[(start_u + 1) * width + start_v], textureB[(start_u + 1) * width + start_v + 1], percent_v);

	float percent_u = u - (float)start_u;
	float R_l = lerp(R_s, R_e, percent_u);
	float G_l = lerp(G_s, G_e, percent_u);
	float B_l = lerp(B_s, B_e, percent_u);

	return Vector3(R_l, G_l, B_l);
}

Vector3 Texture::GetColor(Vector4& vector)
{
	float u = 0.5 - atan2f(vector.GetZ(), vector.GetX()) / (2 * PI);
	float v = 0.5 - asinf(vector.GetY()) / PI;

	u *= this->width;
	v *= this->height;
	int start_u = (int)u;
	int start_v = (int)v;
	if (start_u == this->width) {
		start_u--;
	}
	if (start_v == this->height) {
		start_v--;
	}
	float percent_v = v - (float)start_v;
	float R_s = lerp(this->textureR[start_u * width + start_v], this->textureR[start_u * width + start_v + 1], percent_v);
	float G_s = lerp(textureG[start_u * width + start_v], textureG[start_u * width + start_v + 1], percent_v);
	float B_s = lerp(textureB[start_u * width + start_v], textureB[start_u * width + start_v + 1], percent_v);
	float R_e = lerp(textureR[(start_u + 1) * width + start_v], textureR[(start_u + 1) * width + start_v + 1], percent_v);
	float G_e = lerp(textureG[(start_u + 1) * width + start_v], textureG[(start_u + 1) * width + start_v + 1], percent_v);
	float B_e = lerp(textureB[(start_u + 1) * width + start_v], textureB[(start_u + 1) * width + start_v + 1], percent_v);

	float percent_u = u - (float)start_u;
	float R_l = lerp(R_s, R_e, percent_u);
	float G_l = lerp(G_s, G_e, percent_u);
	float B_l = lerp(B_s, B_e, percent_u);

	return Vector3(R_l, G_l, B_l);
}

Vector3 Texture::GetNormal(Vector3& vector) {
	float u = 0.5 - atan2f(vector.GetZ(), vector.GetX()) / (2 * PI);
	float v = 0.5 - asinf(vector.GetY()) / PI;

	u *= this->width;
	v *= this->height;
	int start_u = (int)u;
	int start_v = (int)v;
	if (start_u == this->width) {
		start_u--;
	}
	if (start_v == this->height) {
		start_v--;
	}
	float percent_v = v - (float)start_v;
	float R_s = lerp(this->textureR[start_u * width + start_v], this->textureR[start_u * width + start_v + 1], percent_v);
	float G_s = lerp(textureG[start_u * width + start_v], textureG[start_u * width + start_v + 1], percent_v);
	float B_s = lerp(textureB[start_u * width + start_v], textureB[start_u * width + start_v + 1], percent_v);
	float R_e = lerp(textureR[(start_u + 1) * width + start_v], textureR[(start_u + 1) * width + start_v + 1], percent_v);
	float G_e = lerp(textureG[(start_u + 1) * width + start_v], textureG[(start_u + 1) * width + start_v + 1], percent_v);
	float B_e = lerp(textureB[(start_u + 1) * width + start_v], textureB[(start_u + 1) * width + start_v + 1], percent_v);

	float percent_u = u - (float)start_u;
	float R_l = lerp(R_s, R_e, percent_u);
	float G_l = lerp(G_s, G_e, percent_u);
	float B_l = lerp(B_s, B_e, percent_u);
	Vector3 normal = Vector3(R_l, G_l, B_l);
	Vector3 new_vector = Vector3(vector);
	normal.Mul(2. / 255., 2. / 255., -1. / 128.);
	normal.Add(-1,-1,2);
	new_vector = new_vector + normal;
	return new_vector;
}



