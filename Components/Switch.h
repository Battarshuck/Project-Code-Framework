#pragma once
#include "Component.h"
#include "OutputPin.h"
class Switch :public Component
{
protected:
	OutputPin m_OutputPin;
public:
	Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	
	void Setswitch(STATUS s);
	
	virtual void Operate();	//Calculates the output of the AND gate
	
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);
};


