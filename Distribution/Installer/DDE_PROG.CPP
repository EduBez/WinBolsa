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
#include "Dde_Prog.h"


HDDEDATA FAR PASCAL _export DdeCallBack(WORD type, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD) {
//*************************************************************************
// This call back function is the heart of interaction between this program
// and DDEML.  Because Windows doesn't pass C++ 'this' pointers to call
// back functions, a static 'this' pointer was used.  If you wanted to
// create a Client that would allow for more than one conversation, using a
// List of conversations and their associated 'this' pointers would be one
// possible method to try.  The XTYP_ constants are described in detail in
// the online help.
//*************************************************************************
	switch (type) {
		case XTYP_DISCONNECT:
			MessageBox(NULL, "Disconnected.", "Notice", MB_ICONINFORMATION);
//			This->HConv = 0;
			break;

		case XTYP_ERROR:
			MessageBox(NULL, "A critical DDE error has occured.", "Error", MB_ICONINFORMATION);
	} //EndSwitch

	return 0;
} //End DdeCallBack()


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++ DdeProgMan +++++++++++++++++++++++++++++++++++++++++++++ DdeProgMan +++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


DdeProgMan::DdeProgMan() {
//***************************************************************************
	InstId  = 0;        // MUST be 0 the first time DdeInitialize() is called!
	HConv   = 0;
	Service = 0;
	Topic   = 0;
	TempStringHandle = 0;
	TempText = 0;
	DdeConnected = FALSE;            // Set to TRUE upon successful DdeConnect
} // End DdeProgMan::DdeProgMan()


DdeProgMan::~DdeProgMan() {
//***************************************************************************
// This clean up is required for those resources that were allocated during
// the DDEML conversation.
//***************************************************************************
	if (HConv)
		DdeDisconnect(HConv);        // Let the other party know we are leaving
	//EndIf

	FreeTemps();                                 // Free any temporary storage

	if (InstId) {
		DdeFreeStringHandle(InstId, Service);
		DdeFreeStringHandle(InstId, Topic);
		DdeUninitialize(InstId);
	} //EndIf
} // End DdeProgMan::~DdeProgMan()


boolean DdeProgMan::DdeConnect() {
//***************************************************************************
	switch (DdeInitialize(&InstId, (PFNCALLBACK)/*(FARPROC)*/DdeCallBack, APPCMD_CLIENTONLY, 0)) {
		case DMLERR_NO_ERROR :
			Service = DdeCreateStringHandle(InstId, "PROGMAN", CP_WINANSI);
			Topic   = DdeCreateStringHandle(InstId, "PROGMAN", CP_WINANSI);

			if (Service && Topic) {  // Establish a connection to the DDE server
				HConv = ::DdeConnect(InstId, Service, Topic, 0);

				switch (DdeGetLastError(InstId)) {
					case DMLERR_NO_ERROR :
						DdeConnected = TRUE;
						return TRUE;
					//End case DMLERR_NO_ERROR

					case DMLERR_DLL_NOT_INITIALIZED :
						DMLErr(DMLERR_DLL_NOT_INITIALIZED);
						return FALSE;
					//End case DMLERR_DLL_NOT_INITIALIZED

					case DMLERR_INVALIDPARAMETER :
						DMLErr(DMLERR_INVALIDPARAMETER);
						return FALSE;
					//End case DMLERR_INVALIDPARAMETER

					case DMLERR_NO_CONV_ESTABLISHED :
						DMLErr(DMLERR_NO_CONV_ESTABLISHED);
						return FALSE;
					//End case DMLERR_NO_CONV_ESTABLISHED

					default :                            // Should never get here!
						GenErr(ERR_UNKNOWNCASE);
						return FALSE;
					//End default
				} //EndSwitch
			} else {
				GenErr(ERR_DIDNOTCONNECT);
				return FALSE;
			} //EndIf
		//End case DMLERR_NO_ERROR

		case DMLERR_DLL_USAGE :
			DMLErr(DMLERR_DLL_USAGE);
			return FALSE;
		//End case DMLERR_DLL_USAGE

		case DMLERR_INVALIDPARAMETER :
			DMLErr(DMLERR_INVALIDPARAMETER);
			return FALSE;
		//End case DMLERR_INVALIDPARAMETER

		case DMLERR_SYS_ERROR :
			DMLErr(DMLERR_SYS_ERROR);
			return FALSE;
		//End case DMLERR_SYS_ERROR

		default :									          // Should never get here!
			GenErr(ERR_UNKNOWNCASE);
			return FALSE;
		//End default
	} //EndSwitch
} // End DdeProgMan::DdeConnect()


