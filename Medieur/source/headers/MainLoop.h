#pragma once

#include <memory>

#include "Graphics\Sprite.h"

class Game;

class MainLoop
{
public:
	MainLoop();
	~MainLoop();

	void run();
	void testRun();
	void stop() { mQuitting = true; }

private:
	bool mQuitting;
	std::unique_ptr<Game> mGame;
	float mFps;
	uint32_t mFrametime;
	void calculateFPS();
};