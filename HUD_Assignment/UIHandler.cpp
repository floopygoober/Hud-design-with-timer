#include "UIHandler.h"
#include <iostream>

//UI handler constructor
UIHandler::UIHandler(Window* window_)
{
	//sets the first UI active by default
	UI1 = true;
	UI2 = false;

	//bool later used to detect when the user wants to change the scene
	changeScene = false;

	//gives the temporary window object to the window object in this class
	window = window_;

}

//creates the scene (defaults to scene1) and returns values to GM
bool UIHandler::OnCreate() {
	UI = new Scene1(window->GetSDL_Window(), window->getRenderer());

	if (UI == nullptr) {
		OnDestroy();
		return false;
	}

	if (UI->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;

}

void UIHandler::OnDestroy() {
	if (UI) delete UI;
}

UIHandler::~UIHandler()
{
}

//Checks for events using the event passed to it by the GM
void UIHandler::HandleEvents(SDL_Event event) {

	//if user pressed space, set UI1 and UI2 to the opposite of what they were
	//changeScene is checked in update, allowing to change scenes at will 
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			UI1 = !UI1;
			UI2 = !UI2;
			changeScene = true;
			std::cout << "Changing scenes! UI1 = " << UI1 << " UI2 = " << UI2 << std::endl;
		}
	}

	//passes the event along to the scene in case it might apply to it
	UI->HandleEvents(event);
}

//Updates all UI
void UIHandler::Update(const float time) {

	//tells scene to update using the delta time passed here by GM
	UI->Update(time);

	//if changeScene was changed to true (method above)... 
	if (changeScene) {

		//then change to scene 1 if that's what's now active
		if (UI1 && !UI2) {
			UI->OnDestroy();
			UI = new Scene1(window->GetSDL_Window(), window->getRenderer());
			UI->OnCreate();
			std::cout << "Changed to scene 1." << std::endl;
		}

		//or change to scene 2 if that's what's now active 
		else if (!UI1 && UI2) {
			UI->OnDestroy();
			UI = new Scene2(window->GetSDL_Window(), window->getRenderer());
			UI->OnCreate();
			std::cout << "Changed to scene 2." << std::endl;
		}

		//reset changeScene so it's not constantly changing
		changeScene = false;
	}

	//render's the scene
	UI->Render();
	
}
