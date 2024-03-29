#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include <fstream>
#include "..\Components\Pin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\InputPin.h"

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface
	Component* ComponentIsSelected;//pointer to component selected
	GraphicsInfo r_GfxInfoUsed;//parameteres of selected component
	Component* ComponenetIsCopied_Cut;//pointer to copied component
	int CopyOrcut;//An integer to distinguish between Copied and Cut Componenet
	int* CopyOrCut_ptr;//pointer to CopyOrCut integer
	//ifstream inputFile;//
	MODE mode;
	int RecycleBinIndex;
	Component* RecycleBin[MaxCompCount];



public:


public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window
	void Refresh();

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);
	//Components getters
	Component* getComponent(int, int, GraphicsInfo& r_GfxInfo);
	Component* getComponentBy_ID(int );
	//unselect functions
	void UnselectOtherComponents(Component*);
	void UnselectComponent();
	void TurnOffComponents();
	//Remove functions
	void Remove(Component*&);
	void Remove_Connections(OutputPin* = NULL, InputPin* = NULL);
	//check if the component list is empty or not
	bool IsCompListEmpty();

	// Save components
	void save(ofstream&);
	//Load components
	void load(ifstream&);
	//Undo and Redo
	void undofn();
	void redofn();
	void AddToRecycleBin(Component*);
	void EmptyRecycleBin();

	//destructor
	~ApplicationManager();
};

#endif