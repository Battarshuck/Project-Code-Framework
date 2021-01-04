#include"EditLabel.h"
#include "..\ApplicationManager.h"

EditLabel::EditLabel(ApplicationManager* pApp, Component*& componentSelected) :Action(pApp), component(componentSelected)
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
}

EditLabel::~EditLabel(void)
{
}

void EditLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

}

void EditLabel::Execute()
{
	ReadActionParameters();

	if (component)
	{
		if (!component->getLabel().empty())
		{
			pOut->PrintMsg("Enter component label");
			string label = pIn->GetSrting(pOut);
			component->setLabel(label);
		}
		else
		{
			pOut->PrintMsg("ERROR: component does not have a label, Please Add Label before Editing");
		}
	}
	else
	{
		pOut->PrintMsg("Please select a component before Editing Label");
	}
}

void EditLabel::Undo()
{}

void EditLabel::Redo()
{}

