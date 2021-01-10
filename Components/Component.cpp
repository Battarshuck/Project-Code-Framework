#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
	setIsSelected(false);
}

void Component::setLabel(string label) 
{
	this->m_Label = label;
}

string Component::getLabel()
{
	return m_Label;
}

//function setIsSelected
void Component::setIsSelected(bool select)
{
	IsSelected = select;
}
//function getIsSelected
bool Component::getIsSelected()
{
	return IsSelected;
}
//Set and Get Component ID
void Component:: Set_Comp_ID(int Comp_Index)
{
	Comp_ID = Comp_Index;
}
int Component::Get_Comp_Id()
{
	return Comp_ID;
}

bool Component::InArea(int x, int y) 
{
	//Checking if the user click on the component or not
	//by checking the coordination of click
	//with the component border
	if (x >= m_GfxInfo.x1 && x <= m_GfxInfo.x2 && y >= m_GfxInfo.y1 && y <= m_GfxInfo.y2)
	{
		return 1;
	}

	return 0;
}

GraphicsInfo Component::getLocation() 
{
	return m_GfxInfo;
}

int Component::numInputs()
{
	return 0;
}

OutputPin* Component::getOutputPin()
{
	return NULL;
}

InputPin* Component::getInputPins(int x)
{
	return NULL;
}

InputPin* Component::getInputPins()
{
	return NULL;
}

Component::Component()
{
	setIsSelected(false);
}

Component::~Component()
{}

//save 
void Component::SaveComponent(ofstream&)
{

}

//Load gate
void Component::LoadComponent()
{

}