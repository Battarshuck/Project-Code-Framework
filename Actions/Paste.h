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
	Component* PasteComp;//component that will be pasted
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area

public:
	Paste(ApplicationManager* pApp, Component*);
	virtual ~Paste(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

};
