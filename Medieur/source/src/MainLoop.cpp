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
	Graphics::GLSLProgram shader;
	
	SDL_Window* _window = Graphics::getwindow();
	mSprite = new Graphics::Sprite("Ukko.png", 1, 1, 1, 1);
	mSprite->init();
	while (!mQuitting) {

		inputhandler.checkInput();

		if (inputhandler.shouldQuit() || inputhandler.getKeyPressed(SDL_SCANCODE_ESCAPE)) {
			mQuitting = true;
			return;
		}

		//Set the base depth to 1.0
		glClearDepth(1.0);
		//Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		//Draw our sprite!
		mSprite->draw(1, 1);

		shader.unuse();

		//Swap our buffer and draw everything to the screen!
		SDL_GL_SwapWindow(_window);
		SDL_Delay(16);
	}
}
