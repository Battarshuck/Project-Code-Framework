#include"Paste.h"
#include "..\ApplicationManager.h"
#include<iostream>

Paste::Paste(ApplicationManager* pApp, Component*& CompCopied_Cut, int& CopyOrCut) :Action(pApp), DeleteComp(CompCopied_Cut)
{
	copyorcut = CopyOrCut;
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
			
			pManager->AddComponent(PasteComp);
			
			if (copyorcut == 2)
			{
				pManager->Delete(DeleteComp);
				
				copyorcut = 0;
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
