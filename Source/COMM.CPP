//-------------------------------------------//
//                                           //
//    COMM. CPP                              //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include <io.h>

#include "comm.h"
#include "globals.h"


//--------------------------------------------//
//                 Local Data                 //
//--------------------------------------------//

static LPCSTR Speed    = "Speed"     ;
static LPCSTR Parity   = "Parity"    ;
static LPCSTR DataBits = "DataBits"  ;
static LPCSTR StopBits = "StopBits"  ;
static LPCSTR XonXoff  = "XonXoff"   ;
static LPCSTR CtsRts   = "CtsRts"    ;
static LPCSTR COM1     = "COM1"      ;
static LPCSTR COM2     = "COM2"      ;
static LPCSTR COM3     = "COM3"      ;
static LPCSTR COM4     = "COM4"      ;

static struct {
	LPCSTR Prop;
	int Value;
	int ID;

} MdmLookupTable[] = {
	{ DataBits, 5,   7   /* ID_Data5       */ },
	{ DataBits, 6,   8   /* ID_Data6       */ },
	{ DataBits, 7,   9   /* ID_Data7       */ },
	{ DataBits, 8,   10  /* ID_Data8       */ },

	{ Parity,   0,   14  /* ID_ParityNone  */ },
	{ Parity,   2,   15  /* ID_ParityOdd   */ },
	{ Parity,   1,   16  /* ID_ParityEven  */ },
	{ Parity,   3,   17  /* ID_ParityMark  */ },
	{ Parity,   4,   18  /* ID_ParitySpace */ },

	{ StopBits, 1,   11  /* ID_Stop1       */ },
	{ StopBits, 0,   12  /* ID_Stop15      */ },
	{ StopBits, 2,   13  /* ID_Stop2       */ },

	{ Speed,   300,  0   /* ID_Baud300     */ },
	{ Speed,   600,  1   /* ID_Baud600     */ },
	{ Speed,  1200,  2   /* ID_Baud1200    */ },
	{ Speed,  2400,  3   /* ID_Baud2400    */ },
	{ Speed,  4800,  4   /* ID_Baud4800    */ },
	{ Speed,  9600,  5   /* ID_Baud9600    */ },
	{ Speed, 19200,  6   /* ID_Baud19200   */ },

	{ 0, 0, 0 }
};

static struct {
	LPCSTR Value;
	int ID;

} CommLookupTable[] = {
	{ COM1, 22 },
	{ COM2, 23 },
	{ COM3, 24 },
	{ COM4, 25 },
	{ 0, 0 }
};

static LPCSTR Mdm[] = { Speed  , Parity, DataBits, StopBits,
								XonXoff, CtsRts, 0 };


