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
    Component* ComponentToBeCut;//pointer to Component to be Cut (just Selected)
    Component*& CutComp;//pointer to Cut Component (will be passed to Application Mansger)
    int x, y;    // location of point clicked
    int* CopyOrCut_ptr; //pointer to integer will be assigned to "2" if a Component is cut

public:
    Cut(ApplicationManager* pApp, Component*, Component*&, int*&);
    virtual ~Cut(void);

    //Reads parameters required for action to execute
    virtual void ReadActionParameters();

    //Execute action (code depends on action type)
    virtual void Execute();

    virtual void Undo();
    virtual void Redo();

};