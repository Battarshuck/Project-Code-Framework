#include "Switch.h"
#include<fstream>
using namespace std;
#include"./Connection.h"


Switch::Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut) : m_OutputPin(r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_OutputPin.setComponent(this);
	//set status of switch
	Setswitch(LOW);
	m_OutputPin.setComponent(this);
}

void Switch::Setswitch(STATUS status)
{
	m_OutputPin.setStatus(status);
	
}

STATUS Switch::Getswitch() 
{
	return Status_Switch;
}

void Switch::Operate()
{
	
}


// Function Draw
void Switch::Draw(Output* pOut )
{
	//Call output class and pass gate drawing info to it.
	if (m_OutputPin.getStatus() == LOW)
		pOut->DrawSWITCHOFF(m_GfxInfo, Component::getIsSelected());
	else
		pOut->DrawSWITCHON(m_GfxInfo, Component::getIsSelected());
	
	string m_Label = Component::getLabel();
	pOut->DrawString(m_GfxInfo, m_Label);
}

//returns status of outputpin
int Switch::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

//returns status of Inputpin #n
int Switch::GetInputPinStatus(int n)
{

	return -1;//n starts from 1 but array index starts from 0.
}

void Switch::setInputPinStatus(int n, STATUS s)
{
	
}

OutputPin* Switch::getOutputPin()
{
	return &m_OutputPin;
}

//save 
void Switch::SaveComponent(ofstream& outputFile)
{
	if (getLabel().empty())
		outputFile <<_Switch <<" " << Component::Get_Comp_Id()<<" "<<"$" <<" "<<m_GfxInfo.x1 <<" "<< m_GfxInfo.y1 <<endl;
	else
		outputFile << _Switch << " " << Component::Get_Comp_Id() << " " << getLabel() << " " << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << endl;
}

//Load gate
int* Switch::LoadComponent(ifstream& inputFile)
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