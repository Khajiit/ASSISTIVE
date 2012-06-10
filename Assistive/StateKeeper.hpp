#pragma once

#include <vector>
#include "State.hpp"
class StateKeeper
{
public:
	StateKeeper(void);
	~StateKeeper(void);
	void ChangeState(int value1, int value2);
	State* GetState();
	void moveUp();
	void moveDown();
	void moveForward();
	void moveBackwards();
	std::vector <State> stany;
	int getMainPos();
	int getSubPos();
private:
	
	int mainPos;
	int subPos;
	State* curr;
};

