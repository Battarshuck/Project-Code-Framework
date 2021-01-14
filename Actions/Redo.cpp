#include"Redo.h"
#include "..\ApplicationManager.h"

redo::redo(ApplicationManager* pApp) : Action(pApp)
{
	
}

redo::~redo(void)
{

}
void redo::ReadActionParameters()
{

}
void redo::Execute()
{
	Output* pOut = pManager->GetOutput();
	pManager->redofn();
}
void redo::Undo()
{

}
void redo::Redo()
{

}