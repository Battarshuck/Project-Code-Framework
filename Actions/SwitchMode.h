#ifndef _SWITCH_MODE_H
#define _SWITCH_MODE_H

#include "..\Actions\Action.h"
#include "..\GUI\UI_Info.h"

class SwitchMode : public Action
{
private:
	MODE m_mode;
public:
	SwitchMode(ApplicationManager* pApp, MODE);
	virtual ~SwitchMode(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif


