#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
	source = NULL;
	destination = NULL;
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

	//checking if the source component is in the drawing area
	//checking if the source component is a connection
	//both these cases must stop the excution
	if (source && !dynamic_cast<Connection*>(source))
	{
	
		Sx1 = source->getLocation().x1;
		Sy1 = source->getLocation().y1;
		Sx2 = source->getLocation().x2;
		Sy2 = source->getLocation().y2;
		// checking if the is gate or a switch or a LED
		if (dynamic_cast<Gate*>(source)) 
		{
			pSrcPin = ((Gate*)source)->getOutputPin();
			source_OutputConnections = ((Gate*)source)->getOutputConnections();
		}
		else if (dynamic_cast<Switch*>(source))
		{
			pSrcPin = ((Switch*)source)->getOutputPins();
			source_OutputConnections = 1;
		}
		else if (dynamic_cast<LED*>(source))
		{
			// a LED cannot be a source component to draw a connection
			pOut->PrintMsg("Source pin component cannot be a LED");
			source = NULL;
			return;
		}
		

		pOut->ClearStatusBar();

		pOut->PrintMsg("Click on destination pin");

		pIn->GetPointClicked(Px2, Py2);

		//getting the destination component details
		destination = pManager->getComponent(Px2, Py2, m_GfxInfo);

		//checking if the destination component is in the drawing area
		//checking if the destination component is a connection
		//both these cases must stop the excution
		if (destination && !dynamic_cast<Connection*>(destination))
		{
			Dx1 = destination->getLocation().x1;
			Dy1 = destination->getLocation().y1;
			Dx2 = destination->getLocation().x2;
			Dy2 = destination->getLocation().y2;
			m_Inputs = ((Gate*)destination)->numInputs();

			if (dynamic_cast<Gate*>(destination))
			{
				if (m_Inputs > 1 )
				{
					pOut->PrintMsg("Enter the pin number");
					InputPinNumber = (int)stoi(pIn->GetSrting(pOut));
					// overloaded getInputPins to return the Pin in the array 
					pDstPin = ((Gate*)destination)->getInputPins(InputPinNumber);
				}
				else
				{
					pDstPin = ((Gate*)destination)->getInputPins();
				}
				
			}
			else if(dynamic_cast<LED*>(destination))
			{
				pDstPin = ((LED*)destination)->getInputPins();
				m_Inputs = 1;
			}
			else if (dynamic_cast<Switch*>(destination))
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
			source = NULL;
			destination = NULL;
			return;
		}

	}
	else
	{
		pOut->ClearStatusBar();
		pOut->PrintMsg("ERROR: Please click on a component");
		source = NULL;
		destination = NULL;
		return;
	}


	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddConnection::Execute()
{
	//If the source and destination component exist
	//and source and destination are NOT the same component
	//then run the Execute function
	Output* pOut = pManager->GetOutput();
	bool FanOut_check; // to check if the source component reached the "FanOut" or Not 
	ReadActionParameters();
	if (source && destination && source != destination) 
	{
		

		//Calculate the rectangle Corners
		//All components have approximately same dimesions as AND2
		int Len = UI.AND2_Width;
		int Wdth = UI.AND2_Height;

		GraphicsInfo GInfo; //Gfx info to be used to draw the connection
		GInfo.x1 = Sx2-1;
		GInfo.y1 = Sy1 + Wdth / 2;
		GInfo.x2 = Dx1 + 2;




		//-------------------------------Computing Destination Pin Location------------------------------------------
		// All the Wdth*(constant) are done by Trial  and Error
		if (m_Inputs == 1) 
		{
			// if the destination component has 1 input 
			GInfo.y2 = Dy1 + Wdth / 2;
		}
		else if (m_Inputs == 2)
		{
			// if the destination component has 2 input 
			if (InputPinNumber == 1) 
			{
				GInfo.y2 = Dy1 + Wdth * 0.2555;
			}
			else if (InputPinNumber == 2)
			{
				GInfo.y2 = Dy1 + Wdth * 0.744;
			}

		}
        else if (m_Inputs == 3)
		{
			// if the destination component has 3 input 
			if (InputPinNumber == 1) 
			{
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
		//-------------------------------------------------------------------------





		if (m_Inputs > 1 &&(InputPinNumber == 1 || InputPinNumber == 2 || InputPinNumber == 3))
		{
			// if the component has more than one input pin
			// then the input pin index in the array is "InputPinNumber-1"
			Connection* pA = new Connection(GInfo, pSrcPin, &pDstPin[InputPinNumber-1]);
			FanOut_check = pSrcPin->ConnectTo(pA);

			if (FanOut_check)
			{
				pManager->AddComponent(pA);
			}
			else
			{
				pOut->PrintMsg("ERROR: Source component reached its Fan Out");
				delete pA; 
			}
		}
		else if (m_Inputs == 1)
		{
			// if the component has only one input pin
			// then the input pin index in the array is "0"
			Connection* pA = new Connection(GInfo, pSrcPin, &pDstPin[0]);
			FanOut_check = pSrcPin->ConnectTo(pA);

			if (FanOut_check)
			{
				pManager->AddComponent(pA);
			}
			else
			{
				pOut->PrintMsg("ERROR: Source component reached its Fan Out");
				delete pA;
			}
		}
		else 
		{
			// if the user entered a invalid input pin number
			pOut->PrintMsg("ERROR: Invalid Input");
		}

	}
}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

