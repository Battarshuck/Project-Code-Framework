#ifndef _DELETE_H
#define _DELETE_H

#include "action.h"
#include"../Components/Component.h"

class Delete : public Action
{
private:
	//the selected component 
	Component*& componentSelected;
public:
	Delete(ApplicationManager* pApp, Component*&);
	virtual ~Delete(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
