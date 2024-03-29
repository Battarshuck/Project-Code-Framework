#ifndef _ADD_OR2_GATE_H
#define _ADD_OR2_GATE_H

#include "action.h"
#include "..\Components\OR2.h"

class AddORgate2 : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	bool* cut_check;
public:
	AddORgate2(ApplicationManager* pApp, bool* = NULL);
	virtual ~AddORgate2(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
