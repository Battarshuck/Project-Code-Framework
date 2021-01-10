#pragma once
#include "Action.h"
#include<fstream>
using namespace std;
class Load : public Action
{
private:
	ifstream inputFile;
public:
	Load(ApplicationManager* pApp);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters() ;

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void Undo() ;

	//To redo this action (code depends on action type)
	virtual void Redo() ;
};