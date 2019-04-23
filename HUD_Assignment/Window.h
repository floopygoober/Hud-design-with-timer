#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>


class Window {

public:
	Window(const std::string &title, int width, int height);
	~Window();

	bool init();

	//small function to return window/renderer when needed outside of this class
	inline SDL_Window* GetSDL_Window() { return window; }
	inline SDL_Renderer* getRenderer() { return renderer; }

private:
	std::string _title;
	int _width = 800;
	int _height = 600;


	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};