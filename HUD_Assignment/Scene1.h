#pragma once
#include "Scene.h"
#include "UIHandler.h"
///calling a max health so that we cant grow our health bar past 100%
#define maxHealth 300


class Scene1 : public Scene 
{
private:
	SDL_Window * window;
	SDL_Renderer* renderer;
	int w, h;
	float elapsedTime;
	SDL_Rect* rect1 = nullptr;
	SDL_Rect* rect2 = nullptr;
	SDL_Texture* Message = nullptr;
	SDL_Rect* Message_rect = nullptr;
	TTF_Font* Sans = nullptr;
	SDL_Surface* surfaceMessage = nullptr;

	SDL_Texture* Message1 = nullptr;
	SDL_Rect* Message_rect1 = nullptr;
	SDL_Surface* surfaceMessage1 = nullptr;
	std::string health;
	SDL_Color Black;
	

public:
	Scene1(SDL_Window* sdlWindow_, SDL_Renderer* sdlRenderer_);
	~Scene1();

	bool OnCreate(); 
	void OnDestroy();
	void Update(const float time);
	void Render();
	virtual void HandleEvents(SDL_Event);
};

