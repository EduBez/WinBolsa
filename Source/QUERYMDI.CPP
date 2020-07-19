//-------------------------------------------//
//                                           //
//    QUERYMDI. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "globals.h"
#include "querymdi.h"


/////////////////////////////////////
//    TQueryMDIChild
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TQueryMDIChild, TMDIChild )
	EV_WM_MDIACTIVATE,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryMDIChild
//                        CONSTRUCTOR
//    ===============================
//
TQueryMDIChild::TQueryMDIChild( int CmID, TMDIClient& parent, const char far* title,
										  TWindow* clientWnd, bool shrinkToClient,
										  TModule* module )

										  : TMDIChild( parent, title, clientWnd,
															shrinkToClient, module )
{
	SetIcon( GetModule(), "WinBolsaMDIChild" );
	command = CmID;

	if ( CmID )
	{
		TButtonGadget::TType type;

		if ( CmID == GARQBIG || CmID == GARQBR )
			type = TButtonGadget::NonExclusive;
		else
			type = TButtonGadget::Command;

		SetMenuDescr( TMenuDescr( CmID + CM_NULL, 0, 1, 1, 0, 0, 0 ));

		ButtonGadget = new TFlyByTIPButton( CM_RUNQUERY, CmID + CM_NULL, type );
		Separator    = new TSeparatorGadget( 12 );
	}
	else
		SetMenuDescr( TMenuDescr( IDM_NO_GARQ, 0, 1, 0, 0, 0, 0 ));
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryMDIChild
//                         DESTRUCTOR
//    ===============================
//
TQueryMDIChild::~TQueryMDIChild()
{
	if ( command )
	{
		delete ButtonGadget;
		delete Separator;
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryMDIChild
//                      EvMDIActivate
//    ===============================
//
void TQueryMDIChild::EvMDIActivate( HWND hWndActivated, HWND hWndDeactivated )
{
	TMDIChild::EvMDIActivate( hWndActivated, hWndDeactivated );

	if ( *this == hWndActivated )
	{
		if ( command )
		{
			__tool_bar->Insert( *ButtonGadget, TGadgetWindow::Before, __speed_button_1 );
			__tool_bar->Insert( *Separator, TGadgetWindow::After, ButtonGadget );
		}
		__tool_bar->LayoutSession();
	}

	else if ( *this == hWndDeactivated )
	{
		if ( command )
		{
			__tool_bar->Remove( *ButtonGadget );
			__tool_bar->Remove( *Separator );
		}
	}
}

