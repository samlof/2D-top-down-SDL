#include "Rectangle.h"


Rectangle::Rectangle()
	:
	Rectangle(0, 0, 0, 0)
{
}

Rectangle::Rectangle(Point & pPoint, int pWidth, int pHeight)
	:
	mPosition(pPoint),
	mWidth(pWidth), mHeight(pHeight)
{
}


Rectangle::Rectangle(int pX, int pY, int pWidth, int pHeight)
	:
	mPosition(pX, pY),
	mWidth(pWidth), mHeight(pHeight)
{
}

#pragma region Gets and sets
int Rectangle::getWidth() const
{
	return mWidth;
}

int Rectangle::getHeight() const
{
	return mHeight;
}

int Rectangle::getX() const
{
	return mPosition.getX();
}

int Rectangle::getY() const
{
	return mPosition.getY();
}
Point Rectangle::getPosition() const
{
	return mPosition;
}
void Rectangle::setXY(const Point & pPoint)
{
	mPosition.setPoint(pPoint);
}
void Rectangle::setXY(const int pX, const int pY)
{
	mPosition.setXY(pX, pY);
}
void Rectangle::setY(const int pY)
{
	mPosition.setY(pY);
}
void Rectangle::setX(const int pX)
{
	mPosition.setX(pX);
}
void Rectangle::setWidth(const int width)
{
	mWidth = width;
}
void Rectangle::setHeight(const int height)
{
	mHeight = height;
}
void Rectangle::addY(const int pY)
{
	mPosition.addY(pY);
}
void Rectangle::addX(const int pX)
{
	mPosition.addX(pX);
}
void Rectangle::addWidth(const int pWidth)
{
	mWidth += pWidth;
}
void Rectangle::addHeight(const int pHeight)
{
	mHeight += pHeight;
}
int Rectangle::getLeft() const
{
	return mPosition.getX();
}
int Rectangle::getRight() const
{
	return mPosition.getX() + mWidth;
}
int Rectangle::getTop() const
{
	return mPosition.getY();
}
int Rectangle::getBottom() const
{
	return mPosition.getY() + mHeight;
}
#pragma endregion
