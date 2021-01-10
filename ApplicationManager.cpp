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
#include "Actions/Delete.h"
#include "Actions/Load.h"
#include "Actions/Save.h"
using namespace std;
#include "Actions/EditConnection.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	mode = DESIGN;

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
	pComp->Set_Comp_ID(CompCount);
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
			pAct = new Select(this, ComponentIsSelected, r_GfxInfoUsed, mode);
			break;

		case SIM_MODE:
			mode = SIMULATION;
			pAct = new SwitchMode(this, SIMULATION);
			break;

		case DSN_MODE:
			mode = DESIGN;
			pAct = new SwitchMode(this, DESIGN);
			break;

		case ADD_Label:
			pAct = new AddLabel(this, ComponentIsSelected);
			break;

		case EDIT_Label:
			pAct = new EditLabel(this, ComponentIsSelected);
			break;

		case EDIT_Connection:
			pAct = new EditConnection(this, ComponentIsSelected);
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
			pAct = new Delete(this, ComponentIsSelected);
			break;
		
		case SAVE:
			pAct = new Save(this);
			break;

		case LOAD:
			pAct = new Load(this);
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
	for (int i = 0; i < CompCount; i++)
	{
		if(mode == DESIGN)
			CompList[i]->Draw(OutputInterface);
		else
		{
			CompList[i]->Operate();
			CompList[i]->Draw(OutputInterface);
			//to update the drawing area after calling the operate function of each gate
			//because some of the components inside the compList won't catch 
			//the change in Pins status instantaneously
			Refresh();
		}
	}

}

void ApplicationManager::Refresh()
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Operate();
		CompList[i]->Draw(OutputInterface);
	}
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
		if (CompList[i] != NULL && dynamic_cast<Switch*>(SwitchSelected))
		{
			if (CompList[i]->InArea(x, y))
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
	// it is used when selecting a new component to unselect the previous one
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

void ApplicationManager::UnselectComponent()
{
	// this functions unselects ALL selected components
	if(ComponentIsSelected)
		ComponentIsSelected->setIsSelected(false);

	ComponentIsSelected = NULL;
}

void ApplicationManager::Remove(Component*& comp)
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
	}
}


void ApplicationManager::Remove_Connections(OutputPin* SrcPin, InputPin* DesPin)
{
	
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] && dynamic_cast<Connection*>(CompList[i]))
		{

			if (SrcPin == ((Connection*)CompList[i])->getSourcePin() || DesPin == ((Connection*)CompList[i])->getDestPin())
			{
				delete CompList[i];
				CompList[i] = NULL;

				for (int j = i; j < CompCount; j++)
				{
					// shift every element to the left
					CompList[j] = CompList[j + 1];
				}

				//Reducing i-- because I want to check also the shifted components
				//if I didn't reduce i-- that could cause that a connection
				//not getting deleted, because in the shifting process
				//we shift every element to the left, and the shifted the first element
				//could be a connection, and when the loop continues it will skip 
				//the first shifted element in the array
				i--;
				CompCount--;
			}

		}
	}
}

void ApplicationManager::save(ofstream&outputFile)
{
	outputFile << CompCount<<endl;
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Switch*>(CompList[i]))
		{
			CompList[i]->SaveComponent(outputFile);
		}
	}
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Gate*>(CompList[i]))
		{
			CompList[i]->SaveComponent(outputFile);
		}
	}
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<LED*>(CompList[i]))
		{
			CompList[i]->SaveComponent(outputFile);
		}
	}
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]))
		{
			outputFile << "Connections" << endl;
			
			CompList[i]->SaveComponent(outputFile);
		}
	}
	
}

void ApplicationManager::load(ifstream& inputFiles)
{
	int counttt;
	inputFiles >> counttt;
	int nnn;
	GraphicsInfo GInfo_SaveOrLoad;
	int Cx, Cy;	//Center point of the gate
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	
	
	for (int i=0;i<counttt;i++)
	{
		inputFiles >> nnn;
		if (nnn == 1)
		{
			inputFiles >> Cx >> Cy;
			GInfo_SaveOrLoad.x1 = Cx - Len / 2;
			GInfo_SaveOrLoad.x2 = Cx + Len / 2;
			GInfo_SaveOrLoad.y1 = Cy - Wdth / 2;
			GInfo_SaveOrLoad.y2 = Cy + Wdth / 2;
			AND2* pA = new AND2(GInfo_SaveOrLoad, AND2_FANOUT);
			AddComponent(pA);
			pA->LoadComponent();
		}
		else if (nnn=2)
		{
			
			inputFiles >> Cx >> Cy;
			GInfo_SaveOrLoad.x1 = Cx - Len / 2;
			GInfo_SaveOrLoad.x2 = Cx + Len / 2;
			GInfo_SaveOrLoad.y1 = Cy - Wdth / 2;
			GInfo_SaveOrLoad.y2 = Cy + Wdth / 2;
			LED* pA = new LED(GInfo_SaveOrLoad, AND2_FANOUT);
			AddComponent(pA);
		}


	}
	inputFiles.close();
}
