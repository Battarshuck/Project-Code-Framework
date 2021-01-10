#include "LED.h"
#include<fstream>
using namespace std;

LED::LED(const GraphicsInfo &r_GfxInfo, int r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	setInputPinStatus(1,LOW);
	m_InputPin.setComponent(this);
	m_InputPin.SetPinNumber(1);
}

//set led status
void LED::setLEDStatus(STATUS stat)
{
	m_InputPin.setStatus(stat);
}

InputPin* LED::getInputPins()
{
	return &m_InputPin;
}

void LED::Operate()
{
	if (GetInputPinStatus(1) == HIGH)
	{
		setInputPinStatus(1, HIGH);
	}
	else
	{
		setInputPinStatus(1, LOW);
	}
}


// Function Draw
// Draws LED
void LED::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if(m_InputPin.getStatus() == LOW)
		pOut->DrawLEDOFF(m_GfxInfo, Component::getIsSelected());
	else
		pOut->DrawLEDON(m_GfxInfo, Component::getIsSelected());
	string m_Label = Component::getLabel();
	pOut->DrawString(m_GfxInfo, m_Label);
}

//returns status of outputpin
int LED::GetOutPinStatus()	
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)	
{
	return m_InputPin.getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin.setStatus(s);
}


//save 
void LED::SaveComponent(ofstream& outputFile)
{
	outputFile << "Led " << getLabel() << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

//Load gate
void LED::LoadComponent()
{

}

