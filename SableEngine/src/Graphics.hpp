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
	void Shutdown();
private:
	bool InitializeDirectX(HWND& hwnd, int& width, int& height);
	bool InitializeShaders();
	bool InitializeScene();
private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11Buffer> m_vertexBuffer2;
	ComPtr<ID3D11RasterizerState> m_rasterizerState;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	std::wstring m_adapterDescription;
	VertexShader m_vertexShader;
	PixelShader m_pixelShader;
	std::vector<Vertex> m_vertices;
	bool m_fullscreen;
	bool m_vsync;
};

