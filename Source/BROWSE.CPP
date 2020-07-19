//-------------------------------------------//
//                                           //
//    BROWSE. CPP                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "browse.h"
#include "globals.h"


/////////////////////////////////////
//    TBrowseCtl
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE2( TBrowseCtl, TVbxSpreadSheet, TVbxEventHandler )
	EV_COMMAND(	CM_EDIT_COPY    , CmEditCopy            ),
	EV_COMMAND(	CM_BEGIN        , CmBegin               ),
	EV_COMMAND(	CM_FASTBACKWARD , CmFastBackward        ),
	EV_COMMAND(	CM_BACKWARD     , CmBackward            ),
	EV_COMMAND(	CM_FORWARD      , CmForward             ),
	EV_COMMAND(	CM_FASTFORWARD  , CmFastForward         ),
	EV_COMMAND( CM_END          , CmEnd                 ),
	EV_COMMAND_ENABLE( CM_EDIT_COPY    , CeEditCopy     ),
	EV_COMMAND_ENABLE( CM_BEGIN        , CeBegin        ),
	EV_COMMAND_ENABLE( CM_FASTBACKWARD , CeBegin        ),
	EV_COMMAND_ENABLE( CM_BACKWARD     , CeBackward     ),
	EV_COMMAND_ENABLE( CM_FORWARD      , CeForward      ),
	EV_COMMAND_ENABLE( CM_FASTFORWARD  , CeEnd          ),
	EV_COMMAND_ENABLE( CM_END          , CeEnd          ),
	EV_VBXEVENTINDEX( IDC_GRIDVBX, Event_SpreadSheet_QueryData, EvQueryData ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                        CONSTRUCTOR
//    ===============================
//
TBrowseCtl::TBrowseCtl( Data4* table, TWindow* parent, int id, LPCSTR title,
								int x, int y, int w, int h, long initLen,
								void far* initData, TModule* module )

								: TVbxSpreadSheet( parent, id, title, x, y, w, h )
{
	Init( parent, title, module );
	QryDataFlag = true;

	sREC   = ""  ;
	sField = ""  ;

	DBF = *table;
	DBF.top();

	MAX_RECS = DBF.recCount();
	MAX_COLS = DBF.numFields();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                        SetupWindow
//    ===============================
//
void TBrowseCtl::SetupWindow()
{
	TVbxSpreadSheet::SetupWindow();

	SetPropBorderStyle( BorderStyle_0_None );
	SetPropGridColor( TColor::Black );

	SetPropGridSolid( false );
	SetPropMaxCols( MAX_COLS );

	SetPropProcessTab( true );
	SetPropRowHeight( 12.5, 0 );

	SetPropSelectBlockOptions(6);
	SetPropTabStop( true );

	SetPropVirtualMode( true );
	SetPropVirtualMaxRows( MAX_RECS );

	SetColRow( -1, -1 );      // Select entire GRID
	SetPropBackColor( TColor( // Set Background color
									  GetSysColor( COLOR_WINDOW ) ));

	SetPropLock( true );      // LOCK all CELLS to prevent editing
	SetPropFontName( string( "MS Sans Serif" ));

	SetPropFontSize( 180.0 );
	SetPropFontBold( false );

	Do_Layout();
	SetFocus();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                      UpdateDisplay
//    ===============================
//
void TBrowseCtl::UpdateDisplay()
{
	if ( MAX_RECS == 0L )
	{
		Tag4 tag;
		tag.initFirst( DBF );
		DBF.select( tag );
	}

	DBF.top();

	MAX_RECS    = DBF.recCount();
	QryDataFlag = true;

	SetPropReDraw( false );

	SetColRow( -1, -1 );	 						// Select entire GRID
	SetPropAction( Action_12_ClearText );	// Delete entire GRID

	SetPropVirtualMaxRows( MAX_RECS );		// Adjust number of rows
	SetPropReDraw( true );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                         CmEditCopy
//    ===============================
//
void TBrowseCtl::CmEditCopy()
{
	long col, row;
	string s;
	bool ok = false;

	GetBlockColRow( col, row );
	SetColRow( col, row );

	bool IsBlockSel;
	GetPropIsBlockSelected( IsBlockSel );

	if ( IsBlockSel )
	{
		long col2, row2;

		GetBlockCol2Row2( col2, row2 );
		SetCol2Row2( col2, row2 );

		if ( GetPropClip( s ) )
			ok = true;
	}
	else
		if ( GetPropText( s ) )
			ok = true;

	if ( ok )
	{
		DWORD len = strlen( s.c_str() ) + 1;

		HGLOBAL global = GlobalAlloc( GHND, len );
		LPSTR dest = (LPSTR) GlobalLock( global );

		strcpy( (char*) dest, s.c_str() );
		GlobalUnlock( global );

		TClipboard& clipboard = OpenClipboard();
		clipboard.EmptyClipboard();

		clipboard.SetClipboardData( CF_TEXT, global );
		clipboard.CloseClipboard();

		MessageBox( "Cópia efetuada.\rConteúdo encontra-se no clipboard do windows.",
						"WinBolsa® - Aviso", MB_OK | MB_ICONINFORMATION );
	}
	else
		MessageBox( "Erro ao copiar célula(s) para clipboard do windows",
						"WinBolsa® - Erro", MB_OK | MB_ICONINFORMATION );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                            CmBegin
//    ===============================
//
void TBrowseCtl::CmBegin()
{
	if ( First > 1 )
	{
		long Col;
		GetPropActiveCol( Col );

		SetColRow( Col, 1 );
		SetPropAction( Action_0_ActivateCell );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                     CmFastBackward
//    ===============================
//
void TBrowseCtl::CmFastBackward()
{
	if ( First > 1 )
	{
		long Col, Row;

		GetPropActiveCol( Col );
		GetPropTopRow( Row );

		Row = Row - ( Last - First ) < 1 ? 1 : Row - ( Last - First );

		SetColRow( Col, Row );
		SetPropAction( Action_0_ActivateCell );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                         CmBackward
//    ===============================
//
void TBrowseCtl::CmBackward()
{
	long Col,
		  Row;

	GetPropActiveCol( Col );
	GetPropActiveRow( Row );

	SetColRow( Col, Row > 1 ? --Row : Row );
	SetPropAction( Action_0_ActivateCell );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                          CmForward
//    ===============================
//
void TBrowseCtl::CmForward()
{
	long Col,
		  Row;

	GetPropActiveCol( Col );
	GetPropActiveRow( Row );

	SetColRow( Col, Row < MAX_RECS ? ++Row : Row );
	SetPropAction( Action_0_ActivateCell );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                      CmFastForward
//    ===============================
//
void TBrowseCtl::CmFastForward()
{
	if ( Last < MAX_RECS )
	{
		long Col,
			  Row,
			  RowsPerPage;

		RowsPerPage = Last - First;
		GetPropActiveCol( Col );

		if ( Last + RowsPerPage > MAX_RECS )
		{
			SetPropTopRow( MAX_RECS - RowsPerPage );
			SetPropRow( MAX_RECS );
		}

		else
		{
			GetPropTopRow( Row );
			SetPropTopRow( Row + RowsPerPage );
		}

		SetPropCol( Col );
		SetPropAction( Action_0_ActivateCell );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                              CmEnd
//    ===============================
//
void TBrowseCtl::CmEnd()
{
	if ( Last < MAX_RECS )
	{
		long Col,
			  RowsPerPage;

		RowsPerPage = Last - First;
		GetPropActiveCol( Col );

		SetPropTopRow( MAX_RECS - RowsPerPage );
		SetColRow( Col, MAX_RECS );

		SetPropAction( Action_0_ActivateCell );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                         CeEditCopy
//    ===============================
//
void TBrowseCtl::CeEditCopy( TCommandEnabler& ce )
{
	ce.Enable( MAX_RECS );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                            CeBegin
//    ===============================
//
void TBrowseCtl::CeBegin( TCommandEnabler& ce )
{
	ce.Enable( MAX_RECS && ( First > 1 ));
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                         CeBackward
//    ===============================
//
void TBrowseCtl::CeBackward( TCommandEnabler& ce )
{
	long Row; GetPropActiveRow( Row );
	ce.Enable( MAX_RECS && ( Row > 1 ));
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                          CeForward
//    ===============================
//
void TBrowseCtl::CeForward( TCommandEnabler& ce )
{
	long Row; GetPropActiveRow( Row );
	ce.Enable( MAX_RECS && ( Row < MAX_RECS ));
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                              CeEnd
//    ===============================
//
void TBrowseCtl::CeEnd( TCommandEnabler& ce )
{
	ce.Enable( MAX_RECS && ( Last < MAX_RECS ));
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                        EvQueryData
//    ===============================
//
void TBrowseCtl::EvQueryData( VBXEVENT FAR* event )
{
	long Row        = VBX_EVENTARGNUM( event, long , 0 );
	long RowsNeeded = VBX_EVENTARGNUM( event, long , 1 );

	DataLoad( Row, RowsNeeded );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                           DataLoad
//    ===============================
//
void TBrowseCtl::DataLoad( long Row, long RowsNeeded )
{
	if ( QryDataFlag )	// Happens only at the
	{                    // first QUERY DATA event
		QryDataFlag = false;
		SetGridRange( Row, RowsNeeded );
	}

	else
	{
		if ( Row == First )
		{
			// WINDOW Grow
			if ( RowsNeeded > Last - First + 1 )
			{
				long Ll = Last;
				long Rn = RowsNeeded - ( Last - First ) + 1;

				GoRec( Last );
				SetGridRange( Row, RowsNeeded );

				Row = Ll; RowsNeeded = Rn;
			}

			// WINDOW Shrink
			else if ( RowsNeeded < Last - First + 1 )
			{
				GoRec( First );
				DBF.skip( RowsNeeded );

				SetGridRange( Row, RowsNeeded );
				return;
			}
			
			// Columm Scroll
			else
				return;
		}

		// Forward
		else if ( Row == First - 1 )
		{                                      
			GoRec( First );
			DBF.skip( -1L );

			SetGridRange( Row, RowsNeeded - 1 );
			Row = First; RowsNeeded = 1;
		}

		// Backward
		else if ( Row == First + 1 )
		{
			GoRec( First );
			DBF.skip( RowsNeeded );

			SetGridRange( Row, RowsNeeded );
			Row = Last; RowsNeeded = 1;
		}

		// Fast Forward
		else if ( Row == Last )
		{
			GoRec( Last );
			SetGridRange( Row, RowsNeeded );
		}

		// Fast Backward, TOP or BOTTOM
		else if ( Row < First || Row > Last )
		{
			if ( Row < First )
			{
				if ( Row == 1 )							// Go TOP ( begin )
					DBF.top();

				else
				{
					GoRec( First );
					DBF.skip( -( First - Row ) );
				}
			}

			else if ( Row > Last )
			{
				if ( Row + RowsNeeded > MAX_RECS )	// Go BOTTOM ( end )
				{
					DBF.bottom();
					DBF.skip( -RowsNeeded + 1 );
				}

				else
				{
					GoRec( Last );
					DBF.skip( Row - Last );
				}
			}

			SetGridRange( Row, RowsNeeded );
		}

		else if ( Row > First && Row < Last )
		{
			GoRec( Row );
			SetGridRange( Row, RowsNeeded );
		}
	}

	sREC = "";
	for ( register long r = 0; r < RowsNeeded; r++ )
	{
		ltoa( DBF.recNo(), sbuff, 10 );

		recNo = sbuff;
		sREC += recNo + __tab;

		for ( register long c = 1; c <= MAX_COLS; c++ )
		{
			field.init( DBF, (int)c );

			if ( field.type() == 'M' )
				sField = "Memo";
			else
				sField = field.str();

			if ( sField.is_null() )
				sREC += " " + __tab;
			else
			{
				if ( field.type() == 'N' )
				{
					size_t pos = sField.find( '.' );

					if ( pos != NPOS )
						sField.replace( pos, 1, ',' );

					sREC += sField + __tab;
				}

				else if ( field.type() == 'D' )
					sREC  += sField.substr( 6, 2 ) + __slash +
								sField.substr( 4, 2 ) + __slash +
								sField.substr( 2, 2 ) + __tab;
				else
					sREC += sField + __tab;
			}
		}

		sREC += '\r';
		DBF.skip();
	}

	SetColRow( 0, Row ); SetCol2Row2( MAX_COLS, Row + RowsNeeded - 1 );
	SetPropClip( sREC );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                          Do_Layout
//    ===============================
//
void TBrowseCtl::Do_Layout()
{
	SetColRow( 0, 0 );            // Select top left corner
	SetPropCellType( CellType_5_StaticText );

	SetPropTypeHAlign( TypeHAlign_2_Center );
	SetPropTypeTextAlignVert( TypeTextAlignVert_1_Center );

	SetPropTypeTextShadow( true );
	SetPropText( string( "Reg" ));

	SetColRow( 0, -1 );           // Select row header

	if ( MAX_RECS > 999L )
		SetPropColWidth( 5.5, 0 );

	SetPropFontBold( true );
	SetPropTypeHAlign( TypeHAlign_0_Left );

	#if 0
		SetColRow( 1, -1 );        // Select first column
		SetPropColHidden( true );  // Hide it from user
	#endif

	for ( int n = 1; n <= DBF.numFields(); n++ )
	{
		field.init( DBF, n );
		SetColRow( n, 0 );         // Select column header

		SetPropFontBold( true );
		SetPropText( string( field.name() ));

		SetColRow( n, -1 );        // Select entire column

		if ( field.type() == 'M' )
			SetPropColWidth( strlen( field.name() ) + 2, n );
		else
			SetPropColWidth( max( strlen( field.name() ), field.len() ) + 2, n );

		#if 0
			if ( field.type() == 'N' )
			{
				SetPropCellType( CellType_2_Float );
				SetPropTypeFloatMax( string( "9", field.len()-( field.decimals() + 1 )));

				SetPropTypeFloatDecimalPlaces( field.decimals() );
				SetPropTypeFloatSeparator( true );
			}
		#endif
	}

	SetColRow( 1, 1 );
	SetPropAction( Action_0_ActivateCell );
	SetPropLeftCol(1);
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TBrowseCtl
//                              GoRec
//    ===============================
//
void TBrowseCtl::GoRec( long Row )
{
	GetText( 0, Row, sREC );
	DBF.go( atol( sREC.c_str() ));
}

