#include"Delete.h"
#include "..\ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp, Component*& Componentselect, int& size) : Action(pApp), CompCount(size)
{

	CompList = pApp->getCompList();

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

	pOut->PrintMsg("Selected Component is deleted");

}

void Delete::Execute()
{
	Output* pOut = pManager->GetOutput();

	ReadActionParameters();
	/// //////////////////////////////
	if (ComponentIsSelected)
	{

		//deleting component connections
		for (int i = 0; i < CompCount; i++)
		{
			if (dynamic_cast<Gate*>(ComponentIsSelected))
			{
				for (int j = i; j < CompCount; j++)
				{
					// shift every element to the left
					CompList[j] = CompList[j + 1];
					CompCount--;
				}


			}
			else if(dynamic_cast<Switch*>(ComponentIsSelected))
			{

			}
			else
			{

			}
		}
		
		/// ////////////////////////////
		
		int i;

		for (i = 0; i < CompCount; i++)
		{
			if (CompList[i] == ComponentIsSelected)
				break;
		}

		if (i < CompCount)
		{

			// for loop to delete the component
			for (int j = i; j < CompCount; j++)
			{
				// shift every element to the left
				CompList[j] = CompList[j + 1];
			}

			CompCount--;

		}
	}
	else 
	{
		pOut->PrintMsg("Please select a component before Deleting");
	}

}
void Delete::Undo()
{
}

void Delete::Redo()
{
}