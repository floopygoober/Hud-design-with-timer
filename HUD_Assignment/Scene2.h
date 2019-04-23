#pragma once
#include "Scene.h"
#include "UIHandler.h"

class Scene2 : public Scene
{
private:
	SDL_Window * window;
	SDL_Renderer* renderer;
	int w, h;
	float elapsedTime;
	SDL_Rect* rect = nullptr;
	SDL_Texture* Message = nullptr;
	SDL_Rect* Message_rect = nullptr;
	TTF_Font* Sans = nullptr;
	SDL_Surface* surfaceMessage = nullptr;
	std::string clock;
	SDL_Color Black;
	int secondsLeft = 61;

public:
	Scene2(SDL_Window* sdlWindow_, SDL_Renderer* sdlRenderer_);
	~Scene2();

	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	virtual void HandleEvents(SDL_Event);
};

