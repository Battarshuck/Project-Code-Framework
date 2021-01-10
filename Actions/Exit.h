#ifndef _EXIT_GATE_H
#define _EXIT_GATE_H

#include "action.h"
#include "..\Components\AND2.h"

class Exit : public Action
{
private:

public:
	Exit(ApplicationManager* pApp);
	virtual ~Exit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif