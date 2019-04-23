#include "Window.h"
#include <iostream>

//Window constructor
Window::Window(const std::string &title, int width, int height) :
	//sets class variables to the temporary given values
	_title(title), _width(width), _height(height)
{
	//make sure window pointer is null before instantiating
	window = nullptr;
}

//Window destructor
Window::~Window() {

	//freeing up the memory we allocated for our rendering window and text stuff
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();

}

//initialises window and renderer
bool Window::init() {

	//if video did not initialise properly let the user know then quit
	//(returns false to GM which then returns false to main and does not start program)
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Fatal error occured. Failed to initialize.\n";
		return false;
	}

	if (TTF_Init() !=0) {
		std::cerr << "Fatal error occured. Failed to initialize.\n";
	}
	//creates window and checks if created correctly
	window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

	if (window == nullptr) {
		std::cerr << "Failed to create window.\n";
		return false;
	}

	//creates renderer and checks if created correctly
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer.\n";
		return false;
	}

	//returns true to GM in OnCreate()
	return true;

}
