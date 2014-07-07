#pragma once

#include "pch.h"

#include "SDL.h"

class Mesh;
class Material;
class Camera;
struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

class Renderer
{
	Window window;

	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* immediateContext;
	ID3D11RenderTargetView* renderTargetView;

public:
	enum class WindowType
	{
		windowed,
		fullscreen,
		borderless
	};

	Renderer(const std::string& title, int width, int height, WindowType windowType);

	// Instructs the renderer to eventually render the mesh with the given material.
	void render(const Mesh& mesh, const Material& material, const Camera& camera);
	
	// Immediately starts the actual rendering process for all meshes received.
	// This is basically a hint; everything will be flushed eventually even if you don't call this.
	void flush();

	// Displays the results on the screen.  This should be called once per frame.
	void show();
};