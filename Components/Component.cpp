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

//fn setIsSelected
void Component::setIsSelected(bool select)
{
	IsSelected = select;
}
//fn getIsSelected
bool Component::getIsSelected()
{
	return IsSelected;
}


bool Component::InArea(int x, int y) 
{
	//Checking if the user click on the component or not
	//by checking the coordination of click
	//with the the component border
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

Component::Component()
{
	setIsSelected(false);
}

Component::~Component()
{}

