#include "Connection.h"
#include<fstream>
using namespace std;

Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin, InputPin *pDstPin):Component(r_GfxInfo)	
	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
}

Connection::~Connection()
{
	SrcPin->Disconnect(this);
	DstPin->Disconnect(this);
}

void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::Draw(Output* pOut)
{
	pOut->DrawConnection(m_GfxInfo, Component::getIsSelected());
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

bool Connection::InArea(int x, int y)
{
	int mid_point;
	if (m_GfxInfo.x1 < m_GfxInfo.x2)
	{
		mid_point = m_GfxInfo.x1 + (m_GfxInfo.x2 - m_GfxInfo.x1) / 2;

		if (x >= m_GfxInfo.x1 && x <= mid_point && y <= m_GfxInfo.y1 + 8 && y >= m_GfxInfo.y1 - 8)
		{
			return true;
		}
		else if (x >= mid_point - 8 && x <= mid_point + 8 && y <= m_GfxInfo.y1 && y >= m_GfxInfo.y2)
		{
			return true;
		}
		else if (x >= mid_point && x <= m_GfxInfo.x2 && y <= m_GfxInfo.y2 + 8 && y >= m_GfxInfo.y2 - 8)
		{
				return true;
		}
		else if (x >= mid_point - 8 && x <= mid_point + 8 && y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)
		{
			return true;
		}
	}
	else 
	{
		mid_point = m_GfxInfo.x2 + (m_GfxInfo.x1 - m_GfxInfo.x2) / 2;

		if (x <= m_GfxInfo.x1 && x >= mid_point && y <= m_GfxInfo.y1 + 8 && y >= m_GfxInfo.y1 - 8)
		{
			return true;
		}
		else if (x >= mid_point - 8 && x <= mid_point + 8 && y <= m_GfxInfo.y1 && y >= m_GfxInfo.y2)
		{
			return true;
		}
		else if (x <= mid_point && x >= m_GfxInfo.x2 && y <= m_GfxInfo.y2 + 8 && y >= m_GfxInfo.y2 - 8)
		{
			return true;
		}
		else if (x >= mid_point - 8 && x <= mid_point + 8 && y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)
		{
			return true;
		}
	}

	return false;

}

//save 
void Connection ::SaveComponent(ofstream& outputFile)
{
	Component* CompSource;
	Component* CompDestination;	
	CompSource = SrcPin->getComponent();
	CompDestination = DstPin->getComponent();
	outputFile << CompSource->Get_Comp_Id() << " " << CompDestination->Get_Comp_Id() <<" " << DstPin->GetPinNumber() << endl;
}

//Load gate
void Connection::LoadComponent()
{

}


