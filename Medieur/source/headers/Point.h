#pragma once

class Point
{
public:
	Point(const int x, const int y) : mX(x), mY(y){}
	Point(const Point& pPoint) : mX(pPoint.mX), mY(pPoint.mY) {}
	Point(const Point&& pPoint);
	Point() : mX(0), mY(0) {};

	int getX() const { return mX; }
	int getY() const { return mY; }
	void setY(const int pY) { mY = pY; }
	void setX(const int pX) { mX = pX; }
	void setXY(const int pX, const int pY) { mX = pX; mY = pY; }
	void setPoint(const Point& pPoint) { mX = pPoint.mX; mY = pPoint.mY; }
	void addY(const int pY) { mY += pY; }
	void addX(const int pX) { mX += pX; }

	unsigned int distanceTo(const Point& pPoint) const;

	Point& operator=(const Point& rhs);


private:
	int mX, mY;
};

