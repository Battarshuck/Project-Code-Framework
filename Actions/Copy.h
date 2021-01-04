#pragma once
#include"Action.h"
#include "..\Components\Connection.h"
#include "..\Components\InputPin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\Gate.h"
#include "..\Components\Gate.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"

class Copy :public Action
{
private:
	Component* ComponentToBeCopied;//component to be copied (just Selected)
	Component*& CopiedComp;//copied component (will be passed to Application Mansger)
	int x, y;	// location of point clicked

public:
	Copy(ApplicationManager* pApp, Component*, Component*&,int&);
	virtual ~Copy(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
