#pragma once
#include"Action.h"
#include"..\Components\Component.h"
#include"..\GUI\Output.h"

class ApplicationManager;

class undo :public Action
{
private:
	Component* ComponentUndo;
public:
	undo(ApplicationManager*);
	
	virtual void ReadActionParameters();
	virtual void Execute();
	
	~undo();
	virtual void Undo();
	virtual void Redo();
};
