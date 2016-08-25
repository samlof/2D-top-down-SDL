#pragma once

#include <memory>

class World;
class InputHandler;

namespace Graphics {
	class Camera;
}

class Game
{
public:
	Game();
	~Game();

	void update();
	void draw();
	void handleEvent(InputHandler& pInputHandler);

private:
	std::unique_ptr<World> mWorld;
	std::unique_ptr<Graphics::Camera> mCamera;
};
