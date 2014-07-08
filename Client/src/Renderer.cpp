#include "pch.h"

#include "Renderer.h"

#include <Windows.h>
#include <d3d11.h>
#include "SDL2/SDL_syswm.h"

#include "SDL.h"
#include "ResourceCleanupTemplate.h"

namespace d3d11
{
	MAKE_RESOURCE_CLASS(SwapChain, IDXGISwapChain*, nullptr, resource->Release());
	MAKE_RESOURCE_CLASS(Device, ID3D11Device*, nullptr, resource->Release());
	MAKE_RESOURCE_CLASS(DeviceContext, ID3D11DeviceContext*, nullptr, resource->Release());
	MAKE_RESOURCE_CLASS(RenderTargetView, ID3D11RenderTargetView*, nullptr, resource->Release());

	MAKE_RESOURCE_CLASS(Texture2D, ID3D11Texture2D*, nullptr, resource->Release());
}

class Renderer::Impl
{
public:
	Window window;

	d3d11::SwapChain swapChain;
	d3d11::Device device;
	d3d11::DeviceContext immediateContext;
	d3d11::RenderTargetView renderTargetView;
};

Renderer::Renderer(const std::string& title, int width, int height, WindowType windowType)
{
	if(width <= 0)
		throw std::invalid_argument("width");
	if(height <= 0)
		throw std::invalid_argument("height");

	m = std::shared_ptr<Impl>(new Impl());

	int32_t flags = 0;
	if(windowType == WindowType::fullscreen) flags = SDL_WINDOW_FULLSCREEN;
	if(windowType == WindowType::borderless) flags = SDL_WINDOW_BORDERLESS;

	m->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

	if(!m->window.get())
		throw std::runtime_error("Failed to create the window.");

	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	if(!SDL_GetWindowWMInfo(m->window.get(), &info))
		throw std::runtime_error(SDL_GetError());

	if(info.subsystem != SDL_SYSWM_WINDOWS)
		throw std::runtime_error("The platform is not supported!");

	HWND hwnd = info.info.win.window;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;


	D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_9_3;
	UINT numFeatureLevels = 1;
	D3D_FEATURE_LEVEL featureLevelsSupported;

	if(FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevels, numFeatureLevels,
		D3D11_SDK_VERSION, &sd, &m->swapChain.get(), &m->device.get(), &featureLevelsSupported, &m->immediateContext.get())))
	{
		throw std::runtime_error("Failed to create D3D11 device and swap chain.");
	}


	d3d11::Texture2D backBuffer;

	// Get a pointer to the back buffer
	if(FAILED(m->swapChain.get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer.get())))
		throw std::runtime_error("Failed to get a buffer from the swap chain.");

	// Create a render-target view
	if(FAILED(m->device.get()->CreateRenderTargetView(backBuffer.get(), NULL, &m->renderTargetView.get())))
		throw std::runtime_error("Failed to create render target view.");

	// Bind the view
	m->immediateContext.get()->OMSetRenderTargets(1, &m->renderTargetView.get(), NULL);


	// Setup the viewport
	D3D11_VIEWPORT viewport;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m->immediateContext.get()->RSSetViewports(1, &viewport);
}

void Renderer::render(const Mesh& mesh, const Material& material, const Camera& camera)
{

}

void Renderer::flush()
{

}

void Renderer::show()
{
	//
	// Clear the backbuffer
	//
	float ClearColor[4] = {0.0f, 0.125f, 0.6f, 1.0f}; // RGBA
	m->immediateContext.get()->ClearRenderTargetView(m->renderTargetView.get(), ClearColor);

	m->swapChain.get()->Present(0, 0);
}
