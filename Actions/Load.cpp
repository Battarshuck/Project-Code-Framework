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
	Input* pIn = pManager->GetInput();
	
	//Print Action Message 
	pOut->PrintMsg("Load an Exicting Circuit: Please enter File Name (.txt)  ");
	string file_name = pIn->GetSrting(pOut);
	//open the file
	inputFile.open(file_name);
	//check that file_name enterred by the user already exists
	if (inputFile.is_open())
	{
		
		pOut->PrintMsg("Load File was Done successfully  ");
		pManager->load(inputFile);
		inputFile.close();
	
	}
	else
		pOut->PrintMsg("Error: File was not Found");
}

//To undo this action (code depends on action type)
void Load:: Undo()
{}

//To redo this action (code depends on action type)
void Load:: Redo()
{}