#include "Game.h"

#include <SDL_scancode.h>

#include "Graphics\Graphics.h"
#include "Graphics\Camera.h"

#include "World.h"
#include "PathFinder.h"
#include "Prototypes.h"
#include "InputHandler.h"


Game::Game()
	:
	mWorld(World::GenerateTestWorld()),
	mCamera(new Camera(mWorld.get()))
{
	PathFinder::setWorld(mWorld.get());
	mWorld->createCharacter(2, 2, Prototypes::getIdByName("Guy"));
}
Game::~Game() = default;

void Game::update()
{
	mWorld->update();
}

void Game::draw()
{
	Graphics::clear();

	mCamera->draw();

	Graphics::renderPresent();
}

void Game::handleEvent(InputHandler & pInputHandler)
{
	if (pInputHandler.getKeyPressed(SDL_SCANCODE_UP)) {
		mCamera->moveUp();
	}
	if (pInputHandler.getKeyPressed(SDL_SCANCODE_DOWN)) {
		mCamera->moveDown();
	}
	if (pInputHandler.getKeyPressed(SDL_SCANCODE_LEFT)) {
		mCamera->moveLeft();
	}
	if (pInputHandler.getKeyPressed(SDL_SCANCODE_RIGHT)) {
		mCamera->moveRight();
	}
	if (pInputHandler.getKeyPressed(SDL_SCANCODE_A)) {
		mCamera->moveHigher();
	}
	if (pInputHandler.getKeyPressed(SDL_SCANCODE_S)) {
		mCamera->moveLower();
	}
}

