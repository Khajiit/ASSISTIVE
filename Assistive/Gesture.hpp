#pragma once
class Gesture
{
public:
	Gesture(void);
	~Gesture(void);

	static const int GESTURE_UNKNOWN = 0;
	static const int GESTURE_RHAND_LEFT = 1;
	static const int GESTURE_RHAND_RIGHT = 2;

	int type;
};

