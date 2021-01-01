#include "LED.h"


LED::LED(const GraphicsInfo &r_GfxInfo, int r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_InputPin.setComponent(this);
}

InputPin* LED::getInputPins()
{
	return &m_InputPin;
}

void LED::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
}


// Function Draw
// Draws LED
void LED::Draw(Output* pOut, bool selected)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawLED(m_GfxInfo);
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
