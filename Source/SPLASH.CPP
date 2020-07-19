//-------------------------------------------//
//                                           //
//    SPLASH. CPP                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "globals.h"
#include "splash.h"


/////////////////////////////////////
//    TSplashDialog
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TSplashDialog, TDialog )
	EV_WM_ERASEBKGND,
	EV_WM_TIMER,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TSplashDialog
//                        CONSTRUCTOR
//    ===============================
//
TSplashDialog::TSplashDialog( TWindow* parent, TResId resid, TModule* module )
										: TDialog( parent, resid, module )
{
	SplashBitMap = new TBitmap( *GetModule(), SPLASHBITMAP );

	H = SplashBitMap->Height() + 2;
	W = SplashBitMap->Width()  + 2;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TSplashDialog
//                        SetupWindow
//    ===============================
//
void TSplashDialog::SetupWindow()
{
	TDialog::SetupWindow();

	TRect ScreenRect;
	::GetWindowRect( GetDesktopWindow(), &ScreenRect );

	TRect DialogRect;
	GetWindowRect( DialogRect );

	int X = ( ScreenRect.Width()  / 2 ) - ( DialogRect.Width()  / 2 );
	int Y = ( ScreenRect.Height() / 2 ) - ( DialogRect.Height() / 2 );

	SetWindowPos( HWND_TOPMOST, X, Y, W, H, SWP_SHOWWINDOW );

	SetTimer( TIMER_SPLASHDLG_START, TIMER_SPLASH_TIMEOUT_START );
	SetTimer( TIMER_SPLASHDLG_STOP , TIMER_SPLASH_TIMEOUT_STOP  );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TSplashDialog
//                      CleanupWindow
//    ===============================
//
void TSplashDialog::CleanupWindow()
{
	__clock->SetPropVisible( true );	// Show __tool_bar CLOCK
	TDialog::CleanupWindow();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TSplashDialog
//                       EvEraseBkgnd
//    ===============================
//
bool TSplashDialog::EvEraseBkgnd( HDC hDC )
{
	TDC dc( hDC );
	TMemoryDC MemDC( dc );

	MemDC.SelectObject( *SplashBitMap );
	dc.BitBlt( 0, 0, W, H, MemDC, 0, 0, SRCCOPY );

	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TSplashDialog
//                            EvTimer
//    ===============================
//
void TSplashDialog::EvTimer( uint TimerId )
{
	if ( TimerId == TIMER_SPLASHDLG_START )
	{
		KillTimer( TIMER_SPLASHDLG_START );
		PostMessage( WM_CLOSE, 0, 0L );
	}
	else
	{
		if ( *( GetApplication()->GetMainWindow() ))
		{
			KillTimer( TIMER_SPLASHDLG_STOP );
			SetWindowPos( HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE |
							  SWP_SHOWWINDOW );

			::PostMessage( *(GetApplication()->GetMainWindow()),
								WM_INITIALIZECOMM, 0, 0L );
		}
	}
}

