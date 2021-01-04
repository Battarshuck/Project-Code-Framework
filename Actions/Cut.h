#pragma once
#include"Action.h"
#include "..\Components\Connection.h"
#include "..\Components\InputPin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\Gate.h"
#include "..\Components\Gate.h"
#include "..\Components\Switch.h"
#include "..\Components\LED.h"

class Cut :public Action
{
private:
    Component* ComponentToBeCut;//component to be copied (just Selected)
    Component* CutComp;//copied component (will be passed to Application Mansger)
    int x, y;    // location of point clicked
    int copyorcut;

public:
    Cut(ApplicationManager* pApp, Component*, Component*&, int&);
    virtual ~Cut(void);

    //Reads parameters required for action to execute
    virtual void ReadActionParameters();
    //Execute action (code depends on action type)
    virtual void Execute();

    virtual void Undo();
    virtual void Redo();

};