//-------------------------------------------//
//                                           //
//    OWNERDRW. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "ownerdrw.h"


/////////////////////////////////////
//    TTip
//                        CONSTRUCTOR
//    ===============================
//
TTip::TTip( TWindow* parent, int resID )
{
	HWnd         = parent;
   id           = resID;

   Capture      = true;
   TipWindow    = false;
	TipWndClosed = false;
	IsButtonDown = false;
	IsButtonUp   = false;

	FlyByMsgWnd  = 0;

   ::Module->LoadString( id + 1000, sbuff, sizeof( sbuff ));
   TIC dc( "DISPLAY", 0, 0 );
   dc.SelectObject( TFont( "MS Sans Serif", 8 ));

   size = dc.GetTextExtent( sbuff, strlen( sbuff ));
   HWnd->GetClientRect( rc );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTip
//                 DisplayFlyByWindow
//    ===============================
//
void TTip::DisplayFlyByWindow()
{
	TPoint p = rc.BottomRight(); //( rc.right, rc.bottom );
	HWnd->ClientToScreen( p );

	if ( FlyByMsgWnd )
		delete FlyByMsgWnd;

	FlyByMsgWnd = new TLabel( HWnd, sbuff );
	FlyByMsgWnd->Attr.Style = WS_POPUP;

	FlyByMsgWnd->Attr.X = p.x;
	FlyByMsgWnd->Attr.Y = p.y;
	FlyByMsgWnd->Attr.W = size.cx + 8 + ( size.cx + 8 % 2 ? 1 : 0 );
	FlyByMsgWnd->Attr.H = size.cy + 8 + ( size.cy + 8 % 2 ? 1 : 0 );

	FlyByMsgWnd->Create();
	FlyByMsgWnd->Show( SW_SHOWNOACTIVATE );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTip
//              MouseInsideClientArea
//    ===============================
//
bool TTip::MouseInsideClientArea( TPoint& point )
{
	if ( rc.Contains( point ) )
		  return true;
	else
	{
		if ( IsButtonUp )
		{
			IsButtonUp   = false;
			TipWndClosed = false;
		}

		return false;
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTip
//                          MouseMove
//    ===============================
//
void TTip::MouseMove( uint modKeys, TPoint& point )
{
	if ( !IsButtonDown )
	{
		if ( Capture )
		{
			Capture = false;
			HWndOldCapture = ::GetCapture();

			HWnd->SetCapture();
		}

		if ( MouseInsideClientArea( point ) )
		{
			if ( !TipWndClosed )
			{
				if ( !TipWindow )
				{
					TipWindow = true;
					DisplayFlyByWindow();
				}
			}
		}

		else
		{
			Capture = true;
			HWnd->ReleaseCapture();

			if ( HWndOldCapture )
				::SetCapture( HWndOldCapture );

			if ( TipWindow )
			{
				TipWindow = false;

				if ( FlyByMsgWnd )
					if ( FlyByMsgWnd->HWindow )
						FlyByMsgWnd->Destroy();
			}
		}
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTip
//                        LButtonDown
//    ===============================
//
void TTip::LButtonDown( uint modKeys, TPoint& point )
{
   IsButtonDown = true;

   if ( FlyByMsgWnd )
		if ( FlyByMsgWnd->HWindow )
			FlyByMsgWnd->Destroy();

	HWnd->ReleaseCapture();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTip
//                          LButtonUp
//    ===============================
//
void TTip::LButtonUp( uint modKeys, TPoint& point )
{
	TipWindow    = false;
	TipWndClosed = true;

	Capture      = true;
	IsButtonDown = false;
	IsButtonUp   = true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODAButton
//                        CONSTRUCTOR
//    ===============================
//
TODAButton::TODAButton( TWindow* parent, int resID, TModule* module )
								: TButton( parent, resID, module )
{
	BmpNormal   = new TBitmap( *GetModule(), resID + 1000 );
	BmpDown     = new TBitmap( *GetModule(), resID + 3000 );
	BmpFocus    = new TBitmap( *GetModule(), resID + 5000 );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODAButton
//                               Draw
//    ===============================
//
void TODAButton::Draw( DRAWITEMSTRUCT far& drawInfo, TBitmap* bmp )
{
	TDC dc( drawInfo.hDC );
	TMemoryDC MemDC( dc );

	MemDC.SelectObject( *bmp );
	dc.BitBlt( 0, 0, bmp->Width(), bmp->Height(), MemDC, 0, 0, SRCCOPY );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODAButton
//                      ODADrawEntire
//    ===============================
//
void TODAButton::ODADrawEntire( DRAWITEMSTRUCT far& drawInfo )
{
	if ( drawInfo.itemState & ODS_SELECTED )
		Draw( drawInfo, BmpDown );
	else
		if ( drawInfo.itemState & ODS_FOCUS )
			Draw( drawInfo, BmpFocus );
	else
		Draw( drawInfo, BmpNormal );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODAButton
//                          ODASelect
//    ===============================
//
void TODAButton::ODASelect( DRAWITEMSTRUCT far& drawInfo )
{
	if ( drawInfo.itemState & ODS_SELECTED )
		Draw( drawInfo, BmpDown );
	else
		Draw( drawInfo, BmpFocus );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODATipButton
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TODATipButton, TODAButton )
	EV_WM_MOUSEMOVE,
	EV_WM_LBUTTONDOWN,
	EV_WM_LBUTTONUP,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODATipButton
//                        SetupWindow
//    ===============================
//
void TODATipButton::SetupWindow()
{
	TODAButton::SetupWindow();
	Tip = new TTip( this, id );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODATipButton
//                        EvMouseMove
//    ===============================
//
void TODATipButton::EvMouseMove( uint modKeys, TPoint& point )
{
	Tip->MouseMove( modKeys, point );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODATipButton
//                      EvLButtonDown
//    ===============================
//
void TODATipButton::EvLButtonDown( uint modKeys, TPoint& point )
{
	Tip->LButtonDown( modKeys, point );
	DefaultProcessing();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TODATipButton
//                        EvLButtonUp
//    ===============================
//
void TODATipButton::EvLButtonUp( uint modKeys, TPoint& point )
{
	Tip->LButtonUp( modKeys, point );
	DefaultProcessing();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODARadioBtn
//                        CONSTRUCTOR
//    ===============================
//
TBwccODARadioBtn::TBwccODARadioBtn( TWindow* parent, int resID, TGroupBox* group,
						TModule* module )

						: TRadioButton( parent, resID, group, module )
{
	BmpNormal   = new TBitmap( *GetModule(), resID + 1000 );
	BmpDown     = new TBitmap( *GetModule(), resID + 3000 );
	BmpFocus    = new TBitmap( *GetModule(), resID + 5000 );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODARadioBtn
//                               Draw
//    ===============================
//
void TBwccODARadioBtn::Draw( DRAWITEMSTRUCT far& drawInfo, TBitmap* bmp )
{
	TDC dc( drawInfo.hDC );
	TMemoryDC MemDC( dc );

	MemDC.SelectObject( *bmp );
	dc.BitBlt( 0, 0, bmp->Width(), bmp->Height(), MemDC, 0, 0, SRCCOPY );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODARadioBtn
//                      ODADrawEntire
//    ===============================
//
void TBwccODARadioBtn::ODADrawEntire( DRAWITEMSTRUCT far& drawInfo )
{
	if ( GetCheck() & BF_CHECKED )
		Draw( drawInfo, BmpDown );
	else
		if ( drawInfo.itemState & ODS_SELECTED )
			Draw( drawInfo, BmpFocus );
	else
		Draw( drawInfo, BmpNormal );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODARadioBtn
//                           ODAFocus
//    ===============================
//
void TBwccODARadioBtn::ODAFocus( DRAWITEMSTRUCT far& drawInfo )

{
	if ( drawInfo.itemState & ODS_CHECKED )
		Draw( drawInfo, BmpDown );
	else
		if ( drawInfo.itemState & ODS_FOCUS )
			Draw( drawInfo, BmpFocus );
	else
		Draw( drawInfo, BmpNormal );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODATipRadioBtn
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TBwccODATipRadioBtn, TBwccODARadioBtn )
	EV_WM_MOUSEMOVE,
	EV_WM_LBUTTONDOWN,
	EV_WM_LBUTTONUP,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODATipRadioBtn
//                        SetupWindow
//    ===============================
//
void TBwccODATipRadioBtn::SetupWindow()
{
	TBwccODARadioBtn::SetupWindow();
	Tip = new TTip( this, id );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODATipRadioBtn
//                        EvMouseMove
//    ===============================
//
void TBwccODATipRadioBtn::EvMouseMove( uint modKeys, TPoint& point )
{
	Tip->MouseMove( modKeys, point );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODATipRadioBtn
//                      EvLButtonDown
//    ===============================
//
void TBwccODATipRadioBtn::EvLButtonDown( uint modKeys, TPoint& point )
{
	Tip->LButtonDown( modKeys, point );
	DefaultProcessing();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBwccODATipRadioBtn
//                        EvLButtonUp
//    ===============================
//
void TBwccODATipRadioBtn::EvLButtonUp( uint modKeys, TPoint& point )
{
	Tip->LButtonUp( modKeys, point );
	DefaultProcessing();
}

