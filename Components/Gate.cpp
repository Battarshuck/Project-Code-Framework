#include "Gate.h"

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_Inputs = r_Inputs;
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	m_OutputPin.setComponent(this);
	//Associate all input pins to this gate
	for (int i = 0; i < m_Inputs; i++)
	{
		m_InputPins[i].setComponent(this);
		m_InputPins[i].SetPinNumber(i);
	}
		
}

InputPin* Gate::getInputPins() 
{
	return m_InputPins;
}

InputPin* Gate::getInputPins(int index)
{
	return &m_InputPins[index];
}

OutputPin* Gate::getOutputPin()
{
	return &m_OutputPin;
}

int Gate::numInputs() 
{
	return m_Inputs;
}

int Gate::getOutputConnections()
{
	return m_OutputPin.getOutputConnections();
}

//save 
void Gate::SaveComponent(ofstream&)
{

}

//Load gate
void Gate::LoadComponent()
{

}