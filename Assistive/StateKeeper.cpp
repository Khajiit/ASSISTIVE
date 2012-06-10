#include "StateKeeper.hpp"
#include "stateFunDeclarations.hpp"


StateKeeper::StateKeeper(void) 
{
	State* stan1 = new State();
	State* stan11 = new State();
	State* stan12 = new State();
	State* stan13 = new State();
	State* stan14 = new State();
	State* stan2 = new State();
	State* stan21 = new State();
	State* stan22 = new State();
	State* stan23 = new State();
	State* stan24 = new State();
	State* stan3 = new State();

	//Stan 1:0 - g³ówny
	stan1->setname("Main 1");
	stan1->setMainPos(1);
	stan1->setSubPos(0);
	stan1->func = &printTest;
	stan1->setImg("menu_img/menu00.jpg");

	//Stan 1:1 - back
	stan11->setname("Back 1");
	stan11->setMainPos(1);
	stan11->setSubPos(1);
	stan11->func = &printTest;
	stan11->setImg("menu_img/sub01.jpg");

	//Stan 1:2 - sub
	stan12->setname("Sub 1");
	stan12->setMainPos(1);
	stan12->setSubPos(2);
	stan12->func = &printPrevSong;
	stan12->setImg("menu_img/sub02.jpg");

	//Stan 1:3 - sub
	stan13->setname("Sub 2");
	stan13->setMainPos(1);
	stan13->setSubPos(3);
	stan13->func = &printPauseSong;
	stan13->setImg("menu_img/sub03.jpg");

	//Stan 1:4 - sub
	stan14->setname("Sub 3");
	stan14->setMainPos(1);
	stan14->setSubPos(4);
	stan14->func = &printNextSong;
	stan14->setImg("menu_img/sub04.jpg");

	//Stan 2:0 - g³ówny
	stan2->setname("Main 2");
	stan2->setMainPos(2);
	stan2->setSubPos(0);
	stan2->func = &printTest;
	stan2->setImg("menu_img/menu10.jpg");

	//Stan 2:1 - back
	stan21->setname("Back 2");
	stan21->setMainPos(2);
	stan21->setSubPos(1);
	stan21->func = &printTest;
	stan21->setImg("menu_img/sub11.jpg");

	//Stan 2:2 - sub 
	stan22->setname("Sub 1");
	stan22->setMainPos(2);
	stan22->setSubPos(2);
	stan22->func = &printEclipse;
	stan22->setImg("menu_img/sub12.jpg");

	//Stan 2:3 - sub 
	stan23->setname("Sub 2");
	stan23->setMainPos(2);
	stan23->setSubPos(3);
	stan23->func = &printChrome;
	stan23->setImg("menu_img/sub13.jpg");

	//Stan 2:4 - sub 
	stan24->setname("Sub 3");
	stan24->setMainPos(2);
	stan24->setSubPos(4);
	stan24->func = &printCalc;
	stan24->setImg("menu_img/sub14.jpg");

	//Stan 3:0 - g³ówny
	stan3->setname("Main 3");
	stan3->setMainPos(3);
	stan3->setSubPos(0);
	stan3->func = &printTest;
	stan3->setImg("menu_img/menu20.jpg");

	stany.push_back(*stan1);
	stany.push_back(*stan11);
	stany.push_back(*stan12);
	stany.push_back(*stan13);
	stany.push_back(*stan2);
	stany.push_back(*stan21);
	stany.push_back(*stan22);
	stany.push_back(*stan23);
	stany.push_back(*stan24);
	stany.push_back(*stan3);

	mainPos = 1;
	subPos = 0;
}


StateKeeper::~StateKeeper(void) 
{
}

// poruszanie sie 
void StateKeeper::moveUp()
{
	ChangeState(mainPos, 0);
}

void StateKeeper::moveDown()
{
	ChangeState(mainPos, 1);
}

void StateKeeper::moveForward()
{
	if(subPos == 0)
		ChangeState(mainPos + 1, subPos);
	else
		ChangeState(mainPos, subPos + 1);
}

void StateKeeper::moveBackwards() 
{
	if(subPos == 0)
		ChangeState(mainPos - 1, subPos);
	else
		ChangeState(mainPos, subPos - 1);
}

//pobieranie stanu

State* StateKeeper::GetState() 
{
	for(std::vector<State>::iterator it = stany.begin(); it != stany.end(); ++it) 
	{
		if ( ( mainPos == it->getMainPos() ) && ( subPos == it->getSubPos() ))
			return &(*it);
	}
	return 0;
	//return findState(mainPos, subPos);
}

// zmiana stanu

void StateKeeper::ChangeState(int value1, int value2) 
{

	for(std::vector<State>::iterator it = stany.begin(); it != stany.end(); ++it) 
	{

		if ( ( value1 == it->getMainPos() ) && ( value2 == it->getSubPos() )) 
		{
			mainPos = value1;
			subPos = value2;
			/*curr.setcols(it->getSubPos());
			curr.setrows(it->getMainPos());
			curr.setname(it->getname());
			curr.setfunc(it->getfunc());*/
		}

	}
}

State& StateKeeper::findState(int value1, int value2) 
{

	for(std::vector<State>::iterator it = stany.begin(); it != stany.end(); ++it) 
	{
		//if ( ( value1 == it->getMainPos() ) && ( value2 == it->getSubPos() ))
		//{
			return *it;
		//}
	}

	//return 0;
}

int StateKeeper::getMainPos()
{
	return mainPos;
}
int StateKeeper::getSubPos()
{
	return subPos;
}

