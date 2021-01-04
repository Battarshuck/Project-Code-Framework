#include"Paste.h"
#include "..\ApplicationManager.h"

Paste::Paste(ApplicationManager* pApp, Component* CompCopied) :Action(pApp)
{

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
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	if (GInfo.y1 > UI.ToolBarHeight && GInfo.y2 < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 6)
	{
		//AND2* pA = new AND2(GInfo, AND2_FANOUT);
		//pManager->AddComponent(pA);
	}
	else
		pOut->PrintMsg("Cannot add here, Please click on Drawing Area");

}

void Paste::Undo()
{}

void Paste::Redo()
{}
