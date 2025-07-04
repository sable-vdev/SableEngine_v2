#pragma once
#include <DirectXMath.h>

struct Vertex
{
	inline Vertex() : position(0.0f, 0.0f, 0.0f), color(0.0f, 0.0f, 0.0f, 1.0f) {};
	inline Vertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), color(r, g, b, 1.0f) {};
	inline Vertex(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 col) : position(pos), color(col) {};

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};