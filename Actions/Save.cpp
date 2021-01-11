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
	Input* pIn = pManager->GetInput();

	//ceck if the component list is emty or not
	if (pManager->IsCompListEmpty())
		pOut->PrintMsg("Error: Cannot Save, no Components are Added");
	else
	{
		//Print Action Message 
		pOut->PrintMsg("Save a Circuit: Please enter File Name (example.txt)  ");
		//(ifstream& inputFiles)
		//open the file
		string file_name = pIn->GetSrting(pOut);
		outputFile.open(file_name, ios::out);
		//Clear Status Bar
		pOut->ClearStatusBar();
		if (outputFile.is_open())
		{
			pManager->save(outputFile);
			pOut->PrintMsg("Save a Circuit: Circuit is Saved");
			outputFile.close();
		}
	}
}

//To undo this action (code depends on action type)
void Save::Undo()
{}

//To redo this action (code depends on action type)
void Save::Redo()
{}