#include "XOR2.h"
XOR2::XOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XOR2::Operate()
{
	if (m_InputPins[0].getStatus() == LOW && m_InputPins[1].getStatus() == LOW)

		m_OutputPin.setStatus(LOW);

	else if (m_InputPins[0].getStatus() == LOW && m_InputPins[1].getStatus() == HIGH)

		m_OutputPin.setStatus(HIGH);

	else if (m_InputPins[0].getStatus() == HIGH && m_InputPins[1].getStatus() == LOW)

		m_OutputPin.setStatus(HIGH);

	else
		m_OutputPin.setStatus(LOW);

	//caclulate the output status as the XORing of the two input pins
//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void XOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR2(m_GfxInfo, Component::getIsSelected());
	string m_Label = Component::getLabel();
	pOut->DrawString(m_GfxInfo, m_Label);
}

//returns status of outputpin
int XOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
