#include "AddINVgate.h"
#include "..\ApplicationManager.h"

AddINVgate::AddINVgate(ApplicationManager* pApp, bool* r_cut_check) :Action(pApp)
{
	cut_check = r_cut_check;
	Cx = 0; Cy = 0; x1 = 0; x2 = 0; y1 = 0, y2 = 0;
}

AddINVgate::~AddINVgate(void)
{
}

void AddINVgate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Inverter Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddINVgate::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//Calculate the rectangle Corners
	int Len = UI.NOT_Width;
	int Wdth = UI.NOT_Height;

	GraphicsInfo GInfo; 
	GraphicsInfo check;

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (GInfo.y1 > UI.ToolBarHeight && GInfo.y2 < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 6 && !pManager->getComponent(Cx, Cy, check))
	{
		INV* pA = new INV(GInfo, AND2_FANOUT);
		pManager->AddComponent(pA);

		if (cut_check)
			*cut_check = true;
	}
	else
		pOut->PrintMsg("Cannot add on bars and on top of components, Please click on a empty spot in the Drawing Area");

}

void AddINVgate::Undo()
{}

void AddINVgate::Redo()
{}

