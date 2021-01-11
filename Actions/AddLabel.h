#ifndef _ADD_LABEL_H
#define _ADD_LABEL_H

#include "..\Actions\Action.h"
#include "..\Components\Component.h"

class AddLabel : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	Component*& component;
	GraphicsInfo m_GfxInfo;

	Output* pOut;
	Input* pIn;
public:
	AddLabel(ApplicationManager* pApp, Component*&);
	virtual ~AddLabel(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif

