#ifndef _ADD_LED_GATE_H
#define _ADD_LED_GATE_H

#include "action.h"
#include "..\Components\LED.h"

class AddLED : public Action
{
private:
	//Parameters for rectangular area to be occupied by the LED
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	bool* cut_check;
public:
	AddLED(ApplicationManager* pApp, bool* = NULL);
	virtual ~AddLED(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
