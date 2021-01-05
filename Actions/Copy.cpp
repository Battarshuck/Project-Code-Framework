#include"Copy.h"
#include "..\ApplicationManager.h"

Copy::Copy(ApplicationManager* pApp, Component* CompSelected, Component*& CompcopiedAppMang,int* & CopyorCut) :Action(pApp), CopiedComp(CompcopiedAppMang),CopyOrCut_ptr(CopyorCut)
{
	ComponentToBeCopied = CompSelected;
	//CopyorCut = 1;
}

Copy::~Copy(void)
{}

void Copy::ReadActionParameters()
{}

void Copy::Execute()
{
	Output* pOut = pManager->GetOutput();

	//Calculate the rectangle Corners
	if (ComponentToBeCopied)
	{
		if (dynamic_cast<Connection*>(ComponentToBeCopied))
			pOut->PrintMsg("Error, Cannot Copy a Connection");
		else
		{
			CopiedComp = ComponentToBeCopied;
			*CopyOrCut_ptr = 1;
			//Print Action Message
			pOut->PrintMsg("Copy a Componenet: Componenet is Copied");
		}
	}
	else
		pOut->PrintMsg("Cannot Copy, Please Select a Component first");
}

void Copy::Undo()
{}

void Copy::Redo()
{}
