#ifndef _EDIT_CONNECTION_H
#define _EDIT_CONNECTION_H

#include "action.h"
#include "..\Components\Connection.h"


class EditConnection : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate

	Component*& m_connection;
	Component* new_component;
	GraphicsInfo m_GfxInfo;

	string choice;
public:
	EditConnection(ApplicationManager* pApp, Component*&);
	virtual ~EditConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	bool is_digits(const string&);

	virtual void Undo();
	virtual void Redo();


};

#endif
