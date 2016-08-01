#pragma once

#include "Point.h"

class Rectangle
{
public:
	Rectangle();
	Rectangle(Point& pPoint, int pWidth, int pHeight);
	Rectangle(int pX, int pY, int pWidth, int pHeight);

	int getWidth() const;
	int getHeight() const;
	int getX() const;
	int getY() const;
	Point getPosition() const;

	void setXY(const Point& pPoint);
	void setXY(const int pX, const int pY);
	void setY(const int pY);
	void setX(const int pX);
	void setWidth(const int pWidth);
	void setHeight(const int pHeight);
	void addY(const int pY);
	void addX(const int pX);
	void addWidth(const int pWidth);
	void addHeight(const int pHeight);

	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;

private:
	Point mPosition;
	int mWidth, mHeight;
};
