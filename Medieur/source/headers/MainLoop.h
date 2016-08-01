#pragma once

#include <memory>

class Game;

class MainLoop
{
public:
	MainLoop();
	~MainLoop();

	void run();
	static void stop() { mIsQuitting = true; }

private:
	std::unique_ptr<Game> mGame;
	static bool mIsQuitting;
};