#pragma once
#include <SDL.h>
#include "Scene.h"
#include "Window.h"
#include "Scene1.h"
#include "Scene2.h"
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

class UIHandler
{

public:
	UIHandler(Window* window_);
	~UIHandler();
	
private:
	//private objects and variables
	Scene *UI = nullptr;
	Window *window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool UI1;
	bool UI2;
	bool changeScene;

public:
	//public methods and variables
	void HandleEvents(SDL_Event);
	void Update(const float time);
	bool OnCreate();
	void OnDestroy();

};

