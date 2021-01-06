#include"Delete.h"
#include "..\ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp, Component*& comp) :Action(pApp), componentSelected(comp)
{

}

Delete::~Delete(void)
{
}

void Delete::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Delete::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	if (componentSelected)
	{
		pManager->Remove(componentSelected);
		componentSelected = NULL;
	}
	else
	{
		pOut->PrintMsg("Please select a component before Deleting");
	}


}

void Delete::Undo()
{}

void Delete::Redo()
{}

