//-------------------------------------------//
//                                           //
//    DIAL .H                                //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _DIAL_H
	#define _DIAL_H

#include <owl\listbox.h>
#include <owl\gauge.h>

#include "centrdlg.h"
#include "ownerdrw.h"
#include "winbolsa.rh"


/*-----------------------------------*
 *          TDialDialog              *
 *-----------------------------------*/

class TDialDialog : public TAutoCenterDialog
{
	public :
		TDialDialog( TWindow* parent, TResId resid, TModule* module = 0 );

		void SetupWindow();
		void CleanupWindow();

	protected :
		// Standard / user windows messages event handlers
		void EvCommNotify( uint CommId, uint Notify );
		void EvTimer( uint timerId );
		LRESULT EvDial( WPARAM wParam, LPARAM lParam );

		DECLARE_RESPONSE_TABLE( TDialDialog );

	private :
		void ComposeDialStr( string& str );
		inline void Repaint() { Invalidate(); UpdateWindow(); }

		void Display( const char* s, bool ClrList = true );
		void SetupLedGauge();

		string DialStr,
				 MemberID,
				 InBuffer;

		int LedValue;
		long TickCnt;

		TListBox *DialStatus;
		TGauge   *LedGauge;

		COMSTAT comstat;
};

#endif   // _DIAL_H

