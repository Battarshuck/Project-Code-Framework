#include "AddLabel.h"
#include "..\ApplicationManager.h"

AddLabel::AddLabel(ApplicationManager* pApp) :Action(pApp)
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

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	component = pManager->getComponent(Cx, Cy, m_GfxInfo);

	//Clear Status Bar
	pOut->ClearStatusBar();

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
}

void AddLabel::Undo()
{}

void AddLabel::Redo()
{}

