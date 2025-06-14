#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>
#include <map>
#include "Logger.hpp"
#include "Shaders.hpp"
#include "Vertex.hpp"

using Microsoft::WRL::ComPtr;

class Graphics
{
public:
	Graphics();
	Graphics(HWND& hwnd, int& width, int& height, bool fullscreen, bool vsync);
	~Graphics();
	void Render();
private:
	bool InitializeDirectX(HWND& hwnd, int& width, int& height);
	bool InitializeShaders();
	bool InitializeScene();
private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	std::wstring m_adapterDescription;
	VertexShader m_vertexShader;
	PixelShader m_pixelShader;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	bool m_fullscreen;
	bool m_vsync;
};

