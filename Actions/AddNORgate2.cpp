#include "AddNORgate2.h"
#include "..\ApplicationManager.h"

AddNORgate2::AddNORgate2(ApplicationManager* pApp, bool* r_cut_check) :Action(pApp)
{
	cut_check = r_cut_check;
	Cx = 0; Cy = 0; x1 = 0; x2 = 0; y1 = 0, y2 = 0;
}

AddNORgate2::~AddNORgate2(void)
{
}

void AddNORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input NOR Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddNORgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//Calculate the rectangle Corners
	int Len = UI.NOR2_Width;
	int Wdth = UI.NOR2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the NOR2 gate
	GraphicsInfo check;

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (GInfo.y1 > UI.ToolBarHeight && GInfo.y2 < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 6)
	{
		NOR2* pA = new NOR2(GInfo, AND2_FANOUT);
		pManager->AddComponent(pA);

		if (cut_check)
			*cut_check = true;
	}
	else
		pOut->PrintMsg("Cannot add on bars and on top of components, Please click on a empty spot in the Drawing Area");

}

void AddNORgate2::Undo()
{}

void AddNORgate2::Redo()
{}

