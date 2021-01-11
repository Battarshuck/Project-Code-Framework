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
#include <fstream>
using namespace std;
#include "Actions/EditConnection.h"
#include "Actions/Exit.h"
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
	if(!dynamic_cast<Connection*>(pComp))
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
			pAct = new Exit(this);
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
		if (mode == DESIGN) 
		{
			CompList[i]->Draw(OutputInterface);
		}
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

////////////////////////////////////////////////////////////////////
void ApplicationManager::Refresh()
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Operate();
		CompList[i]->Draw(OutputInterface);
	}
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::TurnOffComponents()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL)
		{
			if (dynamic_cast<Switch*>(CompList[i]))
			{
				((Switch*)CompList[i])->Setswitch(LOW);
			}
			else if (dynamic_cast<LED*>(CompList[i]))
			{
				((LED*)CompList[i])->setInputPinStatus(1, LOW);
			}
		}
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
	//Delete Connections first
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]))
		{
			delete CompList[i];
			CompList[i] = NULL;
		}
	}
	//Delete the Rest of the Components
	for (int i = 0; i < CompCount; i++)
	{
		if(CompList[i])
			delete CompList[i];
	}
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

Component* ApplicationManager:: getComponentBy_ID(int id)
{
	for (int i = 0; i < CompCount; i++)
	{
		if(CompList[i]->Get_Comp_Id()==id)
			return CompList[i];
	}
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

bool ApplicationManager::IsCompListEmpty()
{
	//check if the component list is empty or not
	//it returns true if it's empty
	//this function is used in Exit class
	if (CompCount == 0)
		return true;
	else
		return false;

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
	int CountComp_no_Connections=0;
	//count number of Components that are not Connections
	for (int i = 0; i < CompCount; i++)
	{
		if (!dynamic_cast<Connection*>(CompList[i]))
			CountComp_no_Connections++;
	}
	outputFile << CountComp_no_Connections <<endl;
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
	outputFile << "Connections" << endl;
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]))
		{	
			CompList[i]->SaveComponent(outputFile);
		}
	}
	outputFile << "-1" << endl;
}

void ApplicationManager::load(ifstream& inputFiles)
{
	string Component_type;
	int count_Comp_inFile;
	inputFiles >> count_Comp_inFile;
	int Comp_type;
	GraphicsInfo GInfo_SaveOrLoad_Dummy;
	GInfo_SaveOrLoad_Dummy.x1 = 0;
	GInfo_SaveOrLoad_Dummy.x2 = 0;
	GInfo_SaveOrLoad_Dummy.y1 = 0;
	GInfo_SaveOrLoad_Dummy.y2 = 0;
	//load Each component (Gates, Led and Switches) by calling its Load  function
	for (int i = 0;i < count_Comp_inFile;i++)
	{
		inputFiles >> Comp_type;//take the Component Type Number  
		if (Comp_type == _BUFF)//identifying the Component Type using the Type Number(from file) with the enum ComponentType 
		{
			BUFF* pCompLoad = new BUFF(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _INV)
		{
			INV* pCompLoad = new INV(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _AND2)
		{
			AND2* pCompLoad = new AND2(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _OR2)
		{
			OR2* pCompLoad = new OR2(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _NAND2)
		{
			NAND2* pCompLoad = new NAND2(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _NOR2)
		{
			NOR2* pCompLoad = new NOR2(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _XOR2)
		{
			XOR2* pCompLoad = new XOR2(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _XNOR2)
		{
			XNOR2* pCompLoad = new XNOR2(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _AND3)
		{
			AND3* pCompLoad = new AND3(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _NOR3)
		{
			NOR3* pCompLoad = new NOR3(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _XOR3)
		{
			XOR3* pCompLoad = new XOR3(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _Switch)
		{
			Switch* pCompLoad = new Switch(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
		else if (Comp_type == _LED)
		{
			LED* pCompLoad = new LED(GInfo_SaveOrLoad_Dummy, AND2_FANOUT);
			AddComponent(pCompLoad);
			pCompLoad->LoadComponent(inputFiles);
		}
	}
	//load Connections
	string DUMMMY;//just for the word "Connections" in the file
	inputFiles >> DUMMMY;
	//load each Connection till the file reach -1
	while (!inputFiles.eof())
	{
		Connection* pCompLoad = new Connection(GInfo_SaveOrLoad_Dummy, NULL, NULL);
		int* Source_Dest_ids_Pin = pCompLoad->LoadComponent(inputFiles);
		if (Source_Dest_ids_Pin == NULL)
		{
			break;
		}
		else
		{
			int Source_Comp_=Source_Dest_ids_Pin[0];
			int Dest_Comp_ = Source_Dest_ids_Pin[1];
			int Pin_Num = Source_Dest_ids_Pin[2];
			Component* Comp_Source;
			Component* Comp_Destination;
			Comp_Source = getComponentBy_ID(Source_Comp_);
			Comp_Destination = getComponentBy_ID(Dest_Comp_);
			delete pCompLoad;
			pCompLoad = NULL;
			Action* p_action = new AddConnection(this, Comp_Source, Comp_Destination, Pin_Num);
			p_action->Execute();
		}
	}
		
}
