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
	
	int CompCount, Px1, Py1;
public:
	
	Delete(ApplicationManager* pApp);
	virtual ~Delete(void);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

};

