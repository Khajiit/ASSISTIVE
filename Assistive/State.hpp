#pragma once
#include <string>

typedef void (* fun_ptr)();

class State
{
public:
	State(void);
	~State(void);
	
	std::string getname();
	//void* getFunc();
	int getMainPos();
	int getSubPos();
	void setname(std::string name);
	//void setfunc(void*);
	void setMainPos(int);
	void setSubPos(int);
	fun_ptr func;
private:
	std::string name;
	int mainPos;
	int subPos;
};

