//-------------------------------------------//
//                                           //
//    FLYBYBTN. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "flybybtn.h"


/////////////////////////////////////
//    TFlyByTIPButton
//                        CONSTRUCTOR
//    ===============================
//
TFlyByTIPButton::TFlyByTIPButton( TResId uiBitmap, int id, TType type,
											 bool enable, TState state, bool repeat )

											 : TButtonGadget( uiBitmap, id, type,
																	enable, state, repeat )
{
	SetNotchCorners( false );
	FlyByMsgWnd = 0;

	::Module->LoadString( id + 1000, sbuff, sizeof( sbuff ));
	TIC dc( "DISPLAY", 0, 0 );

	dc.SelectObject( TFont( "MS Sans Serif", 8 ));
	size = dc.GetTextExtent( sbuff, strlen( sbuff ));
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TFlyByTIPButton
//                        LButtonDown
//    ===============================
//
void TFlyByTIPButton::LButtonDown( uint modkeys, TPoint& point )
{
	TButtonGadget::LButtonDown( modkeys, point );

	if ( FlyByMsgWnd )
	{
		FlyByMsgWnd->Destroy();
		delete FlyByMsgWnd;
		FlyByMsgWnd = 0;
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TFlyByTIPButton
//                         MouseEnter
//    ===============================
//
void TFlyByTIPButton::MouseEnter( uint modkeys, TPoint& point )
{
	TButtonGadget::MouseEnter( modkeys, point );
	r = GetBounds();

	TPoint p( r.right, r.bottom + 4 );
	Window->ClientToScreen( p );

	FlyByMsgWnd = new TLabel( Window, sbuff, TColor::LtYellow );
	FlyByMsgWnd->Attr.Style = WS_POPUP;

	FlyByMsgWnd->Attr.X = p.x ;
	FlyByMsgWnd->Attr.Y = p.y ;
	FlyByMsgWnd->Attr.W = size.cx + 8 + ( size.cx + 8 % 2 ? 1 : 0 );
	FlyByMsgWnd->Attr.H = size.cy + 8 + ( size.cy + 8 % 2 ? 1 : 0 );

	FlyByMsgWnd->Create();
	FlyByMsgWnd->Show( SW_SHOWNOACTIVATE );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TFlyByTIPButton
//                         MouseLeave
//    ===============================
//
void TFlyByTIPButton::MouseLeave( uint modkeys, TPoint& point )
{
	TButtonGadget::MouseLeave( modkeys, point );

	if ( FlyByMsgWnd )
	{
		FlyByMsgWnd->Destroy();
		delete FlyByMsgWnd;
		FlyByMsgWnd = 0;
	}
}

