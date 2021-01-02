#include"Delete.h"
#include "..\ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp, Component*& Componentselect) : Action(pApp)
{

	CompList = pApp->getCompList(CompCount);

	ComponentIsSelected = Componentselect;
}

Delete::~Delete(void)
{
}

void Delete::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces

	Output* pOut = pManager->GetOutput();

	Input* pIn = pManager->GetInput();

	//Print Action Message

	pOut->PrintMsg("The selected component will be deleted");

}

void Delete::Execute()
{
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();

	int i;

	for (i = 0; i < CompCount; i++)
	{
		if (CompList[i] == ComponentIsSelected)

			break;
	}
	if (i < CompCount)
	{

		Component* PH = CompList[i]; //PH is a place holder

		*CompList[i] = *CompList[CompCount - 1];
		
		*CompList[CompCount - 1] = *PH;
		
		delete CompList[CompCount - 1];
		
		CompList[CompCount - 1] = NULL;

		CompCount--;

	}
	

}
void Delete::Undo()
{
}

void Delete::Redo()
{
}