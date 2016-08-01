#include "InputHandler.h"


#include <SDL_events.h>

InputHandler::InputHandler() :
	mKeystate(SDL_GetKeyboardState(NULL)),
	mShouldQuit(false)
{

}


InputHandler::~InputHandler()
{
}

void InputHandler::checkInput()
{
	startNewFrame();

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.repeat != 0) break;
			mReleasedKeys[event.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			if (event.key.repeat != 0) break;
			mPressedKeys[event.key.keysym.scancode] = true;
			break;
		case SDL_QUIT:
			mShouldQuit = true;
			break;
		default:
			break;
		}
	}
}

void InputHandler::startNewFrame()
{
	mPressedKeys.clear();
	mReleasedKeys.clear();
}

bool InputHandler::getKeyDown(const SDL_Scancode key) const
{
	return mKeystate[key] != 0;
}

bool InputHandler::getKeyPressed(const SDL_Scancode key)
{
	return this->mPressedKeys[key];
}

bool InputHandler::getKeyReleased(const SDL_Scancode key)
{
	return mReleasedKeys[key];
}

bool InputHandler::shouldQuit() const
{
	return mShouldQuit;
}

