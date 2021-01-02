#include "Select.h"
#include"ApplicationManager.h"
#include"Defs.H"
#include"Components/Component.h"

//constructor
Select::Select(ApplicationManager* pApp, Component*& ComponentPassed, GraphicsInfo& r_GfxInfo) :Action(pApp), CompSelected(ComponentPassed)
{
	r_GInfo = r_GfxInfo;
	//initialize previous component to NULL
	PreviousComp = NULL;
}

//destructor
Select::~Select(void)
{

}

//Reads parameters required for action to execute
void Select::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Select a component: Click to select a component");

	//Wait for User Input
	pIn->GetPointClicked(x, y);

	//Clear Status Bar
	pOut->ClearStatusBar();

	//get componenet list
	Component** list = pManager->getCompList(size);

	//check if the click is inside area of any componenet	
	for (int i = 0; i < size; i++)
	{
		if (list[i] != NULL)
		{
			if (list[i]->InArea(x, y))
			{
				CompSelected = list[i];
				r_GInfo = list[i]->getLocation();
				break;
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (list[i] != NULL)
		{
			if (list[i] != CompSelected && list[i]->getIsSelected())
			{
				PreviousComp = list[i];
				break;
			}
		}
	}
}

//Execute action (code depends on action type)
void Select::Execute()
{
	//Get the location of the click
	ReadActionParameters();

	//make IsSelected true if initilay false
	//make IsSelected false if initilay true
	Output* pOut = pManager->GetOutput();
	if (CompSelected)
	{
		if (CompSelected->getIsSelected())
		{
			pOut->PrintMsg("Component is Unselected");
			CompSelected->setIsSelected(false);
			CompSelected = NULL;
		}
		else
		{

			pOut->PrintMsg("Component is Selected");
			CompSelected->setIsSelected(true);
		}
	}

	//unselect previous component
	if (PreviousComp)
	{
			PreviousComp->setIsSelected(false);
			PreviousComp = NULL;
	}
}

//To undo this action (code depends on action type)
void Select::Undo()
{}

//To redo this action (code depends on action type)
void Select::Redo()
{}