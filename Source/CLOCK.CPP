//-------------------------------------------//
//                                           //
//    CLOCK. CPP                             //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "clock.h"


/////////////////////////////////////
//    TClock
//                        SetupWindow
//    ===============================
//
void TClock::SetupWindow()
{
	TVbxMhClock::SetupWindow();

	PICTURE pict;
	memset( &pict, '\x0', sizeof( PICTURE ));
	pict.Type = '\x1';
	pict.Data.Bitmap.Bitmap = GetModule()->LoadBitmap( IDG_CLOCK );

	hPict = VBXCreatePicture( &pict );
	SetPropPictureDClock( hPict );

	SetPropStyle( Style_3_24_hour_digital_with_seconds );
	SetPropTextColor( TColor::LtGreen );
	SetPropBestFit( true );

	SetPropFontName( string( "TZ_DIG" ));
	SetPropFontSize( 165.0L );
	SetPropFontBold( false );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TClock
//                      CleanupWindow
//    ===============================
//
void TClock::CleanupWindow()
{
	VBXDestroyPicture( hPict );
	TVbxMhClock::CleanupWindow();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TClock
//                               Show
//    ===============================
//
void TClock::Show( bool Boolean )
{
   if ( Boolean )
      SetPropTextColor( TColor::LtGreen );

   else
      SetPropTextColor( TColor::Black );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TClock
//                            SetTime
//    ===============================
//
void TClock::SetTime( int Hour, int Minute, int Second )
{
   Show( false );

   SetPropHour( Hour );
   SetPropMinute( Minute );
   SetPropSecond( Second );

   // Wait 1 second to update display
   for ( DWORD t = GetTickCount() + 1000L;  GetTickCount() <= t; )
      ;
   Show( true );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TClock
//                            GetTime
//    ===============================
//
void TClock::GetTime( int& Hour, int& Minute, int& Second )
{
   GetPropHour( Hour );
   GetPropMinute( Minute );
   GetPropSecond( Second );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TClock
//                              Reset
//    ===============================
//
void TClock::Reset()
{
   SetTime( 23, 59, 59 );
}

