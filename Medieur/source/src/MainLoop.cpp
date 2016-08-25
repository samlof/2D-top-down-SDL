#include "MainLoop.h"

#include <SDL_scancode.h>
#include <SDL_timer.h>

#include "Graphics\Graphics.h"

#include "Game.h"
#include "InputHandler.h"
#include "Prototypes.h"

MainLoop::MainLoop()
	:
	mQuitting(false)
{
	Graphics::init();
	//Prototypes::createPrototypes();
}

MainLoop::~MainLoop()
{
	Prototypes::clearAll();
	Graphics::quit();
}

void MainLoop::run()
{
	testRun();
	return;
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

#include <GL\glew.h>
#include <SDL_opengl.h>
#include <SDL.h>

#include "Graphics\GLSLProgram.h"

void MainLoop::testRun()
{
	InputHandler inputhandler;

	mSprite = new Graphics::Sprite("Ukko.png", 1, 1, 1, 1);
	mSprite->init();
	while (!mQuitting) {

		inputhandler.checkInput();

		if (inputhandler.shouldQuit() || inputhandler.getKeyPressed(SDL_SCANCODE_ESCAPE)) {
			mQuitting = true;
			return;
		}

		Graphics::clear();

		//Draw our sprite!
		mSprite->draw(1, 1);

		Graphics::flip();

		SDL_Delay(16);
	}
}