/////////////////////////////////////
//    TComm
//                        SetupWindow
//    ===============================
//
void TComm::SetupWindow()
{
	TVbxsaxComm::SetupWindow();

	SetPropAutoReceive( false );
	SetPropAutoSend( false );

	SetPropMaxReceiveLen( -1 );
	ReadIniPrivateFile();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                         GetPropAll
//    ===============================
//
void TComm::GetPropAll( unsigned int (*TBuff)[] )
{
	int i = 0;
	string port;
	GetPropPort( port );

	if ( port.is_null() )
	{
		// Serial Port is in NONE
		if ( IniCommPort.is_null() )
			*( *TBuff + 26 ) = 1;
		// Serial Port is not available
		else
		{
			if ( IniCommPort == "COM1" ) *( *TBuff + 22 ) = 1;
			if ( IniCommPort == "COM2" ) *( *TBuff + 23 ) = 1;
			if ( IniCommPort == "COM3" ) *( *TBuff + 24 ) = 1;
			if ( IniCommPort == "COM4" ) *( *TBuff + 25 ) = 1;
		}
	}
	else
		while( CommLookupTable[i].Value )
			if ( port == CommLookupTable[i].Value )
			{
				*( *TBuff + CommLookupTable[i].ID ) = 1;
				break;
			}
			else
				i++;

	int d;
	GetPropDataBits( d );
	for ( i = 0; i <= 3; i++ )
		if ( MdmLookupTable[i].Value == d ) {
			*( *TBuff + MdmLookupTable[i].ID ) = 1; break;
		}

	unsigned char p;
	GetPropParity( p );
	for ( i = 4; i <= 8; i++ )
		if ( MdmLookupTable[i].Value == p ) {
			*( *TBuff + MdmLookupTable[i].ID ) = 1; break;
		}

	int sb;
	GetPropStopBits( sb );
	for ( i = 9; i <= 11; i++ )
		if ( MdmLookupTable[i].Value == sb ) {
			*( *TBuff + MdmLookupTable[i].ID ) = 1; break;
		}

	long s;
	GetPropSpeed( s );
	for ( i = 12; i <= 18; i++ )
		if ( MdmLookupTable[i].Value == s ) {
			*( *TBuff + MdmLookupTable[i].ID ) = 1; break;
		}

	BOOL c;  GetPropCtsRts( c );   *( *TBuff + 19 ) = c  ? 1 : 0;
	BOOL xo; GetPropXonXoff( xo ); *( *TBuff + 20 ) = xo ? 1 : 0;

	if ( !c && !xo ) *( *TBuff + 21 ) = 1;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                         SetPropAll
//    ===============================
//

void TComm::SetPropAll( unsigned int TBuff[] )
{
	for ( int i = 22 /* ID_Com1 */ ; i <= 26 /* ID_ComNone */ ; ++i )
	{
		if ( TBuff[ i ] )
		{
			memset( sbuff, '\x0', sizeof( sbuff ));
			if ( i != 26 /* ID_ComNone */ )
				wsprintf( sbuff, "COM%d", (i-22)+1 );
			break;
		}
	}

	IsValidPort( string( sbuff ));

	for ( int i = 0; MdmLookupTable[i].Prop; ++i )
		if ( TBuff[ MdmLookupTable[i].ID ] )
			SetProp( MdmLookupTable[i].Prop, MdmLookupTable[i].Value );

	SetPropCtsRts(  TBuff[ 19 ] /* ID_FlowHardware */ ? true : false );
	SetPropXonXoff( TBuff[ 20 ] /* ID_FlowXonXoff  */ ? true : false );

	SetDescription();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                        IsValidPort
//    ===============================
//
bool TComm::IsValidPort( string& Port )
{
	IniCommPort = Port;	// Save comm port for the ini file
	CommId      = -1;		// Save comm device ID

	for ( int i = 0; CommLookupTable[i].Value; i++ )
		if ( Port == CommLookupTable[i].Value )
		{
			CommId = CommLookupTable[i].ID - 22;
			break;
		}

	string scrap, v;

	SetPropPort( Port );
	GetPropPort( scrap );

	// Test for Port existence
	if ( scrap.is_null() )
	{
		if ( IniCommPort.is_null() )
			v = "COM n.s - não selecionada";
		else
			v = Port + " - não instalada";

		__is_valid_comm = false;
		__status_bar->SetText( v.c_str() );

		return false;
	}

	if ( Initialize( scrap ) )
	{
		// All COMM events must be monitorized
		::SetCommEventMask( CommId, 0xFFFF );

		v = Port + " - OK, inicializada";
		__status_bar->SetText( v.c_str() );

		__is_valid_comm = true;
		return true;
	}

   v = Port + " - erro na inicialização";

	if ( scrap.is_null() )
		v = Port + " - não responde";

	__status_bar->SetText( v.c_str() );
	__is_valid_comm = false;

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                     SetDescription
//    ===============================
//
void TComm::SetDescription()
{
	int  j = 0;
   #ifdef BC_5x
   int i = 0;
   #else
	long i = 0;
   #endif
	string scrap;
	memset( sbuff, '\x0', sizeof( sbuff ));

	while ( Mdm[j] )
	{
		GetProp( Mdm[j], i );
		if ( j == 1 /* Parity */ )
		{
			switch ((unsigned char)i)
			{
				case 0 : scrap += "N"; break;
				case 1 : scrap += "P"; break;
				case 2 : scrap += "I"; break;
				case 3 : scrap += "M"; break;
				case 4 : scrap += "E"; break;
			}
		}
		else if ( j == 3 /* StopBits */ )
		{
			switch (i)
			{
				case 0 : scrap += "1.5"; break;
				case 1 : scrap += "1";   break;
				case 2 : scrap += "2";   break;
			}
		}
		else if ( j < 4 /* Skip XonXoff & CtsRts */ )
		{
         #ifdef BC_5x
			itoa( abs(i), sbuff, 10 );
         #else
			ltoa( labs(i), sbuff, 10 );
         #endif
			scrap += sbuff + string( " " );
		}
		j++;
	}

	__status_bar_slot_1->SetText( scrap.c_str() );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                              Delay
//    ===============================
//
void TComm::Delay( unsigned long n )
{
	::SetCursor( ::LoadCursor( 0, IDC_WAIT ));

	for ( DWORD t = ( n * 1000L ) + GetTickCount(); GetTickCount() <= t; )
		::WaitMessage();

	::SetCursor( ::LoadCursor( 0, IDC_ARROW ));
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                         Initialize
//    ===============================
//
bool TComm::Initialize( string& v )
{
	string DialSignal     = __notebook_tab_2.Signal;
	string Initialization = __notebook_tab_3.InitString;
	string TimeOut        = __notebook_tab_3.TimeoutTime;

	if ( TimeOut.is_null() )
		Initialization += "S7=45";
	else
		Initialization += "S7=" + string( TimeOut );

	if ( DialSignal.is_null() )
		Initialization += "X4";
	else
		Initialization += "X3S6=" + string( DialSignal ) + string( '\r' );

	if ( Initialization.contains( "AT" ))         // Must contain 'AT' COMMAND in
	{                                             // the begining of the string
		if ( Initialization.find( "AT" ))
			Initialization.prepend( "AT" );         // Add one if don't
	}
	else
		Initialization.prepend( "AT" );

	Initialization += '\r';

	if ( SendATCommand( "ATZ\r" ) )               // Reset modem
		if ( SendATCommand( Initialization, &v ) ) // Send initialization string
			return true;

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                            DropDTR
//    ===============================
//
void TComm::DropDTR()
{
	::EscapeCommFunction( CommId, CLRDTR );
	Delay( 2L );
	::EscapeCommFunction( CommId, SETDTR );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                      SendATCommand
//    ===============================
//
bool TComm::SendATCommand( string command, string* result )
{
	SetPropSend( command );
	Delay( 2L );

	string v;
	GetPropReceive( v );

	if ( result )
		*result = v;

	if ( v.contains( "OK" ) )
		return true;

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                             HangUp
//    ===============================
//
bool TComm::HangUp()
{
	bool ret = false;

	do {
		DropDTR();                     // Drop 'Data Terminal Ready' line
												 // Send AT command
		if ( SendATCommand( string( "AT\r" )) ) {
			ret = true;
			break;
		}

		SetPropSend( string( "+++" )); // Switch modem to command mode
		Delay( 2L );                   // Wait 1.25 seconds

		if ( SendATCommand( string( "ATH0\r" )) ) {
			ret = true;
			break;
		}
	} while ( ::GetCommError( CommId, &comstat ) );

	return ret;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                             RxUsed
//    ===============================
//
uint TComm::RxUsed()
{
	::GetCommError( CommId, &comstat );
	return comstat.cbInQue;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                 ReadIniPrivateFile
//    ===============================
//
void TComm::ReadIniPrivateFile()
{
	memset( sbuff, '\x0', sizeof( sbuff ));
	if ( access( __ini_file_name.c_str(), 0 ) == 0 )
	{
		GetPrivateProfileString( "Modem", "Port", "", sbuff, sizeof(sbuff), __ini_file_name.c_str() );
		int j = 0;
		while ( Mdm[j] )
		{
			SetProp( Mdm[j], (int)GetPrivateProfileInt( "Modem", Mdm[j], 0, __ini_file_name.c_str() ));
			j++;
		}
	}
	else
	{
		__is_dirty = true;
		SetPropSpeed( 1200L );	// Speed  - 1200
		SetPropParity(1);			// Parity - Even
		SetPropDataBits(7);		// Data   - 7
		SetPropStopBits(1);		// Stop   - 1
		SetPropXonXoff(1);		// Flow   - XonXoff
	}

	IsValidPort( string( sbuff ) );
	SetDescription();          // Display Status Bar information
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TComm
//                WriteIniPrivateFile
//    ===============================
//
void TComm::WriteIniPrivateFile()
{
	if ( __is_dirty )
	{
		WritePrivateProfileString( "Modem", "Port", IniCommPort.c_str(), __ini_file_name.c_str() );
		int  j = 0;
      #ifdef BC_5x
      int i = 0;
      #else
      long i = 0;
      #endif
		memset( sbuff, '\x0', sizeof( sbuff ));

		while ( Mdm[j] )
		{
			GetProp( Mdm[j], i );
 			if ( ( j == 4 /*XonXoff*/ || j == 5 /*CtsRts*/ ) && i != 0 ) i = 1;
         #ifdef BC_5x
			itoa( abs(i), sbuff, 10 );
         #else
			ltoa( labs(i), sbuff, 10 );
         #endif
			WritePrivateProfileString( "Modem", Mdm[j++], sbuff, __ini_file_name.c_str() );
		}
	}
}

