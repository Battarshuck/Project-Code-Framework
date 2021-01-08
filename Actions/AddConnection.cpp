#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
	source = NULL;
	destination = NULL;
	InputPinNumber = 0;
}

AddConnection::AddConnection(ApplicationManager* pApp, Component* source, Component* destination, int InputPinNumber) :Action(pApp)
{
	this->source = source;
	this->destination = destination;
	this->InputPinNumber = InputPinNumber;
}

AddConnection::~AddConnection(void)
{
}

void AddConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//getting the source component details
	if (!source)
	{
		pOut->PrintMsg("Click on source pin");
		pIn->GetPointClicked(Px1, Py1);
		source = pManager->getComponent(Px1, Py1, m_GfxInfo);
	}

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
			pSrcPin = ((Switch*)source)->getOutputPin();
			source_OutputConnections = 1;
		}
		else if (dynamic_cast<LED*>(source))
		{
			// a LED cannot be a source component to draw a connection
			pOut->PrintMsg("Source pin component cannot be a LED");
			source = NULL;
			return;
		}
		

		//getting the destination component details
		if (!destination) 
		{
			pOut->ClearStatusBar();
			pOut->PrintMsg("Click on destination pin");
			pIn->GetPointClicked(Px2, Py2);
			destination = pManager->getComponent(Px2, Py2, m_GfxInfo);
		}

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
					if (InputPinNumber == 0)
					{
						pOut->PrintMsg("Enter the pin number");
						InputPinNumber = stoi(pIn->GetSrting(pOut));
						 
					}

					// overloaded getInputPins to return the exact Pin in the Pins array
					if (InputPinNumber == 1 || InputPinNumber == 2 || InputPinNumber == 3)
					{
						pDstPin = ((Gate*)destination)->getInputPins(InputPinNumber-1);
					}
					else 
					{
						pOut->PrintMsg("ERROR: Invalid Input");
						destination = NULL;
					}
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

}

void AddConnection::Execute()
{
	
	Output* pOut = pManager->GetOutput();
	 //Gfx info to be used to draw the connection
	bool FanOut_check;// to check if the source component reached the "FanOut" or Not 
	bool IputPin_check; // to check if the input pin is already in a connection or not
	ReadActionParameters();

	//If the source and destination component do exist 
	//and source and destination are NOT the same component
	//then run the Execute function
	if (source && destination && source != destination) 
	{
		ComputeCoordinations();

		if (m_Inputs > 1)
		{

			Connection* pA = new Connection(GInfo, pSrcPin, pDstPin);

			FanOut_check = pSrcPin->ConnectTo(pA);
			IputPin_check = pDstPin->ConnectTo(pA);


			if (FanOut_check && IputPin_check)
			{
				pManager->AddComponent(pA);
			}
			else if (!FanOut_check)
			{
				pOut->PrintMsg("ERROR: Source component reached its Fan Out");
				delete pA;
			}
			else if (!IputPin_check)
			{
				pOut->PrintMsg("ERROR: Destination Pin is already in a connection");
				delete pA;
			}
		}
		else if (m_Inputs == 1)
		{

			Connection* pA = new Connection(GInfo, pSrcPin, pDstPin);

			FanOut_check = pSrcPin->ConnectTo(pA);
			IputPin_check = pDstPin->ConnectTo(pA);

			if (FanOut_check && IputPin_check)
			{
				pManager->AddComponent(pA);

			}
			else if(!FanOut_check)
			{
				pOut->PrintMsg("ERROR: Source component reached its Fan Out");
				delete pA;
			}
			else if (!IputPin_check)
			{
				pOut->PrintMsg("ERROR: Destination Pin is already in a connection");
				delete pA;
			}
		}

	}
}

void AddConnection::ComputeCoordinations()
{

	//Calculate the rectangle Corners
	//All components have approximately same dimesions as AND2
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	//X & Y of the source pin
	GInfo.x1 = Sx2 - 1;
	GInfo.y1 = Sy1 + Wdth / 2;
	//X component of the destination pin
	GInfo.x2 = Dx1 + 1;




	//-------------------------------Computing Destination Pin Location------------------------------------------
	// All the constants in Wdth*(constant) are done by Trial and Error
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

}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

