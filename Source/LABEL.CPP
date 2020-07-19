//-------------------------------------------//
//                                           //
//    LABEL. CPP                             //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "label.h"


/////////////////////////////////////
//    TLabel
//                     GetWindowClass
//    ===============================
//
void TLabel::GetWindowClass( WNDCLASS &wndClass )
{
	TWindow::GetWindowClass( wndClass );
	wndClass.style |= CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TLabel
//                              Paint
//    ===============================
//
void TLabel::Paint( TDC& dc, bool erase, TRect& rect )
{
	TRect rc = GetClientRect();

	if ( LTip )
	{
		dc.TextRect( rc, TColor::Black );
		rc.left += 1; rc.top += 1; rc.right -= 1; rc.bottom -= 1;
	}

	dc.TextRect( rc, Color );

	if ( LTip )
	{
		TBrush HighLight( ::GetSysColor( COLOR_BTNHIGHLIGHT ));
		TBrush Shadow( ::GetSysColor( COLOR_BTNSHADOW ));

		dc.SelectObject( HighLight );
		dc.PatBlt( 1, 1, Attr.W - 2, 1 );
		dc.PatBlt( 1, 1, 1, Attr.H - 2 );

		dc.SelectObject( Shadow );
		dc.PatBlt( 2, Attr.H - 2, Attr.W - 4, 1 );
		dc.PatBlt( Attr.W - 2, 2, 1, Attr.H - 3 );
	}

	if ( LTip )
	{
		TFont Font( "MS Sans Serif", 8 );
		dc.SelectObject( Font );
	}

	dc.DrawText( Text, -1, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
}

