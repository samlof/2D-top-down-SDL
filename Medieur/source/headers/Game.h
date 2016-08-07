#pragma once

#include <memory>

class Camera;
class World;
class InputHandler;

class Game
{
public:
	Game();
	~Game();

	void update();
	void draw();
	void handleEvent(InputHandler& pInputHandler);

private:
	bool init;
	std::unique_ptr<World> mWorld;
	std::unique_ptr<Camera> mCamera;
};
