#include"Paste.h"
#include "..\ApplicationManager.h"
#include"..\Components\AND3.h"
#include"..\Components\NOR3.h"
#include"..\Components\XOR3.h"
#include"..\Components\INV.h"
#include"..\Components\BUFF.h"
#include"..\Components\LED.h"
#include"..\Components\Switch.h"

Paste::Paste(ApplicationManager* pApp, Component*& CompCopied_Cut, int& CopyOrCut) :Action(pApp), DeleteComp(CompCopied_Cut),copyorcut(CopyOrCut)
{
	//copyorcut = CopyOrCut;
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

		GInfo.x1 = Cx - Len / 2;
		GInfo.x2 = Cx + Len / 2;
		GInfo.y1 = Cy - Wdth / 2;
		GInfo.y2 = Cy + Wdth / 2;

		if (GInfo.y1 > UI.ToolBarHeight && GInfo.y2 < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 6)
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
			
			//Delete the old Component (in case of Cut only)
			if (copyorcut == 2)
			{
				pManager->Delete(DeleteComp);
				copyorcut = 0;
			}
			//unselect old component ( in case of Copy only)
			else if (copyorcut == 1)
			{
				PasteComp->setIsSelected(false);
			}
		}
		else
			pOut->PrintMsg("Cannot add here, Please click on Drawing Area");

	}
	else
		pOut->PrintMsg("ERROR: No component is cut or copied");
}

void Paste::Undo()
{}

void Paste::Redo()
{}
