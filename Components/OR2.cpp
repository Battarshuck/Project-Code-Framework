#include "OR2.h"

OR2::OR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void OR2::Operate()
{
	if (GetInputPinStatus(1) == HIGH || GetInputPinStatus(2) == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 2-input OR gate
void OR2::Draw(Output* pOut )
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawOR2(m_GfxInfo, Component::getIsSelected());
	string m_Label = Component::getLabel();
	pOut->DrawString(m_GfxInfo, m_Label);
}

//returns status of outputpin
int OR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int OR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void OR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

//save 
void OR2::SaveComponent(ofstream& outputFile)
{
	if (getLabel().empty())
		outputFile << _OR2 << " " << Component::Get_Comp_Id() << " " << "$"<< " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
	else
		outputFile << _OR2 << " " << Component::Get_Comp_Id() << " " << getLabel() << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

//Load gate
int* OR2::LoadComponent(ifstream& inputFile)
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