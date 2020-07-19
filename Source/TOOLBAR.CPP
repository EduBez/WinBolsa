//-------------------------------------------//
//                                           //
//    TOOLBAR. CPP                           //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "globals.h"


/////////////////////////////////////
//    TCtrlBar
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TCtrlBar, TControlBar )
	EV_WM_ERASEBKGND,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TCtrlBar
//                        CONSTRUCTOR
//    ===============================
//
TCtrlBar::TCtrlBar( TWindow* parent, TTileDirection direction, TFont* font,
						  TModule* module )

						  : TControlBar( parent, direction, font, module )
{
	SetHintMode( EnterHints );
	Bitmap = new TBitmap( *GetModule(), GRAYINGBITMAP );
	Brush  = new TBrush( *Bitmap );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TCtrlBar
//                        SetupWindow
//    ===============================
//
void TCtrlBar::SetupWindow()
{
   TControlBar::SetupWindow();
   #ifdef BC_5x
   EnableTooltip(false);
   #endif
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TCtrlBar
//                       EvEraseBkgnd
//    ===============================
//
bool TCtrlBar::EvEraseBkgnd( HDC hDC )
{
	TRect rc;
	TDC dc( hDC );

	TPen HighLight( ::GetSysColor( COLOR_BTNHIGHLIGHT ));
	TPen Shadow( ::GetSysColor( COLOR_BTNSHADOW ));

	GetClientRect( rc );
	dc.FillRect( rc, *Brush );

	dc.SelectObject( HighLight );
	dc.MoveTo( rc.left,    rc.top );
	dc.LineTo( rc.right+1, rc.top );

	dc.SelectObject( Shadow );
	dc.MoveTo( rc.left,    rc.bottom-1 );
	dc.LineTo( rc.right+1, rc.bottom-1 );

	return true;
}

