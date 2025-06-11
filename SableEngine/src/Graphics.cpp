#include "Graphics.hpp"

#include <string>

Graphics::Graphics() : m_fullscreen(false), m_vsync(false)
{
}

Graphics::Graphics(HWND& hwnd, int& width, int& height, bool fullscreen, bool vsync) : m_fullscreen(fullscreen), m_vsync(vsync)
{
    if (!InitializeDirectX(hwnd, width, height))
    {
        Logger::Log(ERROR, "Failed to initialize DirectX");
    }

    if (!InitializeShaders())
    {
        Logger::Log(ERROR, "Failed to initialize Shaders");
    }
}

Graphics::~Graphics()
{
}

void Graphics::Render()
{
    float color[4] = { 0.1f, 0.25f, 0.5f, 1.0f };
    m_deviceContext.Get()->ClearRenderTargetView(m_renderTargetView.Get(), color);
    if (m_vsync)
    {
        m_swapChain.Get()->Present(1, 0);
    }
    else m_swapChain.Get()->Present(0, 0);
}

bool Graphics::InitializeDirectX(HWND& hwnd, int& width, int& height)
{
    ComPtr<IDXGIFactory1> factory;

    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
    {
        Logger::Log(ERROR, "Failed to create DXGIFactory");
        return false;
    }

    ComPtr<IDXGIAdapter1> adapter;
    std::multimap<size_t, ComPtr<IDXGIAdapter1>> adapterMap;
    
    for (UINT i = 0; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);
        adapterMap.insert(std::make_pair(desc.DedicatedVideoMemory, adapter));
        std::wstring output = desc.Description;
        Logger::Log(DEBUG, output + L" " + std::to_wstring(desc.DedicatedVideoMemory));
    }

    if (adapterMap.empty() && adapterMap.rbegin()->first <= 0)
    {
        Logger::Log(ERROR, "Problem while reading the multimap for adapters");
        return false;
    }

    adapter = adapterMap.rbegin()->second;

    m_adapterDescription = DXGI_ADAPTER_DESC1();
    adapter->GetDesc1(&m_adapterDescription);

    Logger::Log(DEBUG, m_adapterDescription.Description);

    ComPtr<IDXGIOutput> output;

    if (FAILED(adapter->EnumOutputs(0, &output)))
    {
        Logger::Log(ERROR, "Failed to enumerate monitors");
        return false;
    }

    UINT numModes = 0;
    DXGI_MODE_DESC* displayModes = nullptr;
    DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

    if (FAILED(output->GetDisplayModeList(format, 0, &numModes, nullptr)))
    {
        return false;
    }

    displayModes = new DXGI_MODE_DESC[numModes];

    if (FAILED(output->GetDisplayModeList(format, 0, &numModes, displayModes)))
    {
        return false;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

    UINT numerator = 0, denominator = 0;
    for (UINT i = 0; i < numModes; i++)
    {
        if (displayModes[i].Width == (UINT) width && displayModes[i].Height == (UINT) height)
        {
            numerator = displayModes[i].RefreshRate.Numerator;
            denominator = displayModes[i].RefreshRate.Denominator;
        }
    }

    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Width = width;
    swapChainDescription.BufferDesc.Height = height;
    swapChainDescription.BufferDesc.Format = format;

    if (m_fullscreen)
    {
        swapChainDescription.BufferDesc.RefreshRate.Numerator = numerator;
        swapChainDescription.BufferDesc.RefreshRate.Denominator = denominator;
    }
    else
    {
        swapChainDescription.BufferDesc.RefreshRate.Numerator = 0;
        swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
    }
    swapChainDescription.SampleDesc.Count = 1;
    swapChainDescription.SampleDesc.Quality = 0;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.OutputWindow = hwnd;
    swapChainDescription.Windowed = m_fullscreen;
    swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    if (FAILED(D3D11CreateDeviceAndSwapChain(adapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &swapChainDescription, m_swapChain.GetAddressOf(), m_device.GetAddressOf(),
        nullptr, m_deviceContext.GetAddressOf())))
    {
        Logger::Log(ERROR, "Failed to create swapchain and device!");
        return false;
    }

    ComPtr<ID3D11Texture2D> backBuffer;

    if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()))))
    {
        Logger::Log(ERROR, "Failed to get back buffer");
        return false;
    }

    if (FAILED(m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf())))
    {
        Logger::Log(ERROR, "Failed to create render target view");
        return false;
    }

    m_deviceContext.Get()->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);

    return true;
}

bool Graphics::InitializeShaders()
{
    std::wstring shaderpath;
#ifdef NDEBUG
    shaderpath = L"..\\Engine\\bin\\Release\\";
#else 
    shaderpath = L"..\\Engine\\bin\\Debug\\";
#endif // NDEBUG

    
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT numElements = ARRAYSIZE(layout);

    if (!m_vertexShader.Initialize(m_device, shaderpath + L"VertexShader.cso", layout, numElements))
    {
        return false;
    }

    return true;
}
