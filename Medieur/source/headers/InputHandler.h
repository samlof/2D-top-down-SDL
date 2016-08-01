#pragma once

#include<map>
#include <SDL_scancode.h>

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	
	
	void checkInput();
	void startNewFrame();

	bool getKeyDown(const SDL_Scancode key) const;
	bool getKeyPressed(const SDL_Scancode key);
	bool getKeyReleased(const SDL_Scancode key);

	bool shouldQuit() const;

private:
	const Uint8 *mKeystate;
	std::map<SDL_Scancode, bool> mPressedKeys;
	std::map<SDL_Scancode, bool> mReleasedKeys;

	bool mShouldQuit;
};