boolean DdeProgMan::DdeClientTransaction(UINT uType) {
//***************************************************************************
// Establish a connection to the DDE server
//***************************************************************************
	switch (uType) {
		case XTYP_EXECUTE :
			hProgData = ::DdeClientTransaction((LPBYTE)commands, strlen(commands) + 1, HConv, 0L, CF_TEXT, XTYP_EXECUTE, 1000, 0);
			break;

		case XTYP_REQUEST :
			if (TempStringHandle)       // If it's been used, we need to free it
				DdeFreeStringHandle(InstId, TempStringHandle); // We also do one last cleanup in the destructor
			//EndIf

			TempStringHandle = DdeCreateStringHandle(InstId, commands, CP_WINANSI);
			hProgData = ::DdeClientTransaction(NULL, 0, HConv, TempStringHandle, CF_TEXT, XTYP_REQUEST, 5000, NULL);
			break;

		default:                                       // Should never get here
			return FALSE;
	} //EndSwitch

	switch (DdeGetLastError(InstId)) {
		case DMLERR_NO_ERROR :
			return TRUE;
		//End case DMLERR_NO_ERROR

		case DMLERR_ADVACKTIMEOUT :
			DMLErr(DMLERR_ADVACKTIMEOUT);
			return FALSE;
		//End case DMLERR_ADVACKTIMEOUT

		case DMLERR_BUSY :
			DMLErr(DMLERR_BUSY);
			return FALSE;
		//End case DMLERR_BUSY

		case DMLERR_DATAACKTIMEOUT :
			DMLErr(DMLERR_DATAACKTIMEOUT);
			return FALSE;
		//End case DMLERR_DATAACKTIMEOUT

		case DMLERR_DLL_NOT_INITIALIZED :
			DMLErr(DMLERR_DLL_NOT_INITIALIZED);
			return FALSE;
		//End case DMLERR_DLL_NOT_INITIALIZED

		case DMLERR_EXECACKTIMEOUT :
			// We will, of course, get an EXECACKTIMEOUT because ProgMan doesn't
			// exist anymore -- so we ignore the error in this case.
			if ( strcmp(commands, "[ExitProgman(0)]") || strcmp(commands, "[ExitProgman(1)]")  )
				return TRUE;
			else {
				DMLErr(DMLERR_EXECACKTIMEOUT);
				return FALSE;
			} //EndIf
		//End case DMLERR_EXECACKTIMEOUT

		case DMLERR_INVALIDPARAMETER :
			DMLErr(DMLERR_INVALIDPARAMETER);
			return FALSE;
		//End case DMLERR_INVALIDPARAMETER

		case DMLERR_MEMORY_ERROR :
			DMLErr(DMLERR_MEMORY_ERROR);
			return FALSE;
		//End case DMLERR_MEMORY_ERROR

		case DMLERR_NO_CONV_ESTABLISHED :
			DMLErr(DMLERR_NO_CONV_ESTABLISHED);
			return FALSE;
		//End case DMLERR_NO_CONV_ESTABLISHED

		case DMLERR_NOTPROCESSED :
			DMLErr(DMLERR_NOTPROCESSED);
			return FALSE;
		//End case DMLERR_NOTPROCESSED

		case DMLERR_POKEACKTIMEOUT :
			DMLErr(DMLERR_POKEACKTIMEOUT);
			return FALSE;
		//End case DMLERR_POKEACKTIMEOUT

		case DMLERR_POSTMSG_FAILED :
			DMLErr(DMLERR_POSTMSG_FAILED);
			return FALSE;
		//End case DMLERR_POSTMSG_FAILED

		case DMLERR_REENTRANCY :
			DMLErr(DMLERR_REENTRANCY);
			return FALSE;
		//End case DMLERR_REENTRANCY

		case DMLERR_SERVER_DIED :
			DMLErr(DMLERR_SERVER_DIED);
			return FALSE;
		//End case DMLERR_SERVER_DIED

		case DMLERR_UNADVACKTIMEOUT :
			DMLErr(DMLERR_UNADVACKTIMEOUT);
			return FALSE;
		//End case DMLERR_UNADVACKTIMEOUT

		default :                         			    // Should never get here!
			GenErr(ERR_UNKNOWNCASE);
			return FALSE;
		//End default
	} //EndSwitch
} //End DdeProgMan::DdeClientTransaction()

