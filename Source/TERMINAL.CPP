//_________________________________________//
//                                         //
//    TERMINAL. CPP                        //
//    	Copyright (C) 1994, 1995, 1996    //
//				by Eduardo Bezerra             //
//_________________________________________//


#include "globals.h"
#include "terminal.h"
#include "winbolsa.rh"


/////////////////////////////////////
//    TTerminal
//                     RESPONSE_TABLE
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DEFINE_RESPONSE_TABLE1( TTerminal, TLayoutWindow )
	EV_WM_CTLCOLOR,
END_RESPONSE_TABLE;
//_____________________________________________________________________________

/////////////////////////////////////
//    TTerminal
//                        CONSTRUCTOR
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TTerminal::TTerminal( TWindow* parent, const char far *title, TModule* module )
							 : TLayoutWindow( parent, title, module ),
								TWindow( parent, title, module )
{
	EditBrush = new TBrush( TColor::Black );
	EditFont  = new TFont( (HFONT)::GetStockObject( SYSTEM_FIXED_FONT ) );
	EditCtl   = new TEdit( this, -1, "", 0, 0, 0, 0, 0, true );

	EditCtl->Attr.Style &= ~WS_HSCROLL & ~ES_AUTOHSCROLL;

	lm.X.Set     ( lmLeft   , lmAbsolute , lmParent  , lmLeft   );
	lm.Width.Set ( lmWidth  , lmSameAs   , lmParent  , lmWidth  );
	lm.Y.Set     ( lmTop    , lmSameAs   , lmParent  , lmTop    );
	lm.Height.Set( lmHeight , lmSameAs   , lmParent  , lmHeight );

	SetChildLayoutMetrics( *EditCtl, lm );
}
//_____________________________________________________________________________

/////////////////////////////////////
//    TTerminal
//                        SetupWindow
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TTerminal::SetupWindow()
{
	TLayoutWindow::SetupWindow();

	EditCtl->SetReadOnly( true );
	EditCtl->SendMessage( WM_SETFONT, (WPARAM(HFONT(*EditFont))), 0L );
}
//_____________________________________________________________________________

/////////////////////////////////////
//    TTerminal
//                         operator<<
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TTerminal& TTerminal::operator <<( string s )
{
	EditCtl->GetSelection( sPos, ePos );            // Get current caret position

	CurLine = EditCtl->GetLineFromPos( ePos );      // Get caret line number
	Lines   = EditCtl->GetNumLines() - 1;           // Get number of lines

	NumChars  = EditCtl->GetLineIndex ( Lines );    // Get number of chars before 'Lines'
	NumChars += EditCtl->GetLineLength( Lines );    // Add current line number of chars

	if ( NumChars >= TERMINAL_MAX_LENGTH )          // If reached maximum size
		Clear();                                     // Clear edit buffer
	else
		EditCtl->SetSelection( NumChars, NumChars ); // Go to last line

	size = (TERMINAL_RIGHT_MARGIN ) - EditCtl->GetLineLength(-1);

	while ( s.length() >= size )
	{
		::WaitMessage();
		string v = s.substr( 0, size );

		EditCtl->Insert( v.c_str() );
		EditCtl->Insert( "\r\n" );

		s = s.substr( size );
		size = TERMINAL_RIGHT_MARGIN;
	}

	EditCtl->Insert( s.c_str() );
	return *this;
}
//_____________________________________________________________________________

/////////////////////////////////////
//    TTerminal
//                      SendKeyStroke
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TTerminal::SendKeyStroke( uint VkKey, int RepeatCount )
{
	WORD code = ::MapVirtualKey( VkKey, 0 );

	for ( int i = 0; i < RepeatCount; i++ )
	{
		SendMessage( WM_KEYDOWN, VkKey, MAKELPARAM( 1, code ) );
		SendMessage( WM_KEYUP  , VkKey, MAKELPARAM( 1, 0xC000 | code ) );
	}
}
//_____________________________________________________________________________

/////////////////////////////////////
//    TTerminal
//                         EvCtlColor
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
HBRUSH TTerminal::EvCtlColor( HDC hDC, HWND HWndChild, uint CtlType )
{
	if ( CtlType == CTLCOLOR_EDIT )
	{
		TDC dc( hDC );
		dc.SetTextColor( TColor::LtGray );

		dc.SetBkColor( TColor::Black );
		return *EditBrush;
	}

	if ( CtlType == CTLCOLOR_MSGBOX )
		return *EditBrush;

	return (HBRUSH)NULL;
}
//_____________________________________________________________________________

/////////////////////////////////////
//    TMDIChildTerminal
//                     RESPONSE_TABLE
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DEFINE_RESPONSE_TABLE1( TMDIChildTerminal, TMDIChild )
	EV_WM_MDIACTIVATE,
END_RESPONSE_TABLE;
//_____________________________________________________________________________

/////////////////////////////////////
//    TMDIChildTerminal
//                        CONSTRUCTOR
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TMDIChildTerminal::TMDIChildTerminal( TMDIClient& parent, const char far* title,
						 TWindow* clientWnd, bool shrinkToClient, TModule* module )

						 : TMDIChild( parent, title, clientWnd, shrinkToClient, module )
{
	Attr.Style &= ~WS_VISIBLE;
	Terminal = new TTerminal;

	SetIcon( GetModule(), "WinBolsaTerminal" );
	SetMenuDescr( TMenuDescr( IDM_TERMINAL, 0, 1, 0, 0, 0, 0 ));
}
//_____________________________________________________________________________

/////////////////////////////////////
//    TMDIChildTerminal
//                        SetupWindow
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMDIChildTerminal::SetupWindow()
{
	TMDIChild::SetupWindow();
	SetClientWindow( Terminal );
}
//_____________________________________________________________________________

/////////////////////////////////////
//    TMDIChildTerminal
//                      EvMDIActivate
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TMDIChildTerminal::EvMDIActivate( HWND hWndActivated, HWND hWndDeactivated )
{
	TMDIChild::EvMDIActivate( hWndActivated, hWndDeactivated );

	if ( *this == hWndActivated )
		__tool_bar->LayoutSession();
}

