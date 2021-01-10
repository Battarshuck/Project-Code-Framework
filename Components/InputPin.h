#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"


class Component; //Forward class declaration
class Connection;	//Forward class declartion

class InputPin: public Pin	//inherited from class Pin
{
private:
	Component* pComp; //Component at which this pin is associated
	int PinNumber;
	Connection* m_Connection; //Connection to this input Pin

public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	bool ConnectTo(Connection*);
	virtual void Disconnect(Connection*);
	Component* getComponent();	//returns the component of this input pin
	void SetPinNumber(int);
	int GetPinNumber();
	bool isConnected();
};

#endif