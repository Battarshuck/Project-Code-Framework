#include"Save.h"
#include "..\ApplicationManager.h"

Save::Save(ApplicationManager* pApp) :Action(pApp)
{}
//Reads parameters required for action to execute
void Save::ReadActionParameters()
{}

//Execute action (code depends on action type)
void Save::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	//Print Action Message
	pOut->PrintMsg("Save a Cuircuit ");
	//(ifstream& inputFiles)
	//open the file
	outputFile.open("circuit_2.txt", ios::out);
	if (outputFile.is_open())
	{
		pManager->save(outputFile);
	}

}

//To undo this action (code depends on action type)
void Save::Undo()
{}

//To redo this action (code depends on action type)
void Save::Redo()
{}