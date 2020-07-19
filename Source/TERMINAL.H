//_________________________________________//
//                                         //
//    TERMINAL. H                          //
//    	Copyright (C) 1994, 1995, 1996    //
//				by Eduardo Bezerra             //
//_________________________________________//


#ifndef _TERMINAL_H
	#define _TERMINAL_H

#include <owl\edit.h>
#include <owl\layoutwi.h>
#include <owl\mdichild.h>


/////////////////////////////////////
//                          TTerminal
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TTerminal : public TLayoutWindow
{
	public :
		TTerminal( TWindow* parent = 0, const char far *title = 0, TModule* module = 0 );

		void SetupWindow();
		void Clear() { EditCtl->SetText( "" ); }

		TTerminal& operator <<( string s );
		void SendKeyStroke( uint VkKey, int RepeatCount = 1 );

	protected :
		HBRUSH EvCtlColor( HDC hDC, HWND HWndChild, uint CtlType );

		DECLARE_RESPONSE_TABLE( TTerminal );

	private :
		TEdit* EditCtl;

		TPointer<TBrush> EditBrush;
		TPointer<TFont>  EditFont;

		TLayoutMetrics lm;

		uint sPos,
			  ePos,
			  CurLine,
			  Lines,
			  NumChars,
			  size;
};
//_____________________________________________________________________________

/////////////////////////////////////
//                  TMDIChildTerminal
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TMDIChildTerminal : public TMDIChild
{
	public :
		TMDIChildTerminal( TMDIClient& parent, const char far* title = 0,
								 TWindow* clientWnd = 0, bool shrinkToClient = false,
								 TModule* module = 0 );
		void SetupWindow();

		bool CanClose() { return false; }
		void Clear() { Terminal->Clear(); }

		TMDIChildTerminal& operator <<( string s ) { *Terminal << s; return *this; }

	protected :
		// Standard / user windows messages event handlers
		void EvMDIActivate( HWND hWndActivated, HWND hWndDeactivated );

		DECLARE_RESPONSE_TABLE( TMDIChildTerminal );

	private :
		TTerminal* Terminal;
};

#endif // _TERMINAL_H

