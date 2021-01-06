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
	int Cx, Cy;	//Center point of the gate	
	int x1, y1, x2, y2;	//Two corners of the rectangluar area	
	int* copyorcut; //pointer to integer that distinguish between the Cut and Copy (The Previous Action Excuted)
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
