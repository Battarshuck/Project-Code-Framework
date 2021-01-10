#pragma once
#include "Action.h"
#include<fstream>
using namespace std;
class Save : public Action
{
private:
	ofstream outputFile;
public:
	Save(ApplicationManager* pApp);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};