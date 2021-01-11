#include "InputPin.h"
#include "Connection.h"

InputPin::InputPin()
{
	m_Connection = NULL;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

bool InputPin::ConnectTo(Connection* r_connection)
{
	if (r_connection && m_Connection == NULL)
	{
		m_Connection = r_connection;
		return true;
	}

	return false;
}

void InputPin::Disconnect(Connection* r_connection)
{
	if(r_connection && r_connection == m_Connection)
		m_Connection = NULL;
}

Component* InputPin::getComponent()
{
	return pComp;
}
void InputPin::SetPinNumber(int PinIndex)
{
	PinNumber = PinIndex+1;
}
int InputPin::GetPinNumber()
{
	return PinNumber;
}
bool InputPin::isConnected()
{
	if (m_Connection)
		return true;

	return false;
}