#include "Camera.h"

#include <algorithm>
#include <iostream>

#include <boost\algorithm\clamp.hpp>

#include "units.h"
#include "World.h"
#include "Tile.h"
#include "Graphics.h"
#include "SpriteManager.h"
#include "GroundEntity.h"
#include "Sprite.h"
#include "Character.h"

namespace {
	const int kCameraStep = 5;
}

Camera::Camera(World* pWorld)
	:
	mWorld(pWorld),
	mZoomAmount(1),
	mRectangle(0, 0, units::kTileSize * units::kScreenWidth, units::kTileSize * units::kScreenHeight),
	mChangeTexture(true)
{
}


Camera::~Camera()
{
	mWorld = nullptr;
}



void Camera::moveUp()
{
	mRectangle.addY(static_cast<int>(-kCameraStep * mZoomAmount));

	mChangeTexture = true;
}

void Camera::moveDown()
{
	mRectangle.addY(static_cast<int>(kCameraStep * mZoomAmount));

	mChangeTexture = true;
}

void Camera::moveRight()
{
	mRectangle.addX(static_cast<int>(kCameraStep * mZoomAmount));

	mChangeTexture = true;
}

void Camera::moveLeft()
{
	mRectangle.addX(static_cast<int>(-kCameraStep * mZoomAmount));

	mChangeTexture = true;
}

void Camera::moveHigher()
{
	if (mZoomAmount < 10)
	{
		mZoomAmount += 0.5f;
		moveUp();
		moveLeft();
		mRectangle.addWidth(static_cast<int>(kCameraStep * 4 * mZoomAmount));
		mRectangle.addHeight(static_cast<int>(kCameraStep * 3 * mZoomAmount));

		mChangeTexture = true;
	}
}

void Camera::moveLower()
{
	if (mZoomAmount > 1) {
		moveDown();
		moveRight();
		mRectangle.addWidth(static_cast<int>(kCameraStep * -4 * mZoomAmount));
		mRectangle.addHeight(static_cast<int>(kCameraStep * -3 * mZoomAmount));
		mZoomAmount -= 0.5f;

		mChangeTexture = true;
	}
}


void Camera::draw()
{
	if (mChangeTexture) {
		Graphics::changeWorldTexture(mRectangle.getWidth(), mRectangle.getHeight());
		mChangeTexture = false;
	}
	Graphics::targetWorldTexture();

	const int startTileX = std::max(mRectangle.getLeft() / units::kTileSize, 0);
	const int startTileY = std::max(mRectangle.getTop() / units::kTileSize, 0);

	const int endTileX = std::min(mRectangle.getRight() / units::kTileSize + 1, units::kWorldWidth);
	const int endTileY = std::min(mRectangle.getBottom() / units::kTileSize + 1, units::kWorldHeight);

	for (int x = startTileX; x < endTileX; x++)
	{
		for (int y = startTileY; y < endTileY; y++)
		{
			Tile* tempTile = mWorld->getTile(x, y);
			// Draw tile
			if (tempTile->getTileType() != TileType::EMPTY) {
				const int drawX = x * units::kTileSize - mRectangle.getX();
				const int drawY = y * 32 - mRectangle.getY();
				SpriteManager::getTileSprite(*tempTile)->draw(
					drawX, drawY
				);
				// Draw Ground entity
				if (tempTile->hasGroundEntity()) {
					const int id = tempTile->getGroundEntity()->getId();
					if (SpriteManager::hasEntityFunction(id)) {
						SpriteManager::getGroundEntitySpriteById(id)->draw(
							drawX, drawY, SpriteManager::getEntityFunction(id)(tempTile->getGroundEntity().get())
						);
					}
					else {
						SpriteManager::getGroundEntitySpriteById(id)->draw(
							drawX, drawY
						);
					}
				}

				// Draw character
				if (tempTile->isCharacterOn()) {
					SpriteManager::getCharacterSprite(tempTile->getCharacter())->draw(
						drawX, drawY
					);
				}
			}
		}
	}

	Graphics::resetTarget();
}