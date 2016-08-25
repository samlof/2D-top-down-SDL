#pragma once

#include "Rectangle.h"

class World;

class Camera
{
public:
	Camera(World* pWorld);
	~Camera();


	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void moveHigher();
	void moveLower();

	int getY() const { return mRectangle.getY(); }
	int getX() const { return mRectangle.getX(); }
	Rectangle getRectangle() const { return mRectangle; }
	
	void draw();

private:
	float mZoomAmount;
	bool mChangeTexture;
	Rectangle mRectangle;
	World* mWorld;
	
	void drawTile(const int x, const int y);
};

