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
	if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == LOW)

		m_OutputPin.setStatus(LOW);

	else if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == HIGH)

		m_OutputPin.setStatus(HIGH);

	else if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == LOW)

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

//save 
void XOR2::SaveComponent(ofstream& outputFile)
{
	if (getLabel().empty())
		outputFile << _XOR2 << " " << Component::Get_Comp_Id() << " " << "$" << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
	else
		outputFile << _XOR2 << " " << Component::Get_Comp_Id() << " " << getLabel() << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

//Load gate
int* XOR2::LoadComponent(ifstream& inputFile)
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