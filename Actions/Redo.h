#pragma once
#include"Action.h"
#include"..\Components\Component.h"
#include "..\GUI\Output.h"

class ApplicationManager;

class redo :public Action
{
private:
	int index;
	Component** Recycle;
public:
	redo(ApplicationManager*);

	virtual void ReadActionParameters();
	virtual void Execute();

	~redo();
	
	virtual void Undo();
	virtual void Redo();
};
