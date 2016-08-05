#include "Game.h"

#include <SDL_timer.h>
#include <SDL_scancode.h>

#include "units.h"
#include "Graphics.h"
#include "InputHandler.h"
#include "PathFinder.h"
#include "World.h"
#include "Prototypes.h"

#include "Tile.h"
#include "GroundEntity.h"
#include "IGroundEntityModule.h"

class GroundEntity;
class PlantEntity;

namespace {

	
}

Game::Game()
	:
	mQuitting(false),
	init(Prototypes::createPrototypes()),
	mWorld(World::GenerateTestWorld()),
	mCamera(mWorld.get())
{
	PathFinder::setWorld(mWorld.get());
}
Game::~Game()
{

}

void Game::update()
{
	InputHandler inputhandler;

	mWorld->createCharacter(2, 2, Prototypes::getCharacterPrototypeByName("Guy"));

	while (!mQuitting) {
		inputhandler.checkInput();
		if (inputhandler.shouldQuit() || inputhandler.getKeyPressed(SDL_SCANCODE_ESCAPE)) mQuitting = true;

		if (inputhandler.getKeyPressed(SDL_SCANCODE_UP)) {
			mCamera.moveUp();
		}
		if (inputhandler.getKeyPressed(SDL_SCANCODE_DOWN)) {
			mCamera.moveDown();
		}
		if (inputhandler.getKeyPressed(SDL_SCANCODE_LEFT)) {
			mCamera.moveLeft();
		}
		if (inputhandler.getKeyPressed(SDL_SCANCODE_RIGHT)) {
			mCamera.moveRight();
		}
		if (inputhandler.getKeyPressed(SDL_SCANCODE_A)) {
			mCamera.moveHigher();
		}
		if (inputhandler.getKeyPressed(SDL_SCANCODE_S)) {
			mCamera.moveLower();
		}
		mWorld->update();
		draw();

		SDL_Delay(16);
	}
}

void Game::draw()
{
	Graphics::clear();

	mCamera.draw();

	Graphics::renderPresent();
}

