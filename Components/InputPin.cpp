#include "InputPin.h"
#include<iostream>
InputPin::InputPin()
{}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}
void InputPin::SetPinNumber(int PinIndex)
{
	std::cout << PinIndex << " hi "<<std::endl;
	PinNumber = PinIndex+1;
}
int InputPin::GetPinNumber()
{
	return PinNumber;
}