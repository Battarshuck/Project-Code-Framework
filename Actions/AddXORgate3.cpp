#include "AddXORgate3.h"
#include "..\ApplicationManager.h"

AddXORgate3::AddXORgate3(ApplicationManager* pApp, bool* r_cut_check) :Action(pApp)
{
	cut_check = r_cut_check;
	Cx = 0; Cy = 0; x1 = 0; x2 = 0; y1 = 0, y2 = 0;
}

AddXORgate3::~AddXORgate3(void)
{
}

void AddXORgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input XOR Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddXORgate3::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//Calculate the rectangle Corners
	int Len = UI.OR2_Width;
	int Wdth = UI.OR2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the XOR3 gate
	GraphicsInfo check;

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (GInfo.y1 > UI.ToolBarHeight && GInfo.y2 < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 6 && !pManager->getComponent(Cx, Cy, check))
	{
		XOR3* pA = new XOR3(GInfo, AND2_FANOUT);
		pManager->AddComponent(pA);

		if (cut_check)
			*cut_check = true;
	}
	else
		pOut->PrintMsg("Cannot add on bars and on top of components, Please click on a empty spot in the Drawing Area");


}

void AddXORgate3::Undo()
{}

void AddXORgate3::Redo()
{}

