#include "OutputPin.h"
#include "Connection.h"

OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;		//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS: r_FanOut;	//set the fan out of the pin.
}

//Functionn ConnectTo:
//Connects the ouput pin the the passed connection if the fan out permits
//if the no. of connections is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(Connection *r_Conn)
{
	if(m_Conn < m_FanOut)
	{
		m_Connections[m_Conn++] = r_Conn;	//add a new connection the the array of connections
		return true;
	}
	
	return false;	//can't connect to any more connections
}

Connection* OutputPin::getConnection(int index)
{
	return m_Connections[index];
}

int OutputPin::getNum_Connections() 
{
	return m_Conn;
}

void OutputPin::Disconnect(Connection* r_conn)
{
	
	int i;
	bool check = false; 
	for (i = 0; i < m_Conn; i++)
	{
		if (m_Connections[i] == r_conn)
		{
			check = true;
			break;
		}
	}

	if (check)
	{
		m_Connections[i] = NULL;

		if (i < m_Conn)
		{

			for (int j = i; j < m_Conn; j++)
			{
				m_Connections[j] = m_Connections[j + 1];
			}

			m_Conn--;

		}
	}

}

int OutputPin::getOutputConnections()
{
	return m_Conn;
}

Component* OutputPin::getComponent()
{
	return pComp;
}

void OutputPin::setComponent(Component* pCmp)
{
	this->pComp = pCmp;
}

bool OutputPin::isConnected()
{
	if (m_Conn == m_FanOut)
		return true;
	
	return false;
}

