#include "Exit.h"
#include "..\ApplicationManager.h"
#include "Save.h"

Exit::Exit(ApplicationManager* pApp) :Action(pApp)
{
}

Exit::~Exit(void)
{
}

void Exit::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


}

void Exit::Execute()
{
	
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//the compList is not empty that means the drawing area contains
	//some components, here we are asking the user if wants to save his current
	//circuit before exiting the program
	if (!pManager->IsCompListEmpty())
	{
		pOut->PrintMsg("Do you want to save before exiting? (y,n)");
		string user_input = pIn->GetSrting(pOut);

		if (user_input == "y" || user_input == "Y")
		{
			 Save* psave= new Save(pManager);
			 psave->Execute();
			 delete psave;
		}
		else 
			pOut->PrintMsg("Click on Exit again to exit");
		
	}
	else
		pOut->PrintMsg("Click on Exit again to exit");

}

void Exit::Undo()
{}

void Exit::Redo()
{}

