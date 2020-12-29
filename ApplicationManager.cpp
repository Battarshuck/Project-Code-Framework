#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddINVgate.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddBUFFgate.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddLED.h"
#include "Actions\AddORgate2.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
	//mostafa
	UpdateInterface();
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
			
			break;

		case ADD_XNOR_GATE_2://amr
			
			break;

		case ADD_AND_GATE_3: //yasser
			pAct = new AddANDgate3(this);
			break;

		case ADD_NOR_GATE_3://amr
			
			break;

		case ADD_XOR_GATE_3://mostafa
			pAct = new AddXORgate3(this);
			break;

		case ADD_Switch://amr
			
			break;

		case ADD_LED: //yasser
			pAct = new AddLED(this);
			break;

		case ADD_CONNECTION:
			//TODO: Create AddConection Action here
			break;

	//############################################################

		case SELECT:
			
			break;

		case STATUS_BAR:
			
			break;

		case DSN_TOOL:
			
			break;

		case SIM_MODE:
			
			
			break;

		case DSN_MODE:
			
			
			break;

		case ADD_Label:
			
			break;

		case EDIT_Label:
			
			break;

		case Create_TruthTable:
			
			break;

		case Change_Switch:
			
			break;

		case DEL:
			
			break;

		case MOVE:
			
			break;

		case SAVE:
			
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