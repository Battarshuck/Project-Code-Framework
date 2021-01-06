#include "Select.h"
#include"ApplicationManager.h"
#include"Defs.H"
#include"Components/Component.h"
#include"..\Components\Switch.h"

//constructor
Select::Select(ApplicationManager* pApp, Component*& ComponentPassed, GraphicsInfo& r_GfxInfo, MODE r_mode) :Action(pApp), CompSelected(ComponentPassed)
{
	this->r_GInfo = r_GfxInfo;
	m_mode = r_mode;
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
	if(m_mode == DESIGN)
		pOut->PrintMsg("Click on the component you want to select");
	else
		pOut->PrintMsg("Click on a switch to change state");

	//Wait for User Input
	pIn->GetPointClicked(x, y);

	//Clear Status Bar
	pOut->ClearStatusBar();

	//check if the click is inside area of any componenet	
	CompSelected = pManager->getComponent(x, y, m_GfxInfo);

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
		if (m_mode == DESIGN)
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
				pManager->UnselectOtherComponents(CompSelected);
				CompSelected->setIsSelected(true);
			}
			
		}

		else if (m_mode == SIMULATION)
		{
			Component* Selected_switch = CompSelected;
			if (dynamic_cast<Switch*>(Selected_switch))
			{
				if ( ((Switch*)Selected_switch)->Getswitch() == LOW )
				{
					pOut->PrintMsg("Switch set to High");
					((Switch*)Selected_switch)->Setswitch(HIGH);
				}
				else
				{
					pOut->PrintMsg("Switch set to Low");
					((Switch*)Selected_switch)->Setswitch(LOW);
				}
			}
			else
			{
				pOut->PrintMsg("You can NOT select a component in simulation mode");
			}
		}
	}
}

//To undo this action (code depends on action type)
void Select::Undo()
{}

//To redo this action (code depends on action type)
void Select::Redo()
{}