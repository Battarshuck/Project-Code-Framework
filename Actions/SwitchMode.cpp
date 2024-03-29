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
		pOut->CreateDesignToolBar();
		pManager->TurnOffComponents();
	}
	else
	{
		pOut->PrintMsg("Switching to Simulation mode");
		pOut->CreateSimulationToolBar();
		pManager->UnselectComponent();
	}

}

void SwitchMode::Undo()
{}

void SwitchMode::Redo()
{}

