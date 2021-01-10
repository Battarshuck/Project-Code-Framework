#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include"OutputPin.h"
#include"InputPin.h"


//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
	bool IsSelected;
	int Comp_ID;//Component ID
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	
	
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	//setting and getting component's label
	void setLabel(string label);
	string getLabel();
	virtual bool InArea(int x, int y);
	GraphicsInfo getLocation();

	//set and get function IsSelected
	void setIsSelected(bool);
	bool getIsSelected();

	//save and load component
	virtual void SaveComponent(ofstream&);
	virtual void LoadComponent();

	//Set and Get ID
	void Set_Comp_ID(int);
	int Get_Comp_Id();

	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
