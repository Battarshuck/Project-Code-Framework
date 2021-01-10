#ifndef _EDIT_CONNECTION_H
#define _EDIT_CONNECTION_H

#include "action.h"
#include "..\Components\Connection.h"

class EditConnection : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area

	Component*& m_connection;
	Component* new_component;
	GraphicsInfo m_GfxInfo;

	int choice;
public:
	EditConnection(ApplicationManager* pApp, Component*&);
	virtual ~EditConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
