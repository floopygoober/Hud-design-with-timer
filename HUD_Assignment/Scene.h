#include <SDL.h>

#ifndef SCENE_H
#define SCENE_H

///we created a virtual class here to use as a blueprint for our different scenes so it will be a bit easier to create more than 2 in teh future
class Scene {
public:
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(SDL_Event) = 0;
};

#endif