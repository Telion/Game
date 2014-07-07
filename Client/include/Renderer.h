#pragma once

#include "pch.h"

class Mesh;
class Material;
class Camera;

class Renderer
{
	class Impl;
	std::shared_ptr <Impl> m;

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