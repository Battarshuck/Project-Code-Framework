#include "AddANDgate2.h"
#include "..\ApplicationManager.h"

AddANDgate2::AddANDgate2(ApplicationManager *pApp):Action(pApp)
{
}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
	
}

void AddANDgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	
		//Calculate the rectangle Corners
		int Len = UI.AND2_Width;
		int Wdth = UI.AND2_Height;

		GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate
		GraphicsInfo check; //to check wether there is already a component in the spot or not

		GInfo.x1 = Cx - Len / 2;
		GInfo.x2 = Cx + Len / 2;
		GInfo.y1 = Cy - Wdth / 2;
		GInfo.y2 = Cy + Wdth / 2;

	if (GInfo.y1 > UI.ToolBarHeight && GInfo.y2 < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 6 && !pManager->getComponent(Cx,Cy, check))
	{
		AND2* pA = new AND2(GInfo, AND2_FANOUT);
		
		pManager->AddComponent(pA);
	}
	else
		pOut->PrintMsg("Cannot add on bars and on top of components, Please click on a empty spot in the Drawing Area");

}

void AddANDgate2::Undo()
{
}

void AddANDgate2::Redo()
{
}

