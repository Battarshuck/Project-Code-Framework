#include "NOR3.h"
NOR3::NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
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

}


// Function Draw
// Draws 3-input NOR gate
void NOR3::Draw(Output* pOut, bool selected)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOR3(m_GfxInfo);
	string m_Label = Component::getLabel();
	pOut->DrawString(m_GfxInfo, m_Label);
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
