#ifndef _INV_H
#define _INV_H

/*
  Class INV
  -----------
  represent the inverter
*/

#include "Gate.h"

class INV :public Gate
{
public:
	INV(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	virtual void SaveComponent(ofstream&);//save NOT gate
	virtual int* LoadComponent(ifstream& inputFile);//Load NOT gate

};

#endif
