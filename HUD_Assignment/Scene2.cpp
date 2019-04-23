#include "Scene2.h"
#include <iostream>



//Constructor for second UI screen
Scene2::Scene2(SDL_Window* sdlWindow_, SDL_Renderer* sdlRenderer_)
{
	//gives values to this class's window and renderer using the ones passed through
	window = sdlWindow_;
	renderer = sdlRenderer_;
	elapsedTime = 0.0f;
}

//Creates all objects and returns true to the UIHandler if they were created successfully
bool Scene2::OnCreate() {

	SDL_GetWindowSize(window, &w, &h);

	rect = new SDL_Rect;

	rect->w = 120;
	rect->h = 120;
	rect->x = (w / 2) - (rect->w / 2);
	rect->y = (h / 2) - (rect->h / 2);
	
	//this opens a font style and sets the size of it
	Sans = TTF_OpenFont("Sans.ttf", 500); 

	Black = { 0, 0, 0 };//same as scene1

	//exact same process as we used in Scene1
	surfaceMessage = TTF_RenderText_Solid(Sans, "", Black);
	
	//now you can convert it into a texture just like scene1
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

	Message_rect = new SDL_Rect; //create a rect for message
	Message_rect->x = rect->x;  //controls the rect's x coordinate 
	Message_rect->y = rect->y; // controls the rect's y coordinte
	Message_rect->w = rect->w; // controls the width of the rect
	Message_rect->h = rect->h; // controls the height of the rect

	if (rect == nullptr) return false;

	else return true;

}
Scene2::~Scene2()
{
}

//Manual destructor, all objects get deleted
void Scene2::OnDestroy() {
	delete rect;
	TTF_CloseFont(Sans);
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
	delete Message_rect;
	//console tells user that stuff has been deleted
	std::cout << "Objects deleted." << std::endl;
}

//Update function for manupulation of shapes and other objects in UI
void Scene2::Update(const float time) {

	//gets elapsed time by constantly adding delta time since the scene started
	elapsedTime += time;

	//count down from 61 until it hits 0, we start at 61 because it will start counting before the user can clearly see the initial number
	//this lets it start at 60 to a users eye instead of 59
	if (secondsLeft > 0) {
		secondsLeft = 61 - elapsedTime;
	}
	
	//make a string to hold the seconds
	clock = std::to_string(secondsLeft);
	
	// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	surfaceMessage = TTF_RenderText_Solid(Sans, clock.c_str(), Black); 
	//now you can convert it into a texture
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
}

//draws everything to the screen, is called during every update in UIHandler
void Scene2::Render() {
	//set and draw background colour
	SDL_SetRenderDrawColor(renderer, 142, 142, 142, 255);
	SDL_RenderClear(renderer);

	//set and draw rectangle
	SDL_SetRenderDrawColor(renderer, 216, 8, 133, 255);
	SDL_RenderFillRect(renderer, rect);
	
	//draw clock
	SDL_RenderCopy(renderer, Message, NULL, Message_rect);

	//update the render on the screen
	SDL_RenderPresent(renderer);

	//destroy the texture and surface for message1 since it's being recreated every loop
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}

//detects events such as a mouse click
void Scene2::HandleEvents(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		std::cout << "This is Scene 2." << std::endl;
	}
}
