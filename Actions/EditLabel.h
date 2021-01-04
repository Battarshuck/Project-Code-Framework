#ifndef _EDIT_LABEL_H
#define _EDIT_LABEL_H

#include "..\Actions\Action.h"
#include "..\Components\Component.h"

class EditLabel : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	Component*& component;
	GraphicsInfo m_GfxInfo;

	Output* pOut;
	Input* pIn;
public:
	EditLabel(ApplicationManager* pApp, Component*&);
	virtual ~EditLabel(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif


