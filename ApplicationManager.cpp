#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddINVgate.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddConnection.h"
#include "Actions\AddBUFFgate.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddLED.h"
#include "Actions\AddSwitch.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddLabel.h"
#include "Actions\SwitchMode.h"
#include "Select.h"
#include "Actions/EditLabel.h"
#include "Actions/Copy.h"
#include "Actions/Paste.h"
#include "Actions/Cut.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
	//initializing ComponentIsSelected to NULL
	ComponentIsSelected = NULL;
	//initializing ComponenetIsCopied to NULL
	ComponenetIsCopied_Cut = NULL;

	CopyOrcut = 0;// 0 is the default value of this integer(no component is copied or cut), 
	//1 indicates a component is copied,
	//2 indicates that a component is cut
	
	CopyOrCut_ptr = &CopyOrcut;//Pointer to CopyOrcut
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_Buff: //yasser
			pAct = new AddBUFFgate(this);
			break;

		case ADD_INV: // mostafa
			pAct = new AddINVgate(this);
			break;

		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;

		case ADD_NAND_GATE_2: //yasser
			pAct = new AddNANDgate2(this);
			break;

		case ADD_OR_GATE_2: //yasser
			pAct = new AddORgate2(this);
			break;

		case ADD_NOR_GATE_2://mostafa
			pAct = new AddNORgate2(this);
			break;

		case ADD_XOR_GATE_2://amr
			pAct = new AddXORgate2(this);
			break;

		case ADD_XNOR_GATE_2://amr
			pAct = new AddXNORgate2(this);
			break;

		case ADD_AND_GATE_3: //yasser
			pAct = new AddANDgate3(this);
			break;

		case ADD_NOR_GATE_3://amr
			pAct = new AddNORgate3(this);
			break;

		case ADD_XOR_GATE_3://mostafa
			pAct = new AddXORgate3(this);
			break;

		case ADD_Switch://amr
			pAct = new AddSwitch(this);
			break;

		case ADD_LED: //yasser
			pAct = new AddLED(this);
			break;

		case ADD_CONNECTION: //mostafa
			pAct = new AddConnection(this);
			break;

	//############################################################

		case SELECT:
			pAct = new Select(this, ComponentIsSelected, r_GfxInfoUsed);
			break;

		case SIM_MODE:
			mode = SIMULATION;
			//pAct = new SwitchMode(this, SIMULATION);
			OutputInterface->CreateSimulationToolBar();
			break;

		case DSN_MODE:
			mode = DESIGN;
			//pAct = new SwitchMode(this, DESIGN);
			OutputInterface->CreateDesignToolBar();
			break;

		case ADD_Label:
			pAct = new AddLabel(this, ComponentIsSelected);
			break;

		case EDIT_Label:
			pAct = new EditLabel(this, ComponentIsSelected);
			break;

		case EDIT_Connection:
			//pAct = new EditConnection(this, ComponentIsSelected);
			break;

		case Change_Switch:
			
			break;

		case COPY:
			ComponenetIsCopied_Cut = NULL;
			pAct = new Copy(this, ComponentIsSelected, ComponenetIsCopied_Cut, CopyOrCut_ptr);
			break;

		case PASTE:
			pAct = new Paste(this, ComponentIsSelected, ComponenetIsCopied_Cut, CopyOrCut_ptr);
			break;

		case CUT:
			ComponenetIsCopied_Cut = NULL;
			pAct = new Cut(this, ComponentIsSelected, ComponenetIsCopied_Cut, CopyOrCut_ptr);
			break;

		case DEL:
			Delete(ComponentIsSelected);
			break;

		case SAVE:
			
			break;

		case LOAD:

			break;

		case EXIT:
			///TODO: create ExitAction here
			break;
	}

	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();
	for(int i=0; i<CompCount; i++)
		CompList[i]->Draw(OutputInterface);

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
}

Component* ApplicationManager::getComponent(int x, int y, GraphicsInfo& r_GfxInfo)
{
	Component* component = NULL;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
				if (CompList[i]->InArea(x, y))
				{
					component = CompList[i];
					r_GfxInfo = CompList[i]->getLocation();
					break;
				}
		}
	}

	return component;
}

Component* ApplicationManager::getSwitch(int x, int y, Component* SwitchSelected)
{
	Component* component = NULL;
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
			if (CompList[i]->InArea(x, y) && dynamic_cast<Switch*>(SwitchSelected))
			{
				component = CompList[i];
				break;
			}
		}
	}

	return component;
}

void ApplicationManager::UnselectOtherComponents(Component* newSelectedComp)
{
	// this functions unselects previously selected components
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
			if (newSelectedComp != CompList[i] && CompList[i]->getIsSelected())
			{
				CompList[i]->setIsSelected(false);
				break;
			}
		}
	}
}

void ApplicationManager::Delete(Component*& comp)
{
	if (comp)
	{

		int i;
		for (i = 0; i < CompCount; i++)
		{
			if (CompList[i] == comp)
				break;
		}

		delete comp;
		comp = NULL;

		// if the component is not the last one in the array
		// then shift every element to left
		// else just delete it and reduce CompCount by 1
		// CompCount is sent by reference so we can modify its value
		// inside the application manager
		if (i < CompCount)
		{

			for (int j = i; j < CompCount; j++)
			{
				// shift every element to the left
				CompList[j] = CompList[j + 1];
			}

			CompCount--;

		}

		//deleting component's connections
	}
	else
	{
		OutputInterface->PrintMsg("Please select a component before Deleting");
	}

}
