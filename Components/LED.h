#ifndef _LED_H
#define _LED_H

/*
  Class LED
  -----------
  represent the LED
*/

#include "Component.h"
#include"InputPin.h"

class LED :public Component
{
protected:
	InputPin m_InputPins;	// input pin of the LED
public:
	LED(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the LED
	virtual void Draw(Output* pOut);	//Draws 1-input LED

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.


};

#endif
