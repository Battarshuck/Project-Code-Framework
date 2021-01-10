#include"Load.h"
#include "..\ApplicationManager.h"

Load::Load(ApplicationManager* pApp) :Action(pApp)
{}
//Reads parameters required for action to execute
void Load::ReadActionParameters()
{}

//Execute action (code depends on action type)
void Load::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	//Print Action Message
	pOut->PrintMsg("Load an Existing File ");
	//(ifstream& inputFiles)
	//open the file
	inputFile.open("circuit_1.txt");
	if (inputFile.is_open())
	{
		pManager->load(inputFile);
	}
	else
		pOut->PrintMsg("Error, File was not Found");

}

//To undo this action (code depends on action type)
void Load:: Undo()
{}

//To redo this action (code depends on action type)
void Load:: Redo()
{}