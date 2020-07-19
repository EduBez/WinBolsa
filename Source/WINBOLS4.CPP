//-------------------------------------------//
//                                           //
//    WINBOLS4. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "winbolsa.h"

#include "qrystkm.h"
#include "querystk.h"


// 	TDrvdDecoratedFrame function definition directory
// 	-------------------------------------------------
//
//	   1)	Cm_GARQ_BOR
//    2) Cm_GARQ_BR
//    3) Cm_GARQ_BRx
//	   4) Cm_GARQ_BRA
//	   5)	Cm_GARQ_BRG
//	   6)	Cm_GARQ_BRI
//	   7)	Cm_GARQ_BFR
//		8) Cm_GARQ_BS
//		9) Cm_GARQ_BSx
//	  10) Cm_GARQ_BSG
//	  11) Cm_GARQ_BSI
//	  12)	Cm_GARQ_BAS
//	  13)	Cm_GARQ_BRJDATA
//	  14)	Cm_GARQ_BSPDATA
//   15) Cm_GARQ_BIG
//   16) Cm_GARQ_BIG_Negociados
//   17) Cm_GARQ_BIG_Especificos
//   18) Cm_GARQ_NEG
//   19) Cm_GARQ_HIS
//   20) Cm_GARQ_IND
//   21) Ce_GARQ
//	  22)	IsAMultRecTable
//	  23)	IsAMultRecQuery
//	  24)	CountMultRec
//	  25) AdjustMultRecFieldLength
//	  26) ExecStockDlg
//	  27)	AssignNewQuery


//--------------------------------------------//
//                  Local Data                //
//--------------------------------------------//

struct tag_MULTREC {

