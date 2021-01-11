#include"Paste.h"
#include "AddANDgate2.h"
#include "AddINVgate.h"
#include "AddNORgate2.h"
#include "AddXORgate3.h"
#include "AddConnection.h"
#include "AddBUFFgate.h"
#include "AddNANDgate2.h"
#include "AddANDgate3.h"
#include "AddLED.h"
#include "AddSwitch.h"
#include "AddORgate2.h"
#include "AddXORgate2.h"
#include "AddXNORgate2.h"
#include "AddNORgate3.h"
#include"Delete.h"
#include "..\ApplicationManager.h"

Paste::Paste(ApplicationManager* pApp, Component*& SelectedComp, Component*& CompCopied_Cut, int*& CopyOrCut) :Action(pApp), DeleteComp(CompCopied_Cut),copyorcut( CopyOrCut), SelectedComp(SelectedComp)
{
	//copyorcut =  CopyOrCut;
	PasteComp = CompCopied_Cut;
	cut_check = false;
}

Paste::~Paste(void)
{
}

void Paste::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	//pOut->PrintMsg("Paste a Component: Click on the Drwaing Area");

	//Wait for User Input
	//pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void Paste::Execute()
{
	Output* pOut = pManager->GetOutput();

	if (PasteComp)
	{
		//Get Center point of the Gate
		ReadActionParameters();


			//identify the Component type of Copied/Cut Component 
			if (dynamic_cast<AND3*>(PasteComp))
			{
				AddANDgate3* ptrCOMP = new AddANDgate3(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<NOR3*>(PasteComp))
			{
				AddNORgate3* ptrCOMP = new AddNORgate3(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<XOR3*>(PasteComp))
			{
				AddXORgate3* ptrCOMP = new AddXORgate3(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<INV*>(PasteComp))
			{
				AddINVgate* ptrCOMP = new AddINVgate(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<BUFF*>(PasteComp))
			{
				AddBUFFgate* ptrCOMP = new AddBUFFgate(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<LED*>(PasteComp))
			{
				AddLED* ptrCOMP = new AddLED(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<Switch*>(PasteComp))
			{
				AddSwitch* ptrCOMP = new AddSwitch(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<OR2*>(PasteComp))
			{
				AddORgate2* ptrCOMP = new AddORgate2(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<XOR2*>(PasteComp))
			{
				AddXORgate2* ptrCOMP = new AddXORgate2(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<XNOR2*>(PasteComp))
			{
				AddXNORgate2* ptrCOMP = new AddXNORgate2(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<NOR2*>(PasteComp))
			{
				AddNORgate2* ptrCOMP = new AddNORgate2(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<NAND2*>(PasteComp))
			{
				AddNANDgate2* ptrCOMP = new AddNANDgate2(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			else if (dynamic_cast<AND2*>(PasteComp))
			{
				AddANDgate2* ptrCOMP = new AddANDgate2(pManager, &cut_check);
				ptrCOMP->Execute();
				delete ptrCOMP;
			}
			//Delete the old Component (in case of Cut only)
			// and make the pointer ComponentIsSelected in AppManager points to NULL
			if (*copyorcut == 2 && cut_check)
			{
				Delete* Delete_function = new Delete(pManager, DeleteComp);
				Delete_function->Execute();
				delete Delete_function;

				SelectedComp = NULL;
				*copyorcut = 0;
			}
			//unselect old component ( in case of Copy only)
			else if (*copyorcut == 1)
			{
				PasteComp->setIsSelected(false);
				SelectedComp = NULL;
			}
		

	}
	else
		pOut->PrintMsg("ERROR: No component is cut or copied");
}

void Paste::Undo()
{}

void Paste::Redo()
{}
