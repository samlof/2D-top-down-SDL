#pragma once

#include <memory>

class Camera;
class World;

class Game
{
public:
	Game();
	~Game();

	void update();
	void draw();

	bool quitting() const { return mQuitting; }
	void quit() { mQuitting = true; }
private:
	bool init;
	bool mQuitting;
	std::unique_ptr<World> mWorld;
	std::unique_ptr<Camera> mCamera;
};
