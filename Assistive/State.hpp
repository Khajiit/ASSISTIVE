#pragma once
#include <string>
#include <opencv2/core/core.hpp>

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
	void setImg(std::string path);
	cv::Mat getImg();
private:
	std::string name;
	int mainPos;
	int subPos;
	cv::Mat img;
};

