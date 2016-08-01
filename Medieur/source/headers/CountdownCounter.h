#pragma once

class CountdownCounter {
public:
	CountdownCounter(const int pMax) : mMax(pMax), mCurrent(0), mPaused(false) {}
	void step() { if(mPaused == false) mCurrent++; }
	bool expired() { return mCurrent >= mMax; }
	void reset() { mCurrent = 0; }
	void pause() { mPaused = true; }
	void unpause() { mPaused = false; }
	void changeCurrent(const int pNew) { mCurrent = pNew; }
private:
	const int mMax;
	int mCurrent;
	bool mPaused;
};