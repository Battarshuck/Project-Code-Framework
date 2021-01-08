#include"Delete.h"
#include "..\ApplicationManager.h"
#include"..\Components\Gate.h"
#include"..\Components\Switch.h"
#include"..\Components\LED.h"

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
	int m_input;
	
	if (componentSelected)
	{
		
		//Deleting component connections
		if (dynamic_cast<Gate*>(componentSelected))
		{
			OutputPin* SrcPin = ((Gate*)componentSelected)->getOutputPin();
			pManager->Remove_Connections(SrcPin);

			m_input = ((Gate*)componentSelected)->numInputs();
			if (m_input == 1)
			{
				InputPin* DestPin = ((Gate*)componentSelected)->getInputPins();
				pManager->Remove_Connections(NULL, DestPin);
			}
			else if (m_input > 1)
			{
				InputPin* DestPins = ((Gate*)componentSelected)->getInputPins();
				for (int i = 0; i < m_input; i++)
				{
					pManager->Remove_Connections(NULL, &DestPins[i]);
				}
			}
		}
		else if (dynamic_cast<Switch*>(componentSelected))
		{
			OutputPin* SrcPin = ((Switch*)componentSelected)->getOutputPin();
			pManager->Remove_Connections(SrcPin);
		}
		else if (dynamic_cast<LED*>(componentSelected))
		{
			InputPin* DestPins = ((LED*)componentSelected)->getInputPins();
			pManager->Remove_Connections(NULL, DestPins);
		}


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

