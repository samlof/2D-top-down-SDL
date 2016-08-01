#include "..\headers\Point.h"

#include <utility>

Point::Point(const Point && pPoint)
	: mX(std::move(pPoint.getX())), mY(std::move(pPoint.getY())) {
}

unsigned int Point::distanceTo(const Point& pPoint) const
{
	int dx = this->mX - pPoint.mX;
	int dy = this->mY - pPoint.mY;

	return abs(dx) + abs(dy);
}

Point& Point::operator=(const Point & rhs)
{
	this->mX = rhs.mX;
	this->mY = rhs.mY;
	return *this;
}
