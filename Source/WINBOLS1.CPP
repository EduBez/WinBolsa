//-------------------------------------------//
//                                           //
//    WINBOLS1. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "winbolsa.h"


// 	TDrvdApp function definition directory
// 	--------------------------------------
//
// 	1) ReadIniPrivateFile
// 	2) WriteIniPrivateFile
//    3) Encode
// 	4) PreEncode


/////////////////////////////////////
//    TDrvdApp
//                 ReadIniPrivateFile
//    ===============================
//
void TDrvdApp::ReadIniPrivateFile()
{
	if ( access( __ini_file_name.c_str(), 0 ) == 0 )
	{
		nCmdShow = GetPrivateProfileInt( "WindowPos", "Maximized", 0, __ini_file_name.c_str() )
													? SW_SHOWMAXIMIZED : nCmdShow;

		if ( nCmdShow == SW_SHOWMAXIMIZED )
		{
			GetMainWindow()->Attr.W  = GetSystemMetrics( SM_CXSCREEN );
			GetMainWindow()->Attr.H  = GetSystemMetrics( SM_CYSCREEN );
			GetMainWindow()->Attr.X  = 0;
			GetMainWindow()->Attr.Y  = 0;
		}
		else
		{
			GetMainWindow()->Attr.X = GetPrivateProfileInt( "WindowPos", "X",  0, __ini_file_name.c_str() );
			GetMainWindow()->Attr.Y = GetPrivateProfileInt( "WindowPos", "Y",  0, __ini_file_name.c_str() );
			GetMainWindow()->Attr.W = GetPrivateProfileInt( "WindowPos", "W", 10, __ini_file_name.c_str() );
			GetMainWindow()->Attr.H = GetPrivateProfileInt( "WindowPos", "H", 10, __ini_file_name.c_str() );
		}

		__notebook_tab_2.Pulse     = GetPrivateProfileInt( "Line", "Pulse",     1, __ini_file_name.c_str() );
		__notebook_tab_2.Tone      = GetPrivateProfileInt( "Line", "Tone",      0, __ini_file_name.c_str() );
		__notebook_tab_2.UsePrefix = GetPrivateProfileInt( "Line", "UsePrefix", 0, __ini_file_name.c_str() );

		GetPrivateProfileString( "Stock", "Id",       "", __notebook_tab_1.Id,
										 sizeof( __notebook_tab_1.Id ),    __ini_file_name.c_str() );

		GetPrivateProfileString( "Stock", "Password", "", __notebook_tab_1.Passw,
										 sizeof( __notebook_tab_1.Passw ), __ini_file_name.c_str() );
		Encode( false );

		GetPrivateProfileString( "Stock", "Phone",    "", __notebook_tab_1.Phone,
										 sizeof( __notebook_tab_1.Phone ),  __ini_file_name.c_str() );

		GetPrivateProfileString( "Line", "Prefix",    "", __notebook_tab_2.Prefix,
										 sizeof( __notebook_tab_2.Prefix ), __ini_file_name.c_str() );

		GetPrivateProfileString( "Line", "Signal",    "", __notebook_tab_2.Signal,
										 sizeof( __notebook_tab_2.Signal ), __ini_file_name.c_str() );

		GetPrivateProfileString( "Modem", "InitString",  "", __notebook_tab_3.InitString,
										 sizeof( __notebook_tab_3.InitString ), __ini_file_name.c_str() );

		GetPrivateProfileString( "Modem", "TimeoutTime", "", __notebook_tab_3.TimeoutTime,
										 sizeof( __notebook_tab_3.TimeoutTime ), __ini_file_name.c_str() );
	}

	else
	{
		__is_dirty = true;

		GetMainWindow()->Attr.W  = GetSystemMetrics( SM_CXSCREEN );
		GetMainWindow()->Attr.H  = GetSystemMetrics( SM_CYSCREEN );
		GetMainWindow()->Attr.X  = 0;
		GetMainWindow()->Attr.Y  = 0;

		__notebook_tab_2.Pulse     = 1;
		__notebook_tab_2.Tone      = 0;
		__notebook_tab_2.UsePrefix = 0;

		#if 0
			strcpy( __notebook_tab_1.Id,    "57100165" );
			strcpy( __notebook_tab_1.Passw, "EDU"      );
		#endif

		strcpy( __notebook_tab_1.Phone,       "2711990" );
		strcpy( __notebook_tab_3.InitString,  "ATS0=0Q0V1&C1&D2" );
		strcpy( __notebook_tab_3.TimeoutTime, "90"      );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                WriteIniPrivateFile
//    ===============================
//
void TDrvdApp::WriteIniPrivateFile()
{
	char sbuff[5] = "";

	// Changes in SIZE / POSITION or changes in
	// configuration tabs 'BOLSA, DISCAGEM, MODEM'

	if ( __is_dirty )
	{
		if ( !GetMainWindow()->IsIconic() )
		{
			TRect r = GetMainWindow()->GetWindowRect();

			itoa( r.left, sbuff, 10 );
			WritePrivateProfileString( "WindowPos", "X", sbuff, __ini_file_name.c_str() );

			itoa( r.top, sbuff, 10 );
			WritePrivateProfileString( "WindowPos", "Y", sbuff, __ini_file_name.c_str() );

			itoa( r.right  - r.left, sbuff, 10 );
			WritePrivateProfileString( "WindowPos", "W", sbuff, __ini_file_name.c_str() );

			itoa( r.bottom - r.top , sbuff, 10 );
			WritePrivateProfileString( "WindowPos", "H", sbuff, __ini_file_name.c_str() );

			WritePrivateProfileString( "WindowPos", "Maximized", GetMainWindow()->IsZoomed() ? "1" : "0",
												__ini_file_name.c_str() );
		}
		else if ( access( __ini_file_name.c_str(), 0 ) )
		{
			int W = 0.8 * GetSystemMetrics( SM_CXSCREEN );
			int H = 0.7 * GetSystemMetrics( SM_CYSCREEN );

			itoa( ( GetSystemMetrics( SM_CXSCREEN ) - W ) / 2, sbuff, 10 );
			WritePrivateProfileString( "WindowPos", "X", sbuff, __ini_file_name.c_str() );

			itoa( GetSystemMetrics( SM_CYSCREEN ) - ( 0.9 * GetSystemMetrics( SM_CYSCREEN )), sbuff, 10 );
			WritePrivateProfileString( "WindowPos", "Y", sbuff, __ini_file_name.c_str() );

			itoa( W, sbuff, 10 );
			WritePrivateProfileString( "WindowPos", "W", sbuff, __ini_file_name.c_str() );

			itoa( H, sbuff, 10 );
			WritePrivateProfileString( "WindowPos", "H", sbuff, __ini_file_name.c_str() );

			WritePrivateProfileString( "WindowPos", "Maximized", GetMainWindow()->IsZoomed() ? "1" : "0",
												__ini_file_name.c_str() );
		}
	}

	Encode( true );

	WritePrivateProfileString( "Stock", "Id",        __notebook_tab_1.Id,     __ini_file_name.c_str() );
	WritePrivateProfileString( "Stock", "Password",  __notebook_tab_1.Passw,  __ini_file_name.c_str() );
	WritePrivateProfileString( "Stock", "Phone",     __notebook_tab_1.Phone,  __ini_file_name.c_str() );

	itoa( __notebook_tab_2.Pulse, sbuff, 10 );
	WritePrivateProfileString( "Line", "Pulse", sbuff, __ini_file_name.c_str() );

	itoa( __notebook_tab_2.Tone, sbuff, 10 );
	WritePrivateProfileString( "Line", "Tone",  sbuff, __ini_file_name.c_str() );

	WritePrivateProfileString( "Line",  "Prefix", __notebook_tab_2.Prefix, __ini_file_name.c_str() );

	itoa( __notebook_tab_2.UsePrefix, sbuff, 10 );
	WritePrivateProfileString( "Line", "UsePrefix", sbuff, __ini_file_name.c_str() );

	WritePrivateProfileString( "Line",  "Signal", __notebook_tab_2.Signal, __ini_file_name.c_str() );

	WritePrivateProfileString( "Modem", "InitString",  __notebook_tab_3.InitString,  __ini_file_name.c_str() );
	WritePrivateProfileString( "Modem", "TimeoutTime", __notebook_tab_3.TimeoutTime, __ini_file_name.c_str() );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//		TDrvdApp
//                             Encode
//    ===============================
//
void TDrvdApp::Encode( bool IsToEncode )
{
	// ID and PASSWORD can't be null
	if ( strlen( __notebook_tab_1.Id ) && strlen( __notebook_tab_1.Passw ))
	{
		Str4ten Id, Passw;

		if ( IsToEncode )
		{
			PreEncode( __notebook_tab_1.Id, ' ', ENCODECHAR, sizeof( __notebook_tab_1.Id ));
			Id.encode( __notebook_tab_1.Id, ENCODE_ID, DECODE_ID );
			Id.ncpy  ( __notebook_tab_1.Id, sizeof( __notebook_tab_1.Id ));

			PreEncode   ( __notebook_tab_1.Passw, ' ', ENCODECHAR, sizeof( __notebook_tab_1.Passw ));
			Passw.encode( __notebook_tab_1.Passw, ENCODE_PW, DECODE_PW );
			Passw.ncpy  ( __notebook_tab_1.Passw, sizeof( __notebook_tab_1.Passw ));
		}
		else
		{
			Id.encode( __notebook_tab_1.Id, DECODE_ID, ENCODE_ID );
			Id.ncpy  ( __notebook_tab_1.Id, sizeof( __notebook_tab_1.Id ));
			PreEncode( __notebook_tab_1.Id, ENCODECHAR, ' ', sizeof( __notebook_tab_1.Id ));

			Passw.encode( __notebook_tab_1.Passw, DECODE_PW, ENCODE_PW );
			Passw.ncpy  ( __notebook_tab_1.Passw, sizeof( __notebook_tab_1.Passw ));
			PreEncode   ( __notebook_tab_1.Passw, ENCODECHAR, ' ', sizeof( __notebook_tab_1.Passw ));
		}
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//		TDrvdApp
//                         PreEncode
//    ===============================
//
void TDrvdApp::PreEncode( char* str, char src, char dest, int len )
{
	TAPointer<char> s = new char[len];
	strcpy( s, str );

	memset( str, ENCODECHAR, len );
	strcpy( str, s );

   register int n;
	for ( n = 0; n < len; n++ )
	{
		if ( str[n] == src )
			str[n] = dest;

		if(  str[n] == '\x0' )
			str[n] = ENCODECHAR;
	}
	str[--n] = '\x0';
}

