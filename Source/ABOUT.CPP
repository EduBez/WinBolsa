//-------------------------------------------------//
//                                                 //
//    ABOUT. CPP                                   //
//                                                 //
//    Copyright (C) 1994, 1995 by Eduardo Bezerra  //
//                                                 //
//-------------------------------------------------//


#include "about.h"


/////////////////////////////////////
//    TAboutDlg
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TAboutDlg, TAutoCenterDialog )
	EV_WM_ERASEBKGND,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TAboutDlg
//                        CONSTRUCTOR
//    ===============================
//
TAboutDlg::TAboutDlg( TWindow* parent, TResId resid, TModule* module )
							 : TAutoCenterDialog( parent, resid, module )
{
	AboutBmp = new TBitmap( *GetModule(), ABOUTBITMAP );
	new TODAButton( this, IDOK );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TAboutDlg
//                       EvEraseBkgnd
//    ===============================
//
bool TAboutDlg::EvEraseBkgnd( HDC hDC )
{
	TAutoCenterDialog::EvEraseBkgnd( hDC );

	TDC dc( hDC );
	TMemoryDC MemDC( dc );

	MemDC.SelectObject( *AboutBmp );
	dc.BitBlt( 11, 15, 66, 66, MemDC, 0, 0, SRCCOPY );

   return true;
}

