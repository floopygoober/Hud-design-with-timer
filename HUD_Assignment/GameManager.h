#include "Scene.h"
#include "Window.h"
#include "Timer.h"
#include "Scene1.h"
#include "UIHandler.h"
#include <memory>
#include <iostream>
#include <SDL_ttf.h>

class GameManager
{
private:
	Window * window = nullptr;
	bool isRunning;
	Timer *timer = nullptr;
	UIHandler *uiHandler = nullptr;

public:
	GameManager();
	~GameManager();
	bool OnCreate();
	void OnDestroy();
	void Run();
};

