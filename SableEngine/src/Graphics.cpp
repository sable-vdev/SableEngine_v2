#include "Graphics.hpp"

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

    if (!InitializeScene())
    {
        Logger::Log(ERROR, "Failed to initialize Scene");
    }
}

Graphics::~Graphics()
{
}

void Graphics::Render()
{
    float color[4] = { 0.4f, 0.6f, 0.9f, 1.0f };
    m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), color);

    m_deviceContext->IASetInputLayout(m_vertexShader.GetLayout());
    m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_deviceContext->VSSetShader(m_vertexShader.GetShader(), nullptr, 0);
    m_deviceContext->PSSetShader(m_pixelShader.GetShader(), nullptr, 0);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);

    m_deviceContext->Draw(3, 0);

    if (m_vsync)
    {
        m_swapChain->Present(1, 0);
    }
    else m_swapChain->Present(0, 0);
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
    
    //go through every adapter the computer has and rank them based on their vram size
    for (UINT i = 0; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);
        adapterMap.insert(std::make_pair(desc.DedicatedVideoMemory, adapter));
        /*
        std::wstring output = desc.Description;
        Logger::Log(DEBUG, output + L" " + std::to_wstring(desc.DedicatedVideoMemory));
        */
    }

    if (adapterMap.empty() && adapterMap.rbegin()->first <= 0)
    {
        Logger::Log(ERROR, "Problem while reading the multimap for adapters");
        return false;
    }

    adapter = adapterMap.rbegin()->second;

    DXGI_ADAPTER_DESC1 desc;
    adapter->GetDesc1(&desc);

    m_adapterDescription = desc.Description;
    m_adapterDescription += L" (";
    m_adapterDescription += std::to_wstring(desc.DedicatedVideoMemory / 1024 / 1024);
    m_adapterDescription += L" GB)";

    Logger::Log(DEBUG, m_adapterDescription);

    ComPtr<IDXGIOutput> output;
    //TODO
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
    //TILL TODO

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
    swapChainDescription.Windowed = !m_fullscreen;
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


    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(viewport));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<FLOAT>(width);
    viewport.Height = static_cast<FLOAT>(height);

    m_deviceContext->RSSetViewports(1, &viewport);

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
        {"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT numElements = ARRAYSIZE(layout);

    if (!m_vertexShader.Initialize(m_device, shaderpath + L"VertexShader.cso", layout, numElements))
    {
        return false;
    }

    if (!m_pixelShader.Initialize(m_device, shaderpath + L"PixelShader.cso"))
    {
        return false;
    }

    return true;
}

bool Graphics::InitializeScene()
{
    Vertex vertices[] = {
        Vertex(0.0f, 0.5f),
        Vertex(0.5f, -0.5f),
        Vertex(-0.5f, -0.5f),
    };

    D3D11_BUFFER_DESC vbDesc;
    ZeroMemory(&vbDesc, sizeof(vbDesc));

    vbDesc.ByteWidth = sizeof(vertices);
    vbDesc.Usage = D3D11_USAGE_DEFAULT;
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbDesc.CPUAccessFlags = 0;
    vbDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vbSRD;
    ZeroMemory(&vbSRD, sizeof(vbSRD));
    vbSRD.pSysMem = vertices;

    if (FAILED(m_device->CreateBuffer(&vbDesc, &vbSRD, m_vertexBuffer.GetAddressOf())))
    {
        Logger::Log(ERROR, "Failed to create vertex buffer");
        return false;
    }

    return true;
}
