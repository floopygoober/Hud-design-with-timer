#include "GameManager.h"



//GM constructor
GameManager::GameManager()
{
	//initialize all pointers to null
	timer = nullptr;
	isRunning = true;
	uiHandler = nullptr;
}

bool GameManager::OnCreate() {

	//defines screen resolution
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//creating a window using my own Window class, passing the title and resolution
	window = new Window("SDL HUD screen", SCREEN_WIDTH, SCREEN_HEIGHT);

	//If window is still a null pointer, destroy the GM and return false to main, exiting the program
	if (window == nullptr) {
		OnDestroy();
		return false;
	}

	//If window did not initialize properly, destroy and return false to main
	if (window->init() == false) {
		OnDestroy();
		return false;
	}

	//creates a timer for the entire program
	timer = new Timer();

	//if still null, destroy & return false
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	//creates a UI handler and gives it the pointer to the window created above
	uiHandler = new UIHandler(window);

	//same as previous objects; if null or did not initialize correctly, destroy GM and return false to main
	if (uiHandler == nullptr) {
		OnDestroy();
		return false;
	}

	if (uiHandler->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	//if all went well, returns true to main in order to then run the program
	return true;
}

GameManager::~GameManager()
{
}

//manual destructor, deletes window and timer when called but only if they exist to begin with
void GameManager::OnDestroy() {
	if (window) delete window;
	if (timer) delete timer;

}

// This function runs the entire program and keeps it open while isRunning is true
void GameManager::Run() {
	SDL_Event event;
	timer->Start();
	std::cout << "Press the space bar to change scenes, click the mouse to display which scene you are currently viewing.\n"
				<< "Scene 1 is interactive, use the left and right arrow keys to raise and lower the health bar.\n" 
				<< "The health bar changes colour depending on how much health there is!" << std::endl;
	while (isRunning) {

		//checks for events while game is running
		if (SDL_PollEvent(&event) != 0) {

			//passes the event to the UIHandler in case it applies to it
			uiHandler->HandleEvents(event);

			//if the program quits, set isRunning to false so that it can exit the loop and close correctly
			if (event.type == SDL_QUIT) isRunning = false;

			//if the user pressed escape, set isRunning to false (closes program)
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
			}
		}

		//Updates UI handler
		uiHandler->Update(timer->GetDeltaTime());

		//updates timer's frame ticks to keep deltatime accurate
		timer->UpdateFrameTicks();



		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}

	// quits program when all code in this function is finished
	SDL_Quit();
}