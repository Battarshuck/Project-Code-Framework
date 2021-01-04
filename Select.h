#pragma once
#include"Actions/Action.h"
#include"Components/Component.h"
#include"Defs.H"

class Select :public Action
{
private:
	// pointer to componenet selected 
	Component* &CompSelected;

	//size of componenet list
	int size;

	//
	GraphicsInfo r_GInfo;

	//Parameters for rectangular area to be occupied by the gate
	int x, y;	//location of point clicked
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	GraphicsInfo m_GfxInfo;
public:
	//constructor
	Select(ApplicationManager* pApp, Component*&, GraphicsInfo& r_GfxInfo);

	//destructor
	~Select();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();




	//Execute action (code depends on action type)
	virtual void Execute();

	//To undo this action (code depends on action type)
	virtual void Undo();


	//To redo this action (code depends on action type)
	virtual void Redo();


};