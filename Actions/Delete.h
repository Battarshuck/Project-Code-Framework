#pragma once
#include "Action.h"
#include "..\Components\Connection.h"
#include "..\Components\InputPin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\Gate.h"

class Component;

class Delete:public Action
{
private:
	Component** CompList;
	Component* ComponentIsSelected;
	int CompCount;

public:
	
	Delete(ApplicationManager* pApp, Component* &);
	virtual ~Delete(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

};

