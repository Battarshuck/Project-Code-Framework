#ifndef _XOR3_H
#define _XOR3_H

/*
  Class XOR3
  -----------
  represent the 3-input XOR gate
*/

#include "Gate.h"

class XOR3 :public Gate
{
public:
	XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 3-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	virtual void SaveComponent(ofstream&);//save XOR3 gate
	virtual int* LoadComponent(ifstream& inputFile);//Load XOR3 gate
};

#endif
