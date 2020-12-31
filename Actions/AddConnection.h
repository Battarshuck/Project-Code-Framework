#ifndef _ADD_CONNECTION_H
#define _ADD_CONNECTION_H

#include "action.h"
#include "..\Components\Connection.h"
#include "..\Components\InputPin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\Gate.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"

class AddConnection : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Px1, Py1, Px2, Py2;
	int Sx1, Sy1, Sx2, Sy2, Dx1, Dx2, Dy1, Dy2;	

	Component* source;
	Component* destination;
	Component* check;
	GraphicsInfo m_GfxInfo;

	int CompCount;

	OutputPin* pSrcPin;
	InputPin* pDstPin;

	int InputPinNumber;
	int m_Inputs;
	int source_OutputConnections;
public:
	AddConnection(ApplicationManager* pApp);
	virtual ~AddConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
