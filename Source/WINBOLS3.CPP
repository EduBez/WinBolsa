//-------------------------------------------//
//                                           //
//    WINBOLS3. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "winbolsa.h"


// 	TDrvdDecoratedFrame function definition directory
// 	-------------------------------------------------
//
//    1) EvInitializeComm
//		2) EvCommNotify
//	   3) Request
//		4) AppendFromCapture
//	   5) InsertRec
//	   6) XtractRec
//		7) XtractTot


/////////////////////////////////////
//    TDrvdDecoratedFrame
//                   EvInitializeComm
//    ===============================
//
LRESULT TDrvdDecoratedFrame::EvInitializeComm( WPARAM wParam, LPARAM lParam )
{
	TRect rc = GetClientRect();
	rc.bottom /= 2;

	__terminal = new TMDIChildTerminal( *GetClientWindow(), "Terminal" );
	__terminal->Create();

	__terminal->MoveWindow( rc );
	__terminal->SetFocus();

	__status_bar->SetText( "Inicializando Modem..." );
	Invalidate(); UpdateWindow();

	__comm = new TComm( this, -1, "", 0, 0, 0, 0 );
	__comm->Create();

	return (LRESULT)0;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//
//    ===============================
//
void TDrvdDecoratedFrame::EvCommNotify( uint CommId, uint Notify )
{
	::GetCommError( CommId, &comstat );
	__rx_gauge->SetValue( comstat.cbInQue );

	if ( Notify == CN_RECEIVE  )
	{
		__comm->GetPropReceive( scrap );
		__capture << scrap;       // Everything must be writen to capture file

		RQST_Buff += scrap;       // Stack data on REQUEST buffer
		*__terminal << scrap;     // Show data in the Terminal Window

		if ( RQST_Buff.length() >= 512 ) // Resize at 512 bytes and keep the last 80 bytes
			RQST_Buff.substr( RQST_Buff.length() - 80 );

		if ( IsAMultRecQuery() )  // Handle queries with diferent kinds of records
			CmStockHangUp();       // Disconect modem

		if ( RQST_Buff.contains( "TEMPO" ) )
		{
			CmStockHangUp();
			::MessageBox( 0, "Tempo esgotado. Conexão desfeita", "WinBolsa® - Aviso",
							  MB_OK | MB_ICONEXCLAMATION );
		}

		if ( RQST_Buff.contains( "\r\n:" ) )
		{                         // Received command prompt from host
			RQST_Buff = "";        // Clear request buffer
			Request();             // Make another request
		}
	}

	if ( Notify == CN_EVENT )
		uint mask = ::GetCommEventMask( CommId, 0xFFFF );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                            Request
//    ===============================
//
void TDrvdDecoratedFrame::Request()
{
	if ( RQST_Str[ StkLstIndex ].is_null() || StkLstIndex == MAXSTOCKLISTSIZE )
	{
		ClearQuery();         // When there's no more requests
		AppendFromCapture();  // Append records from the capture file
	}
	else                     // Else ask for data now
	{
		__comm->SetPropSend( RQST_Str[ StkLstIndex ] );
		StkLstIndex < MAXSTOCKLISTSIZE ? StkLstIndex++ : StkLstIndex = MAXSTOCKLISTSIZE;
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                  AppendFromCapture
//    ===============================
//
void TDrvdDecoratedFrame::AppendFromCapture()
{
	::SetCursor( ::LoadCursor( 0, IDC_WAIT ));
	filebuf* ofs = __capture.rdbuf();

	if ( ofs->is_open() )
	{
		// Close Capture File and flush contents
		__capture.close();

		// Capture File will be rewriten with 80 cols in a file named 'CAPTURE'
		string BOFS80C = __capture_path.substr( 0, __capture_path.find( ".TXT" ));

		ifstream bifs( __capture_path.c_str(), ios::in | ios::binary );
		ofstream bofs( BOFS80C    .c_str(), ios::in | ios::binary );

		if ( bifs && bofs )
			while ( !bifs.eof() )
			{
				char s[ MAXLEN_LINE + 1 ] = "";
				bifs.read ( s, sizeof(s) );

				bofs.write( s, sizeof(s) );
				bofs << '\r'; bofs << '\n';
			}

		bifs.close();
		bofs.close();

		bifs.open( BOFS80C.c_str(), ios::in | ios::binary );

		if ( bifs )
		{
			string line = "";
			long rec = 0L, tot = 0L, cnt = 0L;

			while ( !bifs.eof() )
			{
				char v[ MAXLEN_LINE + 3 ] = "";
				bifs.getline( v, sizeof(v) );

				v[ strlen(v) - 1 ] = '\x0';
				line += v;

				if ( line.contains( "ARQ" ) )
					if ( line.contains('?') || line.contains('!') )
						XtractRec( line, rec, cnt );

				if ( line.contains( "TOT" ) )
					XtractTot( line, tot );
			}

			bifs.close();
			remove( __capture_path.c_str() );
			remove( BOFS80C .c_str() );

			if ( rec )
			{
				doc->UpdateView();
				char s[ 128 ] = "";

				if ( tot ) {
					if ( cnt )
						tot -= cnt;
					wsprintf( s, "Registros acusados de envio pelo Disque-Bolsa : %6ld\rTotal de registros válidos recebidos : %6ld\r", tot, rec );
				}
				else
					wsprintf( s, "Total de registros válidos recebidos : %6ld\r", rec );

				MessageBox( s, "WinBolsa® - Aviso", MB_OK | MB_ICONEXCLAMATION );
			}
		}
		else
			MessageBox( "Erro ao ler Arquivo de Transporte", "WinBolsa® - Erro Fatal",
							 MB_OK | MB_ICONEXCLAMATION );
	}

	::SetCursor( ::LoadCursor( 0, IDC_ARROW ));
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                          InsertRec
//    ===============================
//
void TDrvdDecoratedFrame::InsertRec( string& line, long& rec, long& cnt,
												 size_t A, size_t B )
{
	string v = line.substr( A, B );
	size_t k = v.find('?');

	if ( k == NPOS )
		k = v.find('!');

	if ( k != NPOS ) {
		v = v.substr( 0, k + 1 );

		v.prepend( "/." );					// Some formating required for the
		v.put_at( v.length() - 1, '!' );	// document 'AppendData' function

		CountMultRec( v, cnt );          // Count for diferent record ocurrences
		AdjustMultRecFieldLength( v );   // Adjust field length for some queries

		if ( doc->AppendData( v ) )
			rec++;
	}
	line = line.substr( B );				// Truncate line buffer
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                          XtractRec
//    ===============================
//
void TDrvdDecoratedFrame::XtractRec( string& line, long& rec, long& cnt )
{
	while ( true ) {
		size_t pos;
		size_t A = line.find( "ARQ" );
		size_t B = line.find( "ARQ", A + 1 );

		if ( B == NPOS ) {
			pos = line.find('?');

			if ( pos == NPOS ) {
				pos = line.find('!');

				if ( pos == NPOS )
					break;
			}
			InsertRec( line, rec, cnt, A, pos + 1 );
			break;
		}
		InsertRec( line, rec, cnt, A, B );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                          XtractTot
//    ===============================
//
void TDrvdDecoratedFrame::XtractTot( string& line, long& tot )
{
	size_t k = line.find( "TOT" );
	size_t p = line.find_last_of( '&' );

	if ( p - k == 16 )
	{
		int  n   = 0;
		bool r   = true;
		string s = line.substr( k + 3, 5 );

		while ( n < 5 )
			if ( !isdigit( s[ n++ ] ) )
			{
				r = false;
				break;
			}

		if ( r )
			tot += atoi( s.c_str() );
		else
			tot += 0;

		line = line.substr( p );
	}
}

