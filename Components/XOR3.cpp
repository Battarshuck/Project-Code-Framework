#include "XOR3.h"

XOR3::XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XOR3::Operate()
{
	if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == LOW && GetInputPinStatus(3) == LOW)

		m_OutputPin.setStatus(LOW);

	else if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == LOW && GetInputPinStatus(3) == HIGH)

		m_OutputPin.setStatus(HIGH);

	else if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == HIGH && GetInputPinStatus(3) == LOW)

		m_OutputPin.setStatus(HIGH);

	else if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == HIGH && GetInputPinStatus(3) == HIGH)

		m_OutputPin.setStatus(LOW);//
	
	else if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == LOW && GetInputPinStatus(3) == LOW)

		m_OutputPin.setStatus(HIGH);

	else if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == LOW && GetInputPinStatus(3) == HIGH)

		m_OutputPin.setStatus(LOW);

	else if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == HIGH && GetInputPinStatus(3) == LOW)

		m_OutputPin.setStatus(LOW);

	else if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == HIGH && GetInputPinStatus(3) == HIGH)

		m_OutputPin.setStatus(HIGH);
}


// Function Draw
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR3(m_GfxInfo, Component::getIsSelected());
	string m_Label = Component::getLabel();
	pOut->DrawString(m_GfxInfo, m_Label);
}

//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

//save 
void XOR3::SaveComponent(ofstream& outputFile)
{
	if (getLabel().empty())
		outputFile << _XOR3 << " " << Component::Get_Comp_Id() << " " << "$"<< " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
	else
		outputFile << _XOR3 << " " << Component::Get_Comp_Id() << " " << getLabel() << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

//Load gate
int* XOR3::LoadComponent(ifstream& inputFile)
{
	int id_;
	string label_;
	inputFile >> id_;
	Component::Set_Comp_ID(id_);
	inputFile >> label_;
	if (label_ != "$")
		Component::setLabel(label_);
	inputFile >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2 = m_GfxInfo.x1 + UI.AND2_Width;
	m_GfxInfo.y2 = m_GfxInfo.y1 + UI.AND2_Height;
	return NULL;
}
