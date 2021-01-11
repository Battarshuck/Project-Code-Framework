#pragma once
#include"Action.h"
#include "..\Components\Connection.h"
#include "..\Components\InputPin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\Gate.h"
#include "..\Components\Gate.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"


class Paste :public Action
{
private:
	Component*& DeleteComp;//pointer to Sellected Component that will be Deleted (Used Only if the previous action was cut)
	Component*& SelectedComp;//pointer to Sellected Component that will be Unselected 
	Component* PasteComp;//pointer to Component that will be pasted	
	int* copyorcut; //pointer to integer that distinguish between the Cut and Copy (The Previous Action Excuted)
	bool cut_check;//this variable check if the paste was succesful for a cut component so it can delete the old one
public:
	Paste(ApplicationManager* pApp, Component*&, Component*&, int*&);
	virtual ~Paste(void);

	//Reads parameters required for action to execute
	
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	
	virtual void Execute();

	virtual void Undo();
	
	virtual void Redo();

};
