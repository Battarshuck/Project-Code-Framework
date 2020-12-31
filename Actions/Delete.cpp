#include"Delete.h"
#include "..\ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp) : Action(pApp)
{
	Px1 = 0; Py1 = 0;
	CompList = pApp->getCompList(CompCount);
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
	pOut->PrintMsg("Click on The component you want to delete");

	//Wait for User Input
	pIn->GetPointClicked(Px1, Py1);
}

void Delete::Execute()
{
	ReadActionParameters();

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
			if (CompList[i]->InArea(Px1, Py1))
			{
				Component* PH;
				
				PH = CompList[i];
				
				CompList[i] = CompList[CompCount - 1];
				
				CompList[CompCount - 1] = PH;
				
				delete CompList[CompCount-1];
				
				CompList[CompCount - 1] = NULL;

			}
		}

	}
}
	void Delete::Undo()
	{
	}

	void Delete::Redo()
	{
	}