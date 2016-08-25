#pragma once

#include "Point.h"

class Rectangle
{
public:
	Rectangle(Point& pPoint, int pWidth, int pHeight):
		mPosition(pPoint), mWidth(pWidth), mHeight(pHeight) {}
	Rectangle(int pX, int pY, int pWidth, int pHeight):
		Rectangle(Point{pX, pY}, pWidth, pHeight) {}
	Rectangle() : Rectangle(0, 0, 0, 0) {}

	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }
	int getX() const { return mPosition.getX(); }
	int getY() const { return mPosition.getY(); }
	Point getPosition() { return mPosition; }

	void setXY(const Point& pPoint) { mPosition.setPoint(pPoint); }
	void setXY(const int pX, const int pY) { mPosition.setXY(pX, pY); }
	void setY(const int pY) { mPosition.setY(pY); }
	void setX(const int pX) { mPosition.setX(pX); }
	void setWidth(const int pWidth) { mWidth = pWidth; }
	void setHeight(const int pHeight) { mHeight = pHeight; }
	void addY(const int pY) { mPosition.addY(pY); }
	void addX(const int pX) { mPosition.addX(pX); }
	void addWidth(const int pWidth) { mWidth += pWidth; }
	void addHeight(const int pHeight) { mHeight += pHeight; }

	int getLeft() const { return mPosition.getX(); }
	int getRight() const { return mPosition.getX() + mWidth; }
	int getTop() const { return mPosition.getY(); }
	int getBottom() const { return mPosition.getY() + mHeight; }

private:
	Point mPosition;
	int mWidth, mHeight;
};
