#include "Graphics.hpp"

Graphics::Graphics()
{
}

Graphics::Graphics(HWND hwnd, int& width, int& height, bool fullscreen) : m_fullscreen(fullscreen)
{
    InitializeDirectX(hwnd, width, height);
}

Graphics::~Graphics()
{
}

bool Graphics::InitializeDirectX(HWND hwnd, int& width, int& height)
{
    IDXGIFactory1* factory;

    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
    {
        Logger::Log(ERROR, "Failed to create DXGIFactory");
        return false;
    }

    IDXGIAdapter1* adapter;
    std::multimap<int, IDXGIAdapter1*> adapterMap;
    
    for (UINT i = 0; factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
    {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);
        adapterMap.insert(std::make_pair(desc.DedicatedVideoMemory, adapter));
    }

    if (adapterMap.empty() && adapterMap.begin()->first <= 0)
    {
        Logger::Log(ERROR, "Problem while reading the multimap for adapters");
        return false;
    }

    adapter = adapterMap.begin()->second;

    m_adapterDescription = DXGI_ADAPTER_DESC1();
    adapter->GetDesc1(&m_adapterDescription);

    Logger::Log(DEBUG, m_adapterDescription.Description);

    IDXGIOutput* output = nullptr;

    if (FAILED(adapter->EnumOutputs(0, &output)))
    {
        Logger::Log(ERROR, "Failed to enumerate monitors");
        return false;
    }

    UINT numModes = 0;
    DXGI_MODE_DESC* displayModes = nullptr;
    DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT;

    if (FAILED(output->GetDisplayModeList(format, 0, &numModes, nullptr)))
    {
        return false;
    }

    displayModes = new DXGI_MODE_DESC[numModes];

    if (FAILED(output->GetDisplayModeList(format, 0, &numModes, displayModes)))
    {
        return false;
    }
    
    return true;
}
