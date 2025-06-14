#include "Shaders.hpp"

bool VertexShader::Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* description, UINT elements)
{
	if (FAILED(D3DReadFileToBlob(shaderPath.c_str(), m_vertexBuffer.GetAddressOf())))
	{
		Logger::Log(ERROR, L"Failed to load shader: " + shaderPath);
		return false;
	}

	if (FAILED(device->CreateVertexShader(m_vertexBuffer->GetBufferPointer(), m_vertexBuffer->GetBufferSize(), nullptr, m_vertexShader.GetAddressOf())))
	{
		Logger::Log(ERROR, L"Failed to create vertex shader " + shaderPath);
		return false;
	}

	if (FAILED(device->CreateInputLayout(description, elements, m_vertexBuffer->GetBufferPointer(), m_vertexBuffer->GetBufferSize(), m_inputLayout.GetAddressOf())))
	{
		Logger::Log(ERROR, "Failed to create input layout ");
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetShader() const
{
	return m_vertexShader.Get();
}

ID3D10Blob* VertexShader::GetBuffer() const
{
	return m_vertexBuffer.Get();
}

ID3D11InputLayout* VertexShader::GetLayout() const
{
	return m_inputLayout.Get();
}

bool PixelShader::Initialize(ComPtr<ID3D11Device>& device, std::wstring shaderPath)
{
	if (FAILED(D3DReadFileToBlob(shaderPath.c_str(), m_pixelBuffer.GetAddressOf())))
	{
		Logger::Log(ERROR, L"Failed to load shader: " + shaderPath);
		return false;
	}

	if (FAILED(device->CreatePixelShader(m_pixelBuffer->GetBufferPointer(), m_pixelBuffer->GetBufferSize(), nullptr, m_pixelShader.GetAddressOf())))
	{
		Logger::Log(ERROR, L"Failed to create pixel shader " + shaderPath);
		return false;
	}

	return true;
}

ID3D11PixelShader* PixelShader::GetShader() const
{
	return m_pixelShader.Get();
}

ID3D10Blob* PixelShader::GetBuffer() const
{
	return m_pixelBuffer.Get();
}
