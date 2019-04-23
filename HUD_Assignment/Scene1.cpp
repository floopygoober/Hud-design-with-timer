#include "Scene1.h"

//Constructor for first UI screen
Scene1::Scene1(SDL_Window* sdlWindow_, SDL_Renderer* sdlRenderer_)
{
	//gives values to this class's window and renderer using the ones passed through
	window = sdlWindow_;
	renderer = sdlRenderer_;

	elapsedTime = 0.0f;
}

//Creates all objects and returns true to the UIHandler if they were created successfully
bool Scene1::OnCreate() {

	SDL_GetWindowSize(window, &w, &h);

	///Bottom purple bar on screen
	rect1 = new SDL_Rect;
	rect1->w = w;
	rect1->h = 100;
	rect1->x = 0;
	rect1->y = h - (rect1->h); 

	///health bar creation and placement
	rect2 = new SDL_Rect;
	rect2->w = maxHealth;
	rect2->h = 20;
	rect2->x = 15;
	rect2->y = h - (rect1->h / 2) - (rect2->h / 2) ;

	//text to tell the user to press the arrow keys so they can adjust the health bar and %
	Sans = TTF_OpenFont("Sans.ttf", 500); //this opens a font style and sets a size

	Black = { 0, 0, 0 };  //using rgb to set a black value to be used later

	surfaceMessage = TTF_RenderText_Solid(Sans, "Press L/R arrow keys", Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	Message_rect = new SDL_Rect; //create a rect for message
	Message_rect->x = 0;  //controls the rect's x coordinate 
	Message_rect->y = h/2 - (rect1->h); // controls the rect's y coordinte
	Message_rect->w = 800; // controls the width of the rect
	Message_rect->h = 300; // controls the height of the rect

	//health amount
	health = "Health: ";
	surfaceMessage1 = TTF_RenderText_Solid(Sans, health.c_str(), Black); //TTF_RenderText_Solid can only be used on SDL_Surface then you have to create the surface first

	Message1 = SDL_CreateTextureFromSurface(renderer, surfaceMessage1); //now you can convert it into a texture

	//create a rect for message
	Message_rect1 = new SDL_Rect; 
	Message_rect1->x = 0;  
	Message_rect1->y = 0; 
	Message_rect1->w = 160; 
	Message_rect1->h = 50; 

	if (rect1 == nullptr) return false;

	else return true; 
}

Scene1::~Scene1()
{
}

//Manual destructor, deletes everything from the screen
void Scene1::OnDestroy() {
	delete rect1;
	delete rect2;
	TTF_CloseFont(Sans);
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
	delete Message_rect;
	delete Message_rect1;

	std::cout << "Objects deleted." << std::endl;
}

//Update function for an active UI set up
void Scene1::Update(const float time) {

	elapsedTime += time;

	float i = round(((float)rect2->w / maxHealth) * 100); // getting percentage of the health bar to test the colour and the print out in top left corner
	i = std::floor(i * 100) / 100; // rounding the float to no decimals
	std::ostringstream str; 
	str << i; // converting to string

	health = "Health: " + str.str() + "%";
	//TTF_RenderText_Solid can only be used on SDL_Surface then you have to create the surface first
	surfaceMessage1 = TTF_RenderText_Solid(Sans, health.c_str(), Black); 
	//now you can convert it into a texture
	Message1 = SDL_CreateTextureFromSurface(renderer, surfaceMessage1);
}

//This draws everything to the screen and is called every UI Update
void Scene1::Render() {
	//set colour for background to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	//set colour for rect1 to purple
	SDL_SetRenderDrawColor(renderer, 121, 28, 168, 255);
	SDL_RenderFillRect(renderer, rect1);
	///
	//if health bar is above or equal to 2 thirds, colour it green
	if (rect2->w >= (maxHealth/3)*2) {
		SDL_SetRenderDrawColor(renderer, 35, 175, 10, 255);
		SDL_RenderFillRect(renderer, rect2);
	}

	//if health bar is between 1 and 2 thirds, colour it orange 
	else if (rect2->w >= maxHealth / 3 && rect2->w < (maxHealth / 3) * 2) {
		SDL_SetRenderDrawColor(renderer, 255, 174, 0, 255);
		SDL_RenderFillRect(renderer, rect2);
	}

	//if health bar is below 1 third, colour it red
	else if (rect2->w < maxHealth/3) {
		SDL_SetRenderDrawColor(renderer, 232, 11, 26, 255);
		SDL_RenderFillRect(renderer, rect2);
	}

	//draw messages
	SDL_RenderCopy(renderer, Message, NULL, Message_rect);
	SDL_RenderCopy(renderer, Message1, NULL, Message_rect1);

	//update the render on the screen
	SDL_RenderPresent(renderer); 

	//destroy the texture and surface for message1 since it's being recreated every loop
	SDL_DestroyTexture(Message1);
	SDL_FreeSurface(surfaceMessage1);
}

//detects events such as a mouse click
void Scene1::HandleEvents(SDL_Event event) {
	///if you click this tells the user what scene we are in from the console
	if (event.type == SDL_MOUSEBUTTONDOWN) {

		std::cout << "Scene 1" << std::endl;
	}
	///this here is what we use to shrink and grow our health bar
	else if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) {
			if (rect2->w > 0) rect2->w--;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			if (rect2->w < maxHealth) rect2->w++;
		}
	}
}
