/************************************************************************************/
/*									State.cpp								*/
/************************************************************************************/
/* Autorzy:		Marcin Marzyñski, Daniel Jagielski, Tomasz Kmiecik					*/
/* Kierunek:	III rok Informatyka Stosowana, EAIiE, AGH							*/
/* Data modyfikacji: 10-06-2012														*/
/************************************************************************************/
/*																					*/
/* Klasa przechowuj¹ca stan dla maszyny stanów StateKeeper. Posiada informacjê		*/
/* o powi¹zanej ikonce menu dla tego stanu oraz o funkcji, któr¹ nalezy wykonaæ przy*/
/* aktywacji tego stanu																*/
/************************************************************************************/
#include "State.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

State::State(void)
{
}


State::~State(void)
{
}

//gettery
std::string State::getname() {
	return name;
}

int State::getMainPos() {
	return mainPos;
}


int State::getSubPos() {
	return subPos;
}

/*void* State::getFunc(){
	return func;
}*/

//settery
void State::setMainPos(int newvalue) 
{
	mainPos = newvalue;
}


void State::setSubPos(int newvalue) 
{
	 subPos = newvalue;
}

/*void State::setfunc(void* newvalue) {
	func = newvalue;
}*/

void State::setname(std::string newname)
{
	name = newname;
}

void State::setImg(std::string path)
{
	img = cv::imread(path);
}

cv::Mat State::getImg()
{
	return img;
}

/*
State& State::operator= (State const& ex)
{
     name = ex.name;
     wiersz = ex.wiersz;
	 kolumna = ex.kolumna;
	 func = ex.func;
	 return *this;
}
 */