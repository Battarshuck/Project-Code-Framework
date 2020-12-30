#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
}

void Component::setLabel(string label) 
{
	this->m_Label = label;
}

bool Component::InArea(int x, int y) 
{

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
{}

Component::~Component()
{}

