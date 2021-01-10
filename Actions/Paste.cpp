#include"Paste.h"
#include "..\ApplicationManager.h"
#include"..\Components\AND3.h"
#include"..\Components\NOR3.h"
#include"..\Components\XOR3.h"
#include"..\Components\INV.h"
#include"..\Components\BUFF.h"
#include"..\Components\LED.h"
#include"..\Components\Switch.h"
#include"..\Components\AND2.h"
#include"..\Components\OR2.h"
#include"..\Components\NAND2.h"
#include"..\Components\NOR2.h"
#include"..\Components\XOR2.h"
#include"..\Components\XNOR2.h"
#include"Delete.h"

Paste::Paste(ApplicationManager* pApp, Component*& SelectedComp, Component*& CompCopied_Cut, int*& CopyOrCut) :Action(pApp), DeleteComp(CompCopied_Cut),copyorcut( CopyOrCut), SelectedComp(SelectedComp)
{
	//copyorcut =  CopyOrCut;
	PasteComp = CompCopied_Cut;
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
	pOut->PrintMsg("Paste a Component: Click on the Drwaing Area");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

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

		//Calculate the rectangle Corners
		int Len = UI.AND2_Width;
		int Wdth = UI.AND2_Height;

		GraphicsInfo GInfo; //Gfx info to be used to construct the Copied or cut gate
		GraphicsInfo check;

		GInfo.x1 = Cx - Len / 2;
		GInfo.x2 = Cx + Len / 2;
		GInfo.y1 = Cy - Wdth / 2;
		GInfo.y2 = Cy + Wdth / 2;

		if (GInfo.y1 > UI.ToolBarHeight && GInfo.y2 < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 6 && !pManager->getComponent(Cx, Cy, check))
		{
			//identify the Component type of Copied/Cut Component 
			//Amr 7ot hena your gates
			if (dynamic_cast<AND3*>(PasteComp))
			{
				AND3* ptrCOMP = new AND3(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<NOR3*>(PasteComp))
			{
				NOR3* ptrCOMP = new NOR3(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<XOR3*>(PasteComp))
			{
				XOR3* ptrCOMP = new XOR3(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<INV*>(PasteComp))
			{
				INV* ptrCOMP = new INV(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<BUFF*>(PasteComp))
			{
				BUFF* ptrCOMP = new BUFF(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<LED*>(PasteComp))
			{
				LED* ptrCOMP = new LED(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<Switch*>(PasteComp))
			{
				Switch* ptrCOMP = new Switch(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<OR2*>(PasteComp))
			{
				OR2* ptrCOMP = new OR2(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<XOR2*>(PasteComp))
			{
				XOR2* ptrCOMP = new XOR2(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<XNOR2*>(PasteComp))
			{
				XNOR2* ptrCOMP = new XNOR2(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<NOR2*>(PasteComp))
			{
				NOR2* ptrCOMP = new NOR2(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<NAND2*>(PasteComp))
			{
				NAND2* ptrCOMP = new NAND2(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			else if (dynamic_cast<AND2*>(PasteComp))
			{
				AND2* ptrCOMP = new AND2(GInfo, AND2_FANOUT);
				pManager->AddComponent(ptrCOMP);
			}
			//Delete the old Component (in case of Cut only)
			// and make the pointer ComponentIsSelected in AppManager points to NULL
			if (*copyorcut == 2)
			{
				Delete* Delete_function = new Delete(pManager, DeleteComp);
				Delete_function->Execute();

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
			pOut->PrintMsg("Cannot Paste here, Please click on Drawing Area");

	}
	else
		pOut->PrintMsg("ERROR: No component is cut or copied");
}

void Paste::Undo()
{}

void Paste::Redo()
{}
