#include "MainLoop.h"

#include <SDL_scancode.h>
#include <SDL_timer.h>

#include "Game.h"
#include "Graphics.h"
#include "InputHandler.h"

MainLoop::MainLoop()
	:
	mQuitting(false)
{
	Graphics::init();
}

MainLoop::~MainLoop()
{
	Graphics::quit();
}

void MainLoop::run()
{
	InputHandler inputhandler;
	mGame.reset(new Game());
	while (!mQuitting) {

		inputhandler.checkInput();

		if (inputhandler.shouldQuit() || inputhandler.getKeyPressed(SDL_SCANCODE_ESCAPE)) {
			mQuitting = true;
			return;
		}

		mGame->handleEvent(inputhandler);
		mGame->update();
		mGame->draw();
		SDL_Delay(16);
	}
}
