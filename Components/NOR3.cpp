#include "NOR3.h"
NOR3::NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NOR3::Operate()
{
	Pin m;
	if (m_InputPins[0].getStatus() == LOW && m_InputPins[1].getStatus() == LOW)

		m.setStatus(HIGH);

	else

		m_OutputPin.setStatus(LOW);

	if (m.getStatus() == LOW && m_InputPins[2].getStatus() == LOW)

		m_OutputPin.setStatus(LOW);

	else

		m_OutputPin.setStatus(HIGH);
	//caclulate the output status as the XORing of the two input pins
//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void NOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawAND2(m_GfxInfo);
}

//returns status of outputpin
int NOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

//returns status of Inputpin #n
int NOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
