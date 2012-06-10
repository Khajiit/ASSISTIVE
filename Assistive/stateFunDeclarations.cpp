/************************************************************************************/
/*									stateFunDeclarations.cpp						*/
/************************************************************************************/
/* Autorzy:		Marcin Marzyñski, Daniel Jagielski, Tomasz Kmiecik					*/
/* Kierunek:	III rok Informatyka Stosowana, EAIiE, AGH							*/
/* Data modyfikacji: 10-06-2012														*/
/************************************************************************************/
/*																					*/
/* Zbiór funkcji podpinanych pod stany (pozycje menu) w celach prezentacyjnych		*/
/************************************************************************************/
#include "stateFunDeclarations.hpp"
#include <iostream>

void printTest()
{
	std::cout << "TEST ACTION" << std::endl;
}

void printNextSong()
{
	std::cout << "Akcja: nastêpna piosenka" << std::endl;
}

void printPrevSong()
{
	std::cout << "Akcja: poprzednia piosenka" << std::endl;
}

void printPauseSong()
{
	std::cout << "Akcja: pauza/play" << std::endl;
}

void printEclipse()
{
	std::cout << "Akcja: uruchamiam Eclipse" << std::endl;
}

void printChrome()
{
	std::cout << "Akcja: uruchamiam Chrome" << std::endl;
}

void printCalc()
{
	std::cout << "Akcja: uruchamiam kalkulator" << std::endl;
}
