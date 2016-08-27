#include "MainLoop.h"

#include <SDL_scancode.h>
#include <SDL_timer.h>

#include "Graphics\Graphics.h"

#include "Game.h"
#include "InputHandler.h"
#include "Prototypes.h"


namespace {
	const int kMaxFps = 60;

	float msToFPS(Uint32 pMs) {
		return 1000.0f / pMs;
	}
}
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
	mSprite2.reset(new Graphics::Sprite("content/sprites/character.png",
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

		calculateFPS();

		static int printFPS = 0;
		if (++printFPS == 10) {
			printf("FPS: %f\n", mFps);
			printFPS = 0;
		}

		int timeToDelay = (1000.0f / kMaxFps) - mFrametime;
		if (timeToDelay > 5) {
			SDL_Delay(timeToDelay);
		}
	}
}

void MainLoop::calculateFPS()
{
	static const int NUM_SAMPLES = 8;
	static Uint32 frameTimes[NUM_SAMPLES];
	static int currentFrame = 1;

	static Uint32 prevTicks = SDL_GetTicks();

	Uint32 currentTicks;
	currentTicks = SDL_GetTicks();

	mFrametime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = mFrametime;
	prevTicks = currentTicks;
	currentFrame++;

	int count;
	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	Uint32 frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		mFps = msToFPS(frameTimeAverage);
	}
	else {
		mFps = 60;
	}
}
