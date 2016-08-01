#include "MainLoop.h"

#include "Game.h"
#include "Graphics.h"

bool MainLoop::mIsQuitting = false; // static

MainLoop::MainLoop()
{
	Graphics::init();
	run();
}


MainLoop::~MainLoop()
{
	Graphics::quit();
}

void MainLoop::run()
{
	mGame.reset(new Game());
	while (!mIsQuitting) {
		mGame->update();
		if (mGame->quitting()) mIsQuitting = true;
	}
}
