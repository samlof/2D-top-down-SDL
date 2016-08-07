#pragma once

#include <memory>

class Game;

class MainLoop
{
public:
	MainLoop();
	~MainLoop();

	void run();
	void stop() { mQuitting = true; }

private:
	bool mQuitting;
	std::unique_ptr<Game> mGame;
};