	GARQ_TYPE garq;
	char* s1;
	char* s2;

} MultRecLookupTable [] = {

	{ { GARQBOR1 }, { "!ARQI" }, { "?ARQI" } },
	{ { GARQBOR2 }, { "!ARQB" }, { "?ARQB" } },
	{ { GARQBOR3 }, { "!ARQS" }, { "?ARQS" } },
	{ { GARQBOR4 }, { "!ARQV" }, { "?ARQV" } },
	{ { GARQBFR1 }, { "!ARQI" }, { "?ARQI" } },
	{ { GARQBFR2 }, { "!ARQS" }, { "?ARQS" } },
	{ { GARQBAS1 }, { "!ARQA" }, { "?ARQA" } },
	{ { 0 }, { 0 }, { 0 } }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BOR
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BOR()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
		{
			AssignNewQuery( "GARQBOR\r" );

			if ( OpenCapture() )
				Connect();
		}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                         Cm_GARQ_BR
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BR()
{
	SpeedButtonMenu( CM_GARQ_BR, IDM_GARQ_BR );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BRx
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BRx()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( TQueryStockMAINDlg( this, QueryStockMAIN, GARQBRx, &RQST_Str )
											 .Execute() == IDOK )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BRA
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BRA()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( TQueryStockMAINDlg( this, QueryStockMAIN, GARQBRA, &RQST_Str )
											 .Execute() == IDOK )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BRG
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BRG()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( ExecStockDlg( GARQBR ) )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BRI
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BRI()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
		{
			AssignNewQuery( "GARQBRI\r" );

			if ( OpenCapture() )
				Connect();
		}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BFR
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BFR()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
		{
			int day = 1;

			if ( TQueryStockDays( this, QueryStockDays, &day ).Execute() == IDOK )
			{
				char s[32] = "";
				wsprintf( s, "GARQBFR0%d\r", day );

				AssignNewQuery( s );

				if ( OpenCapture() )
					Connect();
			}
		}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                         Cm_GARQ_BS
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BS()
{
	SpeedButtonMenu( CM_GARQ_BS, IDM_GARQ_BS );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BSx
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BSx()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( TQueryStockMAINDlg( this, QueryStockMAIN, GARQBSx, &RQST_Str )
											 .Execute() == IDOK )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BSG
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BSG()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( ExecStockDlg( GARQBSG ) )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BSI
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BSI()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
		{
			AssignNewQuery( "GARQBSI\r" );

			if ( OpenCapture() )
				Connect();
		}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BAS
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BAS()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
		{
			int day = 1;

			if ( TQueryStockDays( this, QueryStockDays, &day ).Execute() == IDOK )
			{
				char s[32] = "";
				wsprintf( s, "GARQBAS0%d\r", day );

				AssignNewQuery( s );

				if ( OpenCapture() )
					Connect();
			}
		}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                    Cm_GARQ_BRJDATA
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BRJDATA()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
		{
			AssignNewQuery( "GARQBRJDATA\r" );

			if ( OpenCapture() )
				Connect();
		}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                    Cm_GARQ_BSPDATA
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BSPDATA()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
		{
			AssignNewQuery( "GARQBSPDATA\r" );

			if ( OpenCapture() )
				Connect();
		}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_BIG
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BIG()
{
	SpeedButtonMenu( CM_GARQ_BIG, IDM_GARQ_BIG );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//             Cm_GARQ_BIG_Negociados
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BIG_Negociados()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( TQueryStockMAINDlg( this, QueryStockMAIN, GARQBIG, &RQST_Str )
											 .Execute() == IDOK )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//            Cm_GARQ_BIG_Especificos
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_BIG_Especificos()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( ExecStockDlg( GARQBIG ) )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_NEG
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_NEG()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( ExecStockDlg( GARQNEG ) )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_HIS
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_HIS()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( ExecStockDlg( GARQHIS ) )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        Cm_GARQ_IND
//    ===============================
//
void TDrvdDecoratedFrame::Cm_GARQ_IND()
{
	if ( __is_attached || IsValidComm() )
		if ( GetActiveDoc() )
			if ( ExecStockDlg( GARQIND ) )
				if ( OpenCapture() )
					Connect();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                            Ce_GARQ
//    ===============================
//
void TDrvdDecoratedFrame::Ce_GARQ( TCommandEnabler& ce )
{
	// Only when there's no QUERY running
	ce.Enable( !__is_query_running );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                    IsAMultRecTable
//    ===============================
//
int TDrvdDecoratedFrame::IsAMultRecTable()
{
	for ( int i = 0; MultRecLookupTable [i].garq; i++ )
		if ( doc->GetTableType() == MultRecLookupTable [i].garq )
			return i;

	return 0;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                    IsAMultRecQuery
//    ===============================
//
bool TDrvdDecoratedFrame::IsAMultRecQuery()
{
	int i = 0;

	if ( i = IsAMultRecTable() )
		if ( RQST_Buff.contains( MultRecLookupTable [i].s1 ) ||
			  RQST_Buff.contains( MultRecLookupTable [i].s2 ) )
			return true;

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                       CountMultRec
//    ===============================
//
void TDrvdDecoratedFrame::CountMultRec( string& s, long& count )
{
	if ( IsAMultRecTable() )
		if ( s.contains( "ARQH" ) || s.contains( "ARQI" ) ||
			  s.contains( "ARQB" ) || s.contains( "ARQS" ) )
			count++;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//           AdjustMultRecFieldLength
//    ===============================
//
void TDrvdDecoratedFrame::AdjustMultRecFieldLength( string& s )
{
	if ( IsAMultRecTable() )

		if ( s.contains( "ARQH" ) || s.contains( "ARQB" ) ||
			  s.contains( "ARQS" ) || doc->GetTableType() == GARQBAS1 )
		{
			s.remove( s.length() - 1 );
			s = s.strip();
			s.insert( s.length(), '!' );
		}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                       ExecStockDlg
//    ===============================
//
bool TDrvdDecoratedFrame::ExecStockDlg( GARQ_TYPE garq )
{
	if ( TQueryStockDialog( this, QueryStock, garq, &RQST_Str ).Execute() == IDOK )
		return true;

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                     AssignNewQuery
//    ===============================
//
inline void TDrvdDecoratedFrame::AssignNewQuery( const char* s )
{
	for ( int i = 0; i < MAXSTOCKLISTSIZE; i++ )
		RQST_Str[i] = "";

	RQST_Str[0] = s;
}

