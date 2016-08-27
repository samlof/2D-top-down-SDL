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


void MainLoop::testRun()
{
	InputHandler inputhandler;

	std::unique_ptr<Graphics::Sprite> mSprite;
	std::unique_ptr<Graphics::Sprite> mSprite2;

	mSprite.reset(new Graphics::Sprite("content/sprites/character.png",
		-1.0f, -1.0f, 1.0f, 1.0f
	));
	mSprite2.reset(new Graphics::Sprite("content/sprites/character.png" , 
		0.0f, 0.0f, 1.0f, 1.0f
	));

	while (!mQuitting) {

		inputhandler.checkInput();

		if (inputhandler.shouldQuit() || inputhandler.getKeyPressed(SDL_SCANCODE_ESCAPE)) {
			mQuitting = true;
			return;
		}

		Graphics::clear();

		//Draw our sprite!
		mSprite->draw(1, 1);
		mSprite2->draw(1, 1);

		Graphics::flip();

		SDL_Delay(16);
	}
}
