#include"Copy.h"
#include "..\ApplicationManager.h"

Copy::Copy(ApplicationManager* pApp, Component* CompSelected, Component*& CompcopiedAppMang,int & CopyorCut) :Action(pApp), CopiedComp(CompcopiedAppMang)
{
	ComponentToBeCopied = CompSelected;
	CopyorCut = 1;
}

Copy::~Copy(void)
{}

void Copy::ReadActionParameters()
{
	//Get a Pointer to the Output Interfaces
	Output* pOut = pManager->GetOutput();

	//Print Action Message
	pOut->PrintMsg("Copy a Componenet: Componenet is Copied");

}

void Copy::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//Calculate the rectangle Corners
	if (ComponentToBeCopied)
	{
		if (dynamic_cast<Connection*>(ComponentToBeCopied))
			pOut->PrintMsg("Error, Cannot Copy a Connection");
		else
			CopiedComp = ComponentToBeCopied;
	}
	else
		pOut->PrintMsg("Cannot Copy, Please Select a Component first");
}

void Copy::Undo()
{}

void Copy::Redo()
{}
