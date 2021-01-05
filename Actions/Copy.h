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
	Component* ComponentToBeCopied;//Pointer to Component to be Copied (just Selected)
	Component*& CopiedComp;//Pointer to Copied Component (will be passed to Application Mansger)
	int x, y;	// location of point clicked
	int* CopyOrCut_ptr;//pointer to integer will be assigned to "1" if a Component is Copied
public:
	Copy(ApplicationManager* pApp, Component*, Component*&,int*&);
	virtual ~Copy(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
