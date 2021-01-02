#include "AddLabel.h"
#include "..\ApplicationManager.h"

AddLabel::AddLabel(ApplicationManager* pApp, Component* & componentSelected) :Action(pApp), component(componentSelected)
{
	 pOut = pManager->GetOutput();
	 pIn = pManager->GetInput();
}

AddLabel::~AddLabel(void)
{
}

void AddLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on the component you want to add label for");

}

void AddLabel::Execute()
{
	ReadActionParameters();
	

	if (component)
	{
		if (component->getLabel().empty()) 
		{
			pOut->PrintMsg("Enter component label");
			string label = pIn->GetSrting(pOut);
			component->setLabel(label);
		}
		else
		{
			pOut->PrintMsg("ERROR: component already has a label. Please use edit label instead");
		}
	}
	else
	{
		pOut->PrintMsg("Please select a component before Adding Label");
	}
}

void AddLabel::Undo()
{}

void AddLabel::Redo()
{}