DWORD DdeProgMan::DdeGetData(LPSTR pDest, DWORD cbMax){
//***************************************************************************
	DWORD len;
	len = ::DdeGetData(hProgData, pDest, cbMax,  0);

	switch (DdeGetLastError(InstId)) {
		case DMLERR_NO_ERROR :
			return len;
		//End case DMLERR_NO_ERROR

		case DMLERR_DLL_NOT_INITIALIZED :
			DMLErr(DMLERR_DLL_NOT_INITIALIZED);
			return 0;
		//End case DMLERROR_DLL_NOT_INITIALIZED

//		case DMLERR_INVALID_HDDEDATA :    // Seems to not be supported!

		case DMLERR_INVALIDPARAMETER :
			DMLErr(DMLERR_INVALIDPARAMETER);
			return 0;
		//End case DMLERR_INVALIDPARAMETER

		default :                                      // Should never get here
			GenErr(ERR_UNKNOWNCASE);
			return 0;
	} //EndSwitch
} //End DdeProgMan::DdeGetData()


boolean DdeProgMan::CreateGroup(LPSTR GroupName) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[CreateGroup(\"%s\")]", GroupName);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::CreateGroup()


boolean DdeProgMan::CreateGroup(LPSTR GroupName, LPSTR GroupPath) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[CreateGroup(\"%s\",%s)]", GroupName, GroupPath);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::CreateGroup()


boolean DdeProgMan::ShowGroup(LPSTR GroupName, int ShowCommand){
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	if ( (ShowCommand >= 1) && (ShowCommand <= 8) ) {
		wsprintf(commands, "[ShowGroup(\"%s\", %d)]", (LPSTR)GroupName, ShowCommand);
		return DdeClientTransaction(XTYP_EXECUTE);
	} else {
		return FALSE;
	} //EndIf
} //End DdeProgMan::ShowGroup()


boolean DdeProgMan::DeleteGroup(LPSTR GroupName) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[DeleteGroup(\"%s\")]", GroupName);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::DeleteGroup()


boolean DdeProgMan::ReloadGroup(LPSTR GroupName) {
//***************************************************************************
// Not behaving as expected.
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[Reload(\"%s\")]", GroupName);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::ReloadGroup()


boolean DdeProgMan::RequestGroups() {
//***************************************************************************
	DWORD len;

	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "Groups");
	if (DdeClientTransaction(XTYP_REQUEST)) {
		if (TempText) {
			delete TempText;
		} //EndIf

		len = DdeGetData(NULL, 0);                              // request size
		TempText = new char[len];
		len = DdeGetData(TempText, len);                        // request data
		return TRUE;
	} else
		return FALSE;
	//EndIf
} //End DdeProgMan::RequestGroups()


boolean DdeProgMan::RequestGroup(LPSTR GroupName) {
//***************************************************************************
// The request for a non-existant groups information will cause a GPF when
// using raw DDE commands to ProgMan. The begining logic ensures that the
// group exists before it's information is requested. The function will
// return TRUE is successful or FALSE if a DDE request was unsuccessful or
// if the group does not exist.
//
// The structure of data returned by Progman is (with the second line
// repeated for each item):
//    "group_name",qualified_group_path,number_of_items,window_status
//    "item_name","cmdline",working_directory,qualified_icon_path,X,Y,iconindex,hotkey,minimize
// NOTE: the window_status parameter can be any value between 1 and 8 and is
//       the same value that is passed as the second param to the ShowGroup()
//       command.
// NOTE: the hotkey parameter is in numeric form
//***************************************************************************
	DWORD len, arglen;
	LPSTR strptr;
	char r, n;

	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	RequestGroups();
	strptr = strstr(TempText, GroupName);

	if (strptr) {
		arglen = strlen(GroupName);
		r = *(strptr+arglen);
		n = *(strptr+arglen+1);

		if ( (r == '\r') && (n == '\n') ) {                     // Group exists
			wsprintf(commands, "%s", GroupName); // NOW let's request group info

			if (DdeClientTransaction(XTYP_REQUEST)) {
				if (TempText) {
					delete TempText;
				} //EndIf

				len = DdeGetData(NULL, 0);                        // request size
				TempText = new char[len];
				len = DdeGetData(TempText, len);                  // request data
				return TRUE;
			} else
				return FALSE;
			//EndIf
		} else {
			return FALSE;                                 // Group doesn't exist
		} //EndIf
	} else {
		return FALSE;                                    // Group doesn't exist
	} //EndIf
} //End DdeProgMan::RequestGroup()


boolean DdeProgMan::AddItem(LPSTR CmdLine) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[AddItem(%s)]", CmdLine);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::AddItem()


boolean DdeProgMan::AddItem(LPSTR CmdLine, LPSTR ItemName) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[AddItem(%s,\"%s\")]", CmdLine, ItemName);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::AddItem()


boolean DdeProgMan::AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[AddItem(%s,\"%s\",%s)]", CmdLine, ItemName, IconPath);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::AddItem()


boolean DdeProgMan::AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[AddItem(%s,\"%s\",%s,%d)]", CmdLine, ItemName, IconPath, IconIndex);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::AddItem()


boolean DdeProgMan::AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex, int xPos, int yPos) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[AddItem(%s,\"%s\",%s,%d,%d,%d)]", CmdLine, ItemName, IconPath, IconIndex, xPos, yPos);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::AddItem()


boolean DdeProgMan::AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex, int xPos, int yPos, LPSTR DefDir) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[AddItem(%s,\"%s\",%s,%d,%d,%d,%s)]", CmdLine, ItemName, IconPath, IconIndex, xPos, yPos, DefDir);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::AddItem()


boolean DdeProgMan::AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex, int xPos, int yPos, LPSTR DefDir, LPSTR HotKey) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[AddItem(%s,\"%s\",%s,%d,%d,%d,%s,\"%s\")]", CmdLine, ItemName, IconPath, IconIndex, xPos, yPos, DefDir, HotKey);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::AddItem()


boolean DdeProgMan::AddItem(LPSTR CmdLine, LPSTR ItemName, LPSTR IconPath, int IconIndex, int xPos, int yPos, LPSTR DefDir, LPSTR HotKey, boolean fMinimize) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[AddItem(%s,\"%s\",%s,%d,%d,%d,%s,\"%s\",%d)]", CmdLine, ItemName, IconPath, IconIndex, xPos, yPos, DefDir, HotKey, fMinimize);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::AddItem()


boolean DdeProgMan::ReplaceItem(LPSTR ItemName) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[ReplaceItem(\"%s\")]", ItemName);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::ReplaceItem()


boolean DdeProgMan::DeleteItem(LPSTR ItemName) {
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "[DeleteItem(\"%s\")]", ItemName);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::DeleteItem()


boolean DdeProgMan::RequestItems(LPSTR GroupName) {
//***************************************************************************
	int pTempText = 1;
	int tempCtr   = 0;

	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	if ( !RequestGroup(GroupName) )
		return FALSE;                    // Group nonexistant or request failed
	//EndIf

	// Strip off leading record of group information
	while ( (TempText[pTempText] != '\r') && (TempText[pTempText+1] != '\n') ) {
		pTempText++;
	} //EndWhile
	pTempText+=3;

	while (TempText[pTempText] != NULL) {
		while (TempText[pTempText] != '\"') {
			TempText[tempCtr++] = TempText[pTempText++];
		} //EndWhile

		while ( (TempText[pTempText] != '\r') && (TempText[pTempText+1] != '\n') ) {
			pTempText++;
		} //EndWhile

		TempText[tempCtr++] = '\r';
		TempText[tempCtr++] = '\n';
		pTempText += 3;
	} //EndWhile

	TempText[tempCtr++] = NULL;

	return TRUE;
} //End DdeProgMan::RequestItems()


boolean DdeProgMan::FreeForm(LPSTR Commands) {
//***************************************************************************
// Does not work with Requests (because is XTYP_EXECUTE and not XTYP_REQUEST)
//***************************************************************************
	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	wsprintf(commands, "%s", Commands);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::FreeForm()


boolean DdeProgMan::ExitProgman(boolean bSaveGroups) {
//***************************************************************************
	int SaveGroups;

	if (!DdeConnected)
		if (!DdeConnect())
			return FALSE;
		//EndIf
	//EndIf

	if (bSaveGroups)      // This filters nonzero entries to 1 for later use in
		SaveGroups = TRUE; // DMLERR_EXECACKTIMEOUT exception handling.
	//EndIf

	wsprintf(commands, "[ExitProgman(%d)]", SaveGroups);
	return DdeClientTransaction(XTYP_EXECUTE);
} //End DdeProgMan::ExitProgman()


void DdeProgMan::FreeTemps(void) {
//***************************************************************************
	if (TempText) {                   // If it's been used, we need to free it
		delete TempText;
		TempText = NULL;
	} //EndIf

	if (TempStringHandle) {           // If it's been used, we need to free it
		DdeFreeStringHandle(InstId, TempStringHandle);
		TempText = NULL;
	} //EndIf
} //End DdeProgMan::FreeTemps()


void DdeProgMan::DMLErr(int err){
//***************************************************************************
	char msg[750];

	switch (err) {
		case DMLERR_BUSY :
			strcpy(msg, "DMLERR_BUSY  0x4001  ddeml.h\nThe response to the transaction caused the DDE_FBUSY bit to be set.");
			break;
		case DMLERR_ADVACKTIMEOUT :
			strcpy(msg, "DMLERR_ADVACKTIMEOUT  0x4000  ddeml.h\nA request for a synchronous advise transaction has timed out.");
			break;
		case DMLERR_DATAACKTIMEOUT :
			strcpy(msg, "DMLERR_DATAACKTIMEOUT  0x4002  ddeml.h\nA request for a synchronous data transaction has timed out.");
			break;
		case DMLERR_DLL_NOT_INITIALIZED :
			strcpy(msg, "DMLERR_DLL_NOT_INITIALIZED  0x4003  ddeml.h\nA DDEML function was called without first calling the DdeInitialize function, or an invalid instance identifier was passed to a DDEML function.");
			break;
		case DMLERR_DLL_USAGE :
			strcpy(msg, "DMLERR_DLL_USAGE  0x4004  ddeml.h\nAn application initialized as APPCLASS_MONITOR has attempted to perform a DDE transaction, or an application initialized as APPCMD_CLIENTONLY has attempted to perform server transactions.");
			break;
		case DMLERR_EXECACKTIMEOUT :
			strcpy(msg, "DMLERR_EXECACKTIMEOUT  0x4005  ddeml.h\nA request for a synchronous execute transaction has timed out.");
			break;
		case DMLERR_INVALIDPARAMETER :
			strcpy(msg, "DMLERR_INVALIDPARAMETER  0x4006  ddeml.h\nA parameter failed to be validated by the DDEML. Some of the possible causes are as follows:\n* The application used a data handle initialized with a different item-name handle than required by the transaction.\n* The application used a data handle that was initialized with a different clipboard data format than required by the transaction.\n* The application used a client-side conversation handle with a server-side function or vise versa.\n* The application used a freed data handle or string handle. \n* More than one instance of the application used the same object.");
			break;
		case DMLERR_MEMORY_ERROR :
			strcpy(msg, "DMLERR_MEMORY_ERROR 0x4008  ddeml.h");
			break;
		case DMLERR_NO_CONV_ESTABLISHED :
			strcpy(msg, "DMLERR_NO_CONV_ESTABLISHED 0x400a  ddeml.h");
			break;
		case DMLERR_NOTPROCESSED :
			strcpy(msg, "DMLERR_NOTPROCESSED 0x4009  ddeml.h");
			break;
		case DMLERR_POKEACKTIMEOUT :
			strcpy(msg, "DMLERR_POKEACKTIMEOUT 0x400b  ddeml.h");
			break;
		case DMLERR_POSTMSG_FAILED :
			strcpy(msg, "DMLERR_POSTMSG_FAILED 0x400c  ddeml.h");
			break;
		case DMLERR_REENTRANCY :
			strcpy(msg, "DMLERR_REENTRANCY 0x400d  ddeml.h");
			break;
		case DMLERR_SERVER_DIED :
			strcpy(msg, "DMLERR_SERVER_DIED 0x400e  ddeml.h");
			break;
		case DMLERR_SYS_ERROR :
			strcpy(msg, "DMLERR_SYS_ERROR 0x400f  ddeml.h");
			break;
		case DMLERR_UNADVACKTIMEOUT :
			strcpy(msg, "DMLERR_UNADVACKTIMEOUT 0x4010  ddeml.h");
			break;
		default :
			GenErr(ERR_UNKNOWNCASE);
			return;
	} //EndSwitch

	MessageBox(NULL, msg, "DDEML Error", MB_OK) ;
} //End DdeProgMan::DMLErr()


void DdeProgMan::GenErr(int err){
//***************************************************************************
	char msg[750];

	switch (err) {
		case ERR_UNKNOWNCASE :
			strcpy(msg, "Unknown case.");
			break;
		case ERR_PARAMOUTOFBOUNDS :
			strcpy(msg, "Parameter out of bounds");
			break;
		case ERR_DIDNOTCONNECT :
			strcpy(msg, "DDEConnect did not.");
			break;
		case ERR_PARSEERROR :
			strcpy(msg, "Error while parsing Group data.");
			break;
		default :              // Absolutely, Positively, should never get here
			MessageBox(NULL, msg, "Unknown case in General Error module", MB_OK) ;
			return;
	} //EndSwitch

	MessageBox(NULL, msg, "General Error", MB_OK) ;
} //End DdeProgMan::GenErr()
