#pragma once
#include <DirectXMath.h>

struct Vertex
{
	inline Vertex() : position(0.0f, 0.0f) {};
	inline Vertex(float x, float y) : position(x, y) {}

	DirectX::XMFLOAT2 position;
};