#pragma once
#include <DirectXMath.h>
class VertexStruct
{
	inline VertexStruct() : position(0, 0) {};
	inline VertexStruct(float x, float y) : position(x, y) {}

	DirectX::XMFLOAT2 position;
};

