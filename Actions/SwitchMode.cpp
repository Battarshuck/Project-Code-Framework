#include "SwitchMode.h"
#include "..\ApplicationManager.h"

SwitchMode::SwitchMode(ApplicationManager* pApp, MODE r_mode) :Action(pApp)
{
	m_mode = r_mode;
}

SwitchMode::~SwitchMode(void)
{
}

void SwitchMode::ReadActionParameters()
{

}

void SwitchMode::Execute()
{
	Output* pOut = pManager->GetOutput();

	if (m_mode == DESIGN) 
	{
		pOut->PrintMsg("Switching to desining mode");
		UI.AppMode = DESIGN;
	}
	else
	{
		pOut->PrintMsg("Switching to Simulation mode");
		UI.AppMode = SIMULATION;
	}

}

void SwitchMode::Undo()
{}

void SwitchMode::Redo()
{}

