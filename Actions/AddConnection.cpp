#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
	check = NULL;
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

	//getting the source component details
	source = pManager->getComponent(Px1, Py1, m_GfxInfo);

	if (source) 
	{
	
		Sx1 = source->getLocation().x1;
		Sy1 = source->getLocation().y1;
		Sx2 = source->getLocation().x2;
		Sy2 = source->getLocation().y2;
		// checking if the is gate or a switch or a LED
		if (check = dynamic_cast<Gate*>(source)) 
		{
			pSrcPin = ((Gate*)source)->getOutputPin();
			source_OutputConnections = ((Gate*)source)->getOutputConnections();
		}
		else if (check = dynamic_cast<Switch*>(source))
		{
			pSrcPin = ((Switch*)source)->getOutputPins();
			source_OutputConnections = 1;
		}
		else if (check = dynamic_cast<LED*>(source))
		{
			// a LED cannot be a source component to draw a connection
			pOut->PrintMsg("Source pin component cannot be a LED");
			source = NULL;
			return;
		}

		/*if (!pSrcPin->ConnectTo())
		{
			source = NULL;
			pOut->PrintMsg("Source pin reached its maximum number of connections");
			return;
		}*/
		

		pOut->ClearStatusBar();

		pOut->PrintMsg("Click on destination pin");

		pIn->GetPointClicked(Px2, Py2);

		//getting the destination component details
		destination = pManager->getComponent(Px2, Py2, m_GfxInfo);

		if (destination) 
		{
			Dx1 = destination->getLocation().x1;
			Dy1 = destination->getLocation().y1;
			Dx2 = destination->getLocation().x2;
			Dy2 = destination->getLocation().y2;
			

			if (check = dynamic_cast<Gate*>(destination))
			{
				pDstPin = ((Gate*)destination)->getInputPins();
				m_Inputs = ((Gate*)destination)->numInputs();
			}
			else if(check = dynamic_cast<LED*>(destination))
			{
				pDstPin = ((LED*)destination)->getInputPins();
				m_Inputs = 1;
			}
			else if (check = dynamic_cast<Switch*>(destination))
			{
				// a switch cannot be a destination component to draw a connection
				pOut->PrintMsg("Destination pin component cannot be a Switch");
				destination = NULL;
				return;
			}

		}
		else 
		{
			pOut->ClearStatusBar();
			pOut->PrintMsg("ERROR: Please click on a component");
			return;
		}

		pOut->ClearStatusBar();
	}
	else
	{
		pOut->ClearStatusBar();
		pOut->PrintMsg("ERROR: Please click on a component");
		return;
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
	//If the source and destination component exist
	//then run the Execute function
	ReadActionParameters();
	if (source && destination) 
	{

		//Calculate the rectangle Corners
		int Len = UI.AND2_Width;
		int Wdth = UI.AND2_Height;

		GraphicsInfo GInfo; //Gfx info to be used to draw the connection
		GInfo.x1 = Sx2 - 2;
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
}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

