#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pOut)
{
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar

	string StringDisplayed;
	char EnteredChar;
	keytype PressedKey;

	pWind->FlushKeyQueue();
	while (true)
	{
		PressedKey = pWind->WaitKeyPress(EnteredChar);

		if (EnteredChar == '\r')
		{
			pWind->FlushMouseQueue();

			pOut->PrintMsg(" ");

			break;
		}
		else if (EnteredChar == '\b')
		{
			if (StringDisplayed.length() > 0)
			{

				int StringLength = StringDisplayed.length();

				StringDisplayed.erase(StringLength - 1, 1);

				pOut->PrintMsg(StringDisplayed);
			}
		}

		else if (PressedKey == ESCAPE)
		{
			StringDisplayed.clear();
			pOut->PrintMsg(" ");
			break;
		}
		else //If the entered character is neither "Enter" or "Backspace"
		{
			StringDisplayed += EnteredChar; //The entered character is added to the displayed string on the status bar

			pOut->PrintMsg(StringDisplayed);
		}
	}
	return StringDisplayed;

}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check which Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_XOR: return ADD_XOR_GATE_2;
			case ITM_XNOR: return ADD_XNOR_GATE_2;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_NOR3: return ADD_NOR_GATE_3;
			case ITM_XOR3: return ADD_XOR_GATE_3;
			case ITM_INV: return ADD_INV;
			case ITM_Buff: return ADD_Buff;
			case ITM_Switch: return ADD_Switch;
			case ITM_LED: return ADD_LED;
			case ITM_CONNECTION: return ADD_CONNECTION;
			case ITM_EXIT: return EXIT;	
			
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}


		if (y <= UI.height - UI.StatusBarHeight && y >= UI.height - UI.StatusBarHeight - UI.SimBarHeight) 
		{

			int ClickedItemOrder = (x / UI.SimItemWidth);

			switch (ClickedItemOrder)
			{
				case ITM_DSN_MODE:return DSN_MODE;
				case ITM_SIM_MODE:return SIM_MODE;
				case ITM_ADD_Label:return ADD_Label;
				case ITM_EDIT_Label:return EDIT_Label;
				case ITM_COPY:return COPY;
				case ITM_CUT:return CUT;
				case ITM_PASTE:return PASTE;
				case ITM_DEL:return DEL;
				case ITM_SAVE:return SAVE;
				case ITM_LOAD:return LOAD;
				case ITM_UNDO:return UNDO;
				case ITM_REDO:return REDO;
				case ITM_EDIT_CONNECTION:return EDIT_Connection;
			}
		}

	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight - UI.SimBarHeight - 8)
		{
			return SELECT;	//user want to select/unselect a component
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{

		if (y <= UI.height - UI.StatusBarHeight && y >= UI.height - UI.StatusBarHeight - UI.SimBarHeight)
		{

			int ClickedItemOrder = (x / UI.SimItemWidth);

			switch (ClickedItemOrder)
			{
			//case ITM_TRUTH:return Create_TruthTable;
			case ITM_DSN_MODE: return DSN_MODE;
			case ITM_SIM_MODE:return SIM_MODE;
			//case ITM_STATUSBAR:return STATUS_BAR;
			default: DSN_TOOL;
			}
		}

		if (y > UI.SimBarHeight && y < UI.height - UI.StatusBarHeight- UI.SimBarHeight)
		{
			return SELECT;
		}

		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
	}

}


Input::~Input()
{
}
