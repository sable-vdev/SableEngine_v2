#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>
#include <map>
#include "Logger.hpp"

using Microsoft::WRL::ComPtr;

class Graphics
{
public:
	Graphics();
	Graphics(HWND hwnd, int& width, int& height, bool fullscreen);
	~Graphics();
private:
	bool InitializeDirectX(HWND hwnd, int& width, int& heightn);
private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	DXGI_ADAPTER_DESC1 m_adapterDescription;
	bool m_fullscreen;
};

