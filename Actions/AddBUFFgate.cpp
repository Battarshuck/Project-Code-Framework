#include "AddBUFFgate.h"
#include "..\ApplicationManager.h"

AddBUFFgate::AddBUFFgate(ApplicationManager* pApp) :Action(pApp)
{
}

AddBUFFgate::~AddBUFFgate(void)
{
}

void AddBUFFgate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("1-Input BUFF Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddBUFFgate::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//Calculate the rectangle Corners
	int Len = UI.NOT_Width;
	int Wdth = UI.NOT_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the BUFF gate
	GraphicsInfo check;

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	if (GInfo.y1 > UI.ToolBarHeight && GInfo.y2 < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 6 && !pManager->getComponent(Cx, Cy, check))
	{
		BUFF* pA = new BUFF(GInfo, AND2_FANOUT);
		pManager->AddComponent(pA);
	}
	else
		pOut->PrintMsg("Cannot add on bars and on top of components, Please click on a empty spot in the Drawing Area");

}

void AddBUFFgate::Undo()
{}

void AddBUFFgate::Redo()
{}