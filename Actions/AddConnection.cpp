#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager* pApp) :Action(pApp)
{
	source = NULL;
	destination = NULL;
	InputPinNumber = 0;
	Px1 = 0; Py1 = 0; Px2 = 0; Py2 = 0;
	Sx1 = 0; Sy1 = 0; Sx2 = 0; Sy2 = 0; Dx1 = 0; Dx2 = 0; Dy1 = 0; Dy2 = 0;
}

AddConnection::AddConnection(ApplicationManager* pApp, Component* source, Component* destination, int InputPinNumber) :Action(pApp)
{
	//this is a non-default constructor that is used with Edit Connection Class
	this->source = source;
	this->destination = destination;
	this->InputPinNumber = InputPinNumber;
	Px1 = 0; Py1 = 0; Px2 = 0; Py2 = 0;
	Sx1 = 0; Sy1 = 0; Sx2 = 0; Sy2 = 0; Dx1 = 0; Dx2 = 0; Dy1 = 0; Dy2 = 0;
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
		// checking if the is a LED
		if (!dynamic_cast<LED*>(source))
		{
			pSrcPin = source->getOutputPin();
		}
		else
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
			m_Inputs = destination->numInputs();

			if (dynamic_cast<Gate*>(destination))
			{
				if (m_Inputs > 1 )
				{
					if (InputPinNumber == 0)
					{
						pOut->PrintMsg("Enter the pin number");
						string User_input = pIn->GetSrting(pOut);

						if (is_digits(User_input))
						{
							InputPinNumber = stoi(User_input);
						}
						else
						{
							pOut->PrintMsg("ERROR: Invalid Input");
							destination = NULL;
							source = NULL;
							return;
						}
						
						 
					}

					// overloaded getInputPins to return the exact Pin in the Pins array
					if ((InputPinNumber == 1 || InputPinNumber == 2 || InputPinNumber == 3) && m_Inputs >= InputPinNumber)
					{
						pDstPin = destination->getInputPins(InputPinNumber-1);
					}
					else 
					{
						pOut->PrintMsg("ERROR: Invalid Input");
						destination = NULL;
						source = NULL;
					}

				}
				else
				{
					pDstPin = destination->getInputPins();
				}
				
			}
			else if(dynamic_cast<LED*>(destination))
			{
				pDstPin = destination->getInputPins();
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

bool AddConnection::is_digits(const string& str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}

void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

