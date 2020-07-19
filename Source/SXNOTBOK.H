//-------------------------------------------//
//                                           //
//    NOTEBOOK .H                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _NOTEBOOK_H
	#define _NOTEBOOK_H

#include <saxtabs.h>

#include "centrdlg.h"
#include "winbolsa.rh"


/*-----------------------------------*
 *           TNoteBookPage           *
 *-----------------------------------*/

class TNoteBookPage : public TDialog
{
	public :
		TNoteBookPage( TWindow* parent, const char* title, TResId resid,
							TModule* module = 0 );

		void CmOk() { Parent->CloseWindow( IDOK ); }
		void CmCancel();
		bool CanClose();

		bool PreProcessMsg( MSG& Msg );

	protected :
		// Standard / user windows messages event handlers
		void EvShowWindow( bool show, uint status );

		DECLARE_RESPONSE_TABLE( TNoteBookPage );

		const char* Caption;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *          TNoteBookTab1            *
 *-----------------------------------*/

class TNoteBookTab1 : public TNoteBookPage
{
	public :
		TNoteBookTab1( TWindow* parent, const char* title, TResId resid,TModule* module = 0 );

	private :
		TEdit *Id,
				*PassWord,
				*Phone;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *          TNoteBookTab2            *
 *-----------------------------------*/

class TNoteBookTab2 : public TNoteBookPage
{
	public :
		TNoteBookTab2( TWindow* parent, const char* title, TResId resid,TModule* module = 0 );

	private :
		TRadioButton *Pulse,
						 *Tone;

		TEdit        *Prefix,
						 *Signal;

		TCheckBox    *UsePrefix;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *          TNoteBookTab3            *
 *-----------------------------------*/

class TNoteBookTab3 : public TNoteBookPage
{
	public :
		TNoteBookTab3( TWindow* parent, const char* title, TResId resid,TModule* module = 0 );

	private :
		TEdit *InitString,
				*TimeOutTime;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *          TNoteBookTab4            *
 *-----------------------------------*/

class TNoteBookTab4 : public TNoteBookPage
{
	public :
		TNoteBookTab4( TWindow* parent, const char* title, TResId resid,TModule* module = 0 );

		void SetupWindow();
		bool CanClose();

	private :
		TRadioButton *Baud300    , *Baud600      , *Baud1200,
						 *Baud2400   , *Baud4800     , *Baud9600     , *Baud19200,
						 *Data5      , *Data6        , *Data7        , *Data8    ,
						 *Stop1      , *Stop15       , *Stop2        ,
						 *ParityNone , *ParityOdd    ,
						 *ParityEven , *ParityMark   , *ParitySpace  ,
						 *FlowNone   , *FlowHardware , *FlowXonXoff  ,
						 *ComNone    , *Com1         , *Com2         , *Com3 , *Com4;
};

//----------------------------------------------------------------------------//

/*----------------------------------*
 *          TNoteBookFrame          *
 *----------------------------------*/

class TNoteBookFrame : public TAutoCenterDialog, public TVbxEventHandler
{
	public :
		TNoteBookFrame( TWindow* parent, TResId resid, TModule* module = 0 );

		void SetupWindow();
		void Destroy( int retVal = 0 );
		bool PreProcessMsg( MSG& Msg );

		bool IsComm;

	protected :
		inline void SetupTabCtl();

		// Message response functions
		LRESULT EvMessage( WPARAM wParam, LPARAM lParam );

		// VBX event handler
		void EvClick( VBXEVENT FAR* event );

		DECLARE_RESPONSE_TABLE( TNoteBookFrame );

	private :
		TNoteBookTab1 *Tab1Dlg;
		TNoteBookTab2 *Tab2Dlg;
		TNoteBookTab3 *Tab3Dlg;
		TNoteBookTab4 *Tab4Dlg;

		int TabIndex,
			 PrevTabIndex;

		TVbxSaxTab* TabCtl;
};


#endif   // _NOTEBOOK_H

