#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
	CompList = pApp->getCompList(CompCount);
}

AddConnection::~AddConnection(void)
{
}

void AddConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click on source pin");

	//Wait for User Input
	pIn->GetPointClicked(Px1, Py1);

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL) 
		{
			if (CompList[i]->InArea(Px1, Py1)) 
			{
				source = CompList[i];
				pSrcPin = ((Gate*)CompList[i])->getOutputPin();
				Sx1 = CompList[i]->getLocation().x1;
				Sy1 = CompList[i]->getLocation().y1;
				Sx2 = CompList[i]->getLocation().x2;
				Sy2 = CompList[i]->getLocation().y2;
				source_OutputConnections = ((Gate*)CompList[i])->getOutputConnections();
				break;
			}
		}
	}

	pOut->ClearStatusBar();

	
	pOut->PrintMsg("Click on destination pin");

	pIn->GetPointClicked(Px2, Py2);

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] != NULL) {
			if (CompList[i]->InArea(Px2, Py2))
			{
				pDstPin = ((Gate*)CompList[i])->getInputPins();
				Dx1 = CompList[i]->getLocation().x1;
				Dy1 = CompList[i]->getLocation().y1;
				Dx2 = CompList[i]->getLocation().x2;
				Dy2 = CompList[i]->getLocation().y2;
				m_Inputs = ((Gate*)CompList[i])->numInputs();
				//source
				break;
			}
		}
	}

	pOut->ClearStatusBar();

	if (m_Inputs > 1) {
		pOut->PrintMsg("Enter the pin number");
		InputPinNumber = stoi(pIn->GetSrting(pOut));
	}
	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddConnection::Execute()
{
	
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to draw the connection
	GInfo.x1 = Sx2-2;
	GInfo.y1 = Sy1 + Wdth / 2;

	GInfo.x2 = Dx1 + 2;

	if (m_Inputs == 1) {
		GInfo.y2 = Dy1 + Wdth / 2;
	}

	if (m_Inputs == 2)
	{
		if (InputPinNumber == 1) {
			GInfo.y2 = Dy1 + Wdth * 0.2555;
		}
		else if (InputPinNumber == 2)
		{
			GInfo.y2 = Dy1 + Wdth * 0.744;
		}

	}

	if (m_Inputs == 3)
	{
		if (InputPinNumber == 1) {
			GInfo.y2 = Dy1 + Wdth * 0.256;
		}
		else if (InputPinNumber == 2)
		{
			GInfo.y2 = Dy1 + Wdth * 0.5;
		}
		else if (InputPinNumber == 3)
		{
			GInfo.y2 = Dy1 + Wdth * 0.75;
		}

	}


	Connection* pA = new Connection(GInfo, pSrcPin, &pDstPin[InputPinNumber]);
	pManager->AddComponent(pA);
}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

