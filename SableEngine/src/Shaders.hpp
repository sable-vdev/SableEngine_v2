#pragma once
#pragma comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include "Logger.hpp"

using Microsoft::WRL::ComPtr;

class VertexShader
{
public:
	bool Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* description, UINT elements);
	ID3D11VertexShader* GetShader() const;
	ID3D10Blob* GetBuffer() const;
	ID3D11InputLayout* GetLayout() const;
private:
	ComPtr<ID3D11VertexShader> m_vertexShader;
	ComPtr<ID3D10Blob> m_vertexBuffer;
	ComPtr<ID3D11InputLayout> m_inputLayout;
};

class PixelShader
{
public:
	bool Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath);
	ID3D11PixelShader* GetShader() const;
	ID3D10Blob* GetBuffer() const;
private:
	ComPtr<ID3D11PixelShader> m_pixelShader;
	ComPtr<ID3D10Blob> m_pixelBuffer;
};

