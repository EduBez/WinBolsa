#ifndef DdeProg_H
//***************************************************************************
// Program Manager Shell Dynamic-Data Exchange Interface (3.1)
//
// Version 0.97
// DdeProgMan - (C) Copyright 1995 by Michael Weber
//
// Send sugestions or error reports to Michael Weber:
//    * via Compuserve [71301,1221]
//    * via Internet   mweber@pcbuoa.ako.dec.com
//
// Tabs are set to 3 ***
//***************************************************************************
#include <ddeml.h>
#include <string.h>
#include <stdlib.h>

#define boolean int
#define TRUE    1
#define FALSE   0
#define ERR_UNKNOWNCASE      100
#define ERR_DIDNOTCONNECT    101
#define ERR_PARAMOUTOFBOUNDS 102
#define ERR_PARSEERROR		  103


class DdeProgMan {
	public:
		LPSTR TempText; // Holds result of Request... methods and valid until next Request... call

		DdeProgMan();
		~DdeProgMan();
      boolean DdeConnect();

		boolean CreateGroup(LPSTR GroupName);
		boolean CreateGroup(LPSTR GroupName, LPSTR GroupPath);
		boolean ShowGroup(LPSTR GroupName, int ShowCommand);
		boolean DeleteGroup(LPSTR GroupName);
		boolean ReloadGroup(LPSTR GroupName);
		boolean RequestGroups();
		boolean RequestGroup(LPSTR GroupName);
		boolean AddItem(LPSTR CmdLine);
		boolean AddItem(LPSTR CmdLine, LPSTR ItemName);
		boolean AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath);
		boolean AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex);
		boolean AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex, int xPos, int yPos);
		boolean AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex, int xPos, int yPos, LPSTR DefDir);
		boolean AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex, int xPos, int yPos, LPSTR DefDir, LPSTR HotKey);
		boolean AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex, int xPos, int yPos, LPSTR DefDir, LPSTR HotKey, boolean fMinimize);
		boolean ReplaceItem(LPSTR ItemName);
		boolean DeleteItem(LPSTR ItemName);

		boolean RequestItems(LPSTR GroupName);

		boolean FreeForm(LPSTR Command);
		boolean ExitProgman(int bSaveGroups=0);
		void    FreeTemps();

	protected:
		virtual void GenErr(int err);
		virtual void DMLErr(int err);

	private:
		DWORD   InstId;
		HCONV   HConv;
		HSZ     Service;
		HSZ     Topic;
		HSZ     TempStringHandle;
		char    commands[1024]; // wsprintf has a 1024 buffer limit. A good improvement would be to make this dynamic.
		boolean DdeConnected;         // Set to TRUE upon successful DdeConnect
		HDDEDATA hProgData;

		boolean DdeClientTransaction(UINT uType);
		DWORD DdeGetData(LPSTR pDest, DWORD cbMax);   // Set pDest to NULL to determine return buffer size. cbMax is the size of the buffer pDest
}; //End class DdeProgMan

#endif

