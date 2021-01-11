#include "EditConnection.h"
#include "..\ApplicationManager.h"
#include "AddConnection.h"


EditConnection::EditConnection(ApplicationManager* pApp, Component*& SelectedComp) :Action(pApp), m_connection(SelectedComp)
{
	
}

EditConnection::~EditConnection(void)
{
	
}

void EditConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (m_connection) 
	{
		if (dynamic_cast<Connection*>(m_connection))
		{
			pOut->PrintMsg("Enter 1 to change Source Pin, 2 to change Destination Pin");
			choice = pIn->GetSrting(pOut);

			if (choice == "1" || choice == "2")
			{
				int x, y;
				pOut->PrintMsg("Click on the new Component's Pin");
				pIn->GetPointClicked(x, y);
				new_component = pManager->getComponent(x, y, m_GfxInfo);
			}
			else
			{
				new_component = NULL;
				pOut->PrintMsg("ERROR: Invalid Input");
			}
		}
		else
		{
			pOut->PrintMsg("ERROR: you can only use this Action for a Connection");
		}
	}
	else
	{
		pOut->PrintMsg("Please Select a Connection first");
		new_component = NULL;
	}
	
}

void EditConnection::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	AddConnection* edit_connection = NULL;

	if (new_component)
	{
		//isConnected(); function checks if the pin is in connection or not
		//if it's in a connection the function returns true, otherwise return false
		//if it's not connected, it will create a connection normally
		if (choice == "1")
		{
			// getting the connection's default destinationPin's component which will stay the same
			Component* destination = ((Connection*)m_connection)->getDestPin()->getComponent();

			if (destination != new_component)
			{
				//LED component cannot be destination component
				if (!dynamic_cast<LED*>(new_component))
				{
					if (dynamic_cast<Gate*>(new_component))
					{
						if (!new_component->getOutputPin()->isConnected())
						{
							//if the pin and the connection passes every validation
							//the functiom will delete the old connection
							//and will create a new connectin
							//which is the edited one
							pManager->Remove(m_connection);
							//using a non-default constructor
							edit_connection = new AddConnection(pManager, new_component, destination);
							edit_connection->Execute();
						}
						else
						{
							pOut->PrintMsg("ERROR: New Source Pin is already in a Connection");
						}
					}
					else
					{
						if (!new_component->getOutputPin()->isConnected())
						{
							pManager->Remove(m_connection);
							edit_connection = new AddConnection(pManager, new_component, destination);
							edit_connection->Execute();
						}
						else
						{
							pOut->PrintMsg("ERROR: New Source Pin is already in a Connection");
						}
					}

				}
				else
				{
					pOut->PrintMsg("ERROR: New Source Pin Component cannot be a LED");
				}

			}
			else
			{
				pOut->PrintMsg("ERROR: Identical Components");
			}

		}
		else
		{
			//if the user wants to change the destination Pin
			int InputPinNumber = 0;
			// getting the connection's default sourcePin's component which will stay the same
			Component* source = ((Connection*)m_connection)->getSourcePin()->getComponent();
			int m_Inputs = new_component->numInputs();
			if (source != new_component)
			{
				if (m_Inputs > 1)
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
						source = NULL;
						return;
					}

				}
				else
				{
					InputPinNumber = 1;
				}
			


				if ((InputPinNumber == 1 || InputPinNumber == 2 || InputPinNumber == 3) && m_Inputs >= InputPinNumber)
				{
					
					//switch component cannot be destination component
					if (!dynamic_cast<Switch*>(new_component))
					{
						if (dynamic_cast<Gate*>(new_component))
						{
							if (!new_component->getInputPins(InputPinNumber - 1)->isConnected())
							{
								pManager->Remove(m_connection);
								//in addition here, send the Pin number
								//because in the AddConnection class, the function will first check
								//if the source and the destination are actual components or NULL
								//if NULL it will stop the class, and that will not asking the user for
								//the pin number, for this resaon I send the inputPin number to the class
								edit_connection = new AddConnection(pManager, source, new_component, InputPinNumber);
								edit_connection->Execute();
							}
							else
							{
								pOut->PrintMsg("ERROR: New Destination Pin is already in a Connection");
							}
						}
						else
						{

							if (!new_component->getInputPins()->isConnected())
							{
								pManager->Remove(m_connection);
								edit_connection = new AddConnection(pManager, source, new_component, InputPinNumber);
								edit_connection->Execute();
							}
							else
							{
								pOut->PrintMsg("ERROR: New Destination Pin is already in a Connection");
							}
						}

					}
					else
					{
						pOut->PrintMsg("ERROR: New Destination Pin Component cannot be a Switch");
					}
				}
				else
				{
					pOut->PrintMsg("ERROR: Invalid Input");
				}
			}
			else
			{
				pOut->PrintMsg("ERROR: Identical Components");
			}
		}
	}
	//deleting edit_connection dynamically created component
	if(edit_connection)
		delete edit_connection;
	
}

bool EditConnection::is_digits(const string& str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}

void EditConnection::Undo()
{}

void EditConnection::Redo()
{}

