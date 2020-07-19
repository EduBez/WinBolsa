//-------------------------------------------//
//                                           //
//    WINBOLS2. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "winbolsa.h"
#include "about.h"
#include "dial.h"


// 	TDrvdDecoratedFrame function definition directory
// 	-------------------------------------------------
//
// 	1) RESPONSE_TABLE
//    2) CONSTRUCTOR
//    3) SetupWindow
//		4) CanClose
//    5) VCRShow
//		6) EvMove
//		7) EvSize
//		8) CmEditCopy
//    9) CmVCR
//   10) CmStockDial
//   11) CeStockDial
//   12) CmStockHangUp
//	  13) CmFilePrint
//	  14) CeFilePrint
//	  15) CmFilePrinterSetup
//	  16) CmAbout
//	  17) GetActiveDoc
//	  18) IsValidComm
//	  19) OpenCapture
//	  20) Connect
//	  21)	PostRequest
//	  22) SpeedButtonMenu
//	  23)	CmHelpIndex
//	  24)	CmHelpHelp


/////////////////////////////////////
//    TDrvdDecoratedFrame
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TDrvdDecoratedFrame, TDecoratedMDIFrame )
	EV_WM_MOVE,
	EV_WM_SIZE,
	EV_WM_TIMER,
	EV_WM_COMMNOTIFY,
	EV_MESSAGE( WM_INITIALIZECOMM      , EvInitializeComm   ),
	EV_COMMAND(	CM_FILEPRINT           , CmFilePrint        ),
	EV_COMMAND( CM_FILEPRINTERSETUP    , CmFilePrinterSetup ),
	EV_COMMAND(	CM_STOCKDIAL           , CmStockDial        ),
	EV_COMMAND(	CM_STOCKHANGUP         , CmStockHangUp      ),
	EV_COMMAND( CM_HELPINDEX           , CmHelpIndex        ),
	EV_COMMAND( CM_HELPHELP            , CmHelpHelp         ),
	EV_COMMAND(	CM_ABOUT               , CmAbout            ),
	EV_COMMAND(	CM_GARQ_BOR_1          , Cm_GARQ_BOR        ),
	EV_COMMAND(	CM_GARQ_BOR_2          , Cm_GARQ_BOR        ),
	EV_COMMAND(	CM_GARQ_BOR_3          , Cm_GARQ_BOR        ),
	EV_COMMAND(	CM_GARQ_BOR_4          , Cm_GARQ_BOR        ),
	EV_COMMAND(	CM_GARQ_BOR_5          , Cm_GARQ_BOR        ),
	EV_COMMAND(	CM_GARQ_BR             , Cm_GARQ_BR         ),
	EV_COMMAND(	CM_GARQ_BRx            , Cm_GARQ_BRx        ),
	EV_COMMAND(	CM_GARQ_BRA            , Cm_GARQ_BRA        ),
	EV_COMMAND(	CM_GARQ_BRG            , Cm_GARQ_BRG        ),
	EV_COMMAND(	CM_GARQ_BRI            , Cm_GARQ_BRI        ),
	EV_COMMAND(	CM_GARQ_BFR_1          , Cm_GARQ_BFR        ),
	EV_COMMAND(	CM_GARQ_BFR_2          , Cm_GARQ_BFR        ),
	EV_COMMAND(	CM_GARQ_BFR_3          , Cm_GARQ_BFR        ),
	EV_COMMAND(	CM_GARQ_BS             , Cm_GARQ_BS         ),
	EV_COMMAND(	CM_GARQ_BSx            , Cm_GARQ_BSx        ),
	EV_COMMAND(	CM_GARQ_BSG            , Cm_GARQ_BSG        ),
	EV_COMMAND(	CM_GARQ_BSI            , Cm_GARQ_BSI        ),
	EV_COMMAND(	CM_GARQ_BAS_1          , Cm_GARQ_BAS        ),
	EV_COMMAND(	CM_GARQ_BAS_2          , Cm_GARQ_BAS        ),
	EV_COMMAND(	CM_GARQ_BRJDATA        , Cm_GARQ_BRJDATA    ),
	EV_COMMAND(	CM_GARQ_BSPDATA        , Cm_GARQ_BSPDATA    ),
	EV_COMMAND(	CM_GARQ_BIG            , Cm_GARQ_BIG        ),
	EV_COMMAND( CM_GARQ_BIG_NEGOCIADOS , Cm_GARQ_BIG_Negociados  ),
	EV_COMMAND( CM_GARQ_BIG_ESPECIFICOS, Cm_GARQ_BIG_Especificos ),
	EV_COMMAND(	CM_GARQ_NEG            , Cm_GARQ_NEG        ),
	EV_COMMAND(	CM_GARQ_HIS            , Cm_GARQ_HIS        ),
	EV_COMMAND(	CM_GARQ_IND            , Cm_GARQ_IND        ),
	EV_COMMAND_ENABLE( CM_FILEPRINT    , CeFilePrint        ),
	EV_COMMAND_ENABLE( CM_STOCKDIAL    , CeStockDial        ),
	EV_COMMAND_ENABLE( CM_GARQ_BOR_1   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BOR_2   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BOR_3   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BOR_4   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BOR_5   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BRx     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BRA     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BRG     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BRI     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BFR_1   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BFR_2   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BFR_3   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BS      , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BSx     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BSG     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BSI     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BAS_1   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BAS_2   , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BRJDATA , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BSPDATA , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_BIG_NEGOCIADOS , Ce_GARQ     ),
	EV_COMMAND_ENABLE( CM_GARQ_BIG_ESPECIFICOS, Ce_GARQ     ),
	EV_COMMAND_ENABLE( CM_GARQ_NEG     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_HIS     , Ce_GARQ            ),
	EV_COMMAND_ENABLE( CM_GARQ_IND     , Ce_GARQ            ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        CONSTRUCTOR
//    ===============================
//
TDrvdDecoratedFrame::TDrvdDecoratedFrame( const char far* title, TResId menuResId,
														TMDIClient& clientWnd, bool trackMenuSelection,
														TModule* module )

							: TDecoratedMDIFrame ( title, menuResId, clientWnd,
														  trackMenuSelection, module )
{
	Init( 0, false );
	doc = 0;	// 'protected:' data pointer to current active document

	__capture_path = __ini_file_name.substr( 0, __ini_file_name.
						  find( "WINBOLSA.INI" )) + "CAPTURE.TXT";

	__tool_bar     = new TCtrlBar( this );
	__status_bar   = new TStatusBar( this, TGadget::Recessed );

	__status_bar_slot_1 = new TTextGadget( IDG_SLOT1, TTextGadget::Recessed,
														TTextGadget::Center, 7 );

	__status_bar_slot_2 = new TTextGadget( IDG_SLOT2, TTextGadget::Recessed,
														TTextGadget::Center, 12, "DESCONECTADO" );

	__clock    = new TClock( this, -1, 0, 65, 23 );
	__rx_gauge = new TGauge( this, "rx: %d", -1, 0, 2, 67, 23 );

	__speed_button_1 = new TFlyByTIPButton( CM_STOCKDIAL,   CM_STOCKDIAL   );
	__speed_button_2 = new TFlyByTIPButton( CM_STOCKHANGUP, CM_STOCKHANGUP );
	__speed_button_3 = new TFlyByTIPButton( CM_CONFIG,      CM_CONFIG      );

	__tool_bar->Insert( *new TFlyByTIPButton( CM_FILENEW,   CM_FILENEW,
															TButtonGadget::NonExclusive ) );

	__tool_bar->Insert( *new TFlyByTIPButton( CM_FILEOPEN,  CM_FILEOPEN   ) );
	__tool_bar->Insert( *new TFlyByTIPButton( CM_FILESAVE,  CM_FILESAVE   ) );

	__tool_bar->Insert( *new TSeparatorGadget( 12 ));
	__tool_bar->Insert( *new TFlyByTIPButton( CM_EDIT_COPY, CM_EDIT_COPY  ) );

	#if 0
		__tool_bar->Insert( *new TSeparatorGadget( 12 ));
		__tool_bar->Insert( *new TFlyByTIPButton( CM_FILEPRINT, CM_FILEPRINT  ) );
	#endif

	__tool_bar->Insert( *new TSeparatorGadget( 12 ));
	__tool_bar->Insert( *new TFlyByTIPButton( CM_TERMINAL,  CM_TERMINAL,
															TButtonGadget::NonExclusive ) );

	__tool_bar->Insert( *new TSeparatorGadget( 12 ));
	__tool_bar->Insert( *__speed_button_1 );
	__tool_bar->Insert( *__speed_button_2 );
	__tool_bar->Insert( *__speed_button_3 );

	__tool_bar->Insert( *new TSeparatorGadget( 12 ));
	__tool_bar->Insert( *new TControlGadget( *__rx_gauge ));

	__tool_bar->Insert( *new TSeparatorGadget( 12 ));
	__tool_bar->Insert( *new TControlGadget( *__clock ));

	__status_bar->Insert( *__status_bar_slot_1 );
	__status_bar->Insert( *__status_bar_slot_2 );

   for ( int i = CM_BEGIN; i <= CM_END; i++ )
      aVCR[ i - CM_BEGIN ] = new TFlyByTIPButton( i, i );

   oSpc = new TSeparatorGadget( 12 );

	Insert( *__tool_bar );
	Insert( *__status_bar, TDecoratedFrame::Bottom );

	SetIcon( GetModule(), "WinBolsa" );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                         DESTRUCTOR
//    ===============================
//
TDrvdDecoratedFrame::~TDrvdDecoratedFrame()
{
   for ( int i = CM_BEGIN; i <= CM_END; i++ )
      delete aVCR[ i - CM_BEGIN ];

   delete oSpc;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        SetupWindow
//    ===============================
//
void TDrvdDecoratedFrame::SetupWindow()
{
	TDecoratedMDIFrame::SetupWindow();
	__clock->SetPropVisible( false );	// Hide __clock VBX

	__rx_gauge->Show( SW_HIDE );			// Hide __rx_gauge control
	__rx_gauge->SetRange( 1, 384 );

	TRect r = GetClientRect();
	FrameWndSize = TSize( r.BottomRight() );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    CannotClose
//    ===============================
//
static bool CannotClose( TWindow* win, void* )
{
	if ( win->HWindow == __terminal->HWindow )
		return false;

	return !win->CanClose();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    CloseChild
//    ===============================
//
static void CloseChild( TWindow* win, void* )
{
	if ( win->HWindow == __terminal->HWindow )
		return;

	win->Destroy();
	delete win;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                           CanClose
//    ===============================
//
bool TDrvdDecoratedFrame::CanClose()
{
	bool ret = GetClientWindow()->CloseChildren();
	if ( ret )
		UpdateWindow();

	return ret;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                            VCRShow
//    ===============================
//
void TDrvdDecoratedFrame::VCRShow( bool show )
{
	if ( show )
	{
		TGadget *g, *p = __speed_button_3;
		while ( p ) {	// Find the last gadget in the toolbar
			g = p;      // The last gadget is the __clock VBX
			p = __tool_bar->NextGadget( *g );
		}
		for ( int i = CM_BEGIN; i <= CM_END; i++ )
			// Insert VCR before __clock VBX
			__tool_bar->Insert( *aVCR[ i - CM_BEGIN ], TGadgetWindow::Before, g );

      __tool_bar->Insert( *oSpc, TGadgetWindow::Before, g );
	}
	else
	{
		TGadget *v = __tool_bar->GadgetWithId( CM_END );
		v = __tool_bar->NextGadget( *v );

		// Remove space between VCR and __clock VBX
		__tool_bar->Remove( *v );

		// Remove VCR from the __tool_bar
		for ( register int i = CM_BEGIN; i <= CM_END; i++ )
		{
			v = __tool_bar->GadgetWithId(i);
			__tool_bar->Remove( *v );
		}
	}
	__tool_bar->LayoutSession();
	__tool_bar->Invalidate();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                             EvMove
//    ===============================
//
void TDrvdDecoratedFrame::EvMove( TPoint& clientOrigin )
{
	DefaultProcessing();

	if ( !__is_dirty )			// If not already DIRTY
		if ( !IsIconic() )
			__is_dirty = true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                             EvSize
//    ===============================
//
void TDrvdDecoratedFrame::EvSize( uint sizeType, TSize& size )
{
	TDecoratedFrame::EvSize( sizeType, size );

	TRect rc = GetClientRect();
	rc.bottom /= 2;

	if ( __terminal )
		__terminal->MoveWindow( rc, true );

	if ( !__is_dirty )			// If not already DIRTY
		if ( !IsIconic() )
			if ( FrameWndSize != size )
				__is_dirty = true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        CmStockDial
//    ===============================
//
void TDrvdDecoratedFrame::CmStockDial()
{
	TDialDialog( this, DialDlg ).Execute();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        CeStockDial
//    ===============================
//
void TDrvdDecoratedFrame::CeStockDial( TCommandEnabler& ce )
{
	ce.Enable( __is_valid_comm && !__is_attached );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                      CmStockHangUp
//    ===============================
//
void TDrvdDecoratedFrame::CmStockHangUp()
{
	__comm->HangUp();            // Disconect modem

	if ( __is_attached )
	{
		__is_attached   = false;
		__is_valid_comm = __is_frst_ntbf_inst = true;

										  // Restore panels
		__status_bar_slot_2->SetText( "DESCONECTADO" );
		__rx_gauge->Show( SW_HIDE );
		__clock->SetTime();
										  // Disable comm notifications
		::EnableCommNotification( __comm->GetCommId(), NULL, 0, 0 );

		ClearQuery();             // Clear all query member variables
		AppendFromCapture();      // Transport all pending records
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        CmFilePrint
//    ===============================
//
void TDrvdDecoratedFrame::CmFilePrint()
{
	if ( GetActiveDoc() )
	{
		if ( doc->GetTableType() == NOGARQ )
			MessageBox( "Impressão somente para\rdocumentos padrão 'WinBolsa'",
							"WinBolsa® - Aviso", MB_OK | MB_ICONINFORMATION );

		else if ( doc->GetTableType() == GARQBIG )
			;
		else
			MessageBox( "Opção não implementada.", "WinBolsa® - Aviso",
							 MB_OK | MB_ICONINFORMATION );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        CeFilePrint
//    ===============================
//
void TDrvdDecoratedFrame::CeFilePrint( TCommandEnabler& ce )
{
	TTableDocument* d = TYPESAFE_DOWNCAST( GetApplication()->GetDocManager()
														->GetCurrentDoc(), TTableDocument );
	ce.Enable( d && !__is_query_running );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                 CmFilePrinterSetup
//    ===============================
//
void TDrvdDecoratedFrame::CmFilePrinterSetup()
{
	TPrinter().Setup( this );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        CmHelpIndex
//    ===============================
//
void TDrvdDecoratedFrame::CmHelpIndex()
{
	WinHelp( "WINBOLSA.HLP", HELP_INDEX, 0 );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        CmHelpHelp
//    ===============================
//
void TDrvdDecoratedFrame::CmHelpHelp()
{
	WinHelp( "WINBOLSA.HLP", HELP_HELPONHELP, 0 );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                            CmAbout
//    ===============================
//
void TDrvdDecoratedFrame::CmAbout()
{
	TAboutDlg( this, AboutDlg ).Execute();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                       GetActiveDoc
//    ===============================
//
bool TDrvdDecoratedFrame::GetActiveDoc()
{
	doc = TYPESAFE_DOWNCAST( GetApplication()->GetDocManager()->GetCurrentDoc(),
									 TTableDocument );

	// GetCurrentDoc return the document with the focus. If the document is
	// MINIMIZED it doesn't have the focus and 'doc' will be a NULL pointer
	if ( doc )
		return true;

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        IsValidComm
//    ===============================
//
bool TDrvdDecoratedFrame::IsValidComm()
{
	// Can't QUERY when configuration dialog is open
	if ( !__is_frst_ntbf_inst )
		return false;

	// Can't QUERY when modem is not configured
	if ( !__is_valid_comm )
	{
		int i = MessageBox( "A Porta Serial não responde.\rAperte 'SIM' para reconfigurar a\rporta serial e refaça a consulta",
								  "WinBolsa® - Aviso", MB_YESNO | MB_ICONQUESTION );
		if ( i == IDYES )
			SendMessage( WM_COMMAND, CM_CONFIG, 0L );

		return false;
	}
	// Can't QUERY when there's no 'UserId'
	if ( strlen( __notebook_tab_1.Id ) == 0 )
	{
		MessageBox( "O 'Nome do Participante' não se encontra preenchido.\rPreencha o campo e refaça a consulta",
						"WinBolsa® - Aviso", MB_OK );
		return false;
	}
	// Can't QUERY when there's no 'Password'
	if ( strlen( __notebook_tab_1.Passw ) == 0 )
	{
		MessageBox( "A 'Senha do Participante' não se encontra preenchida.\rPreencha o campo e refaça a consulta",
						"WinBolsa® - Aviso", MB_OK );
		return false;
	}
	// Can't QUERY when there's no 'Phone Number'
	if ( strlen( __notebook_tab_1.Phone ) == 0 )
	{
		MessageBox( "O 'Número do Telefone' não se encontra preenchido.\rPreencha o campo e refaça a consulta",
						"WinBolsa® - Aviso", MB_OK );
		return false;
	}
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        OpenCapture
//    ===============================
//
bool TDrvdDecoratedFrame::OpenCapture()
{
	__capture.close();
	__capture.open( __capture_path.c_str(), ios::out | ios::binary );

	if ( __capture.fail() ) {
		MessageBox( "Erro ao criar Arquivo de Transporte", "WinBolsa® - Erro",
						 MB_OK | MB_ICONEXCLAMATION );
		return false;
	}
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                            Connect
//    ===============================
//
void TDrvdDecoratedFrame::Connect()
{
	ClearQuery();

	if ( !__is_attached )
	{
		int i = IDNO;
		do {
			SendMessage( WM_COMMAND, CM_STOCKDIAL, 0L );

			if ( !__is_attached )
				 i = MessageBox( "Consulta não foi efetuada.\rDeseja consultar novamente ?",
									  "WinBolsa® - Aviso", MB_YESNO | MB_ICONQUESTION );
			else
         	break;
		} while ( i == IDYES );
	}

	if ( __is_attached )
		PostRequest();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                        PostRequest
//    ===============================
//
void TDrvdDecoratedFrame::PostRequest()
{
	__is_query_running = true;
	__is_valid_comm    = __is_frst_ntbf_inst = false;

	// Reset clock to show conection time
   __clock->Reset();

   // Enable 'WM_COMMNOTIFY' messages
   ::EnableCommNotification( __comm->GetCommId(), *this, 1024, 1024 );

   // Make a request
   Request();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdDecoratedFrame
//                    SpeedButtonMenu
//    ===============================
//
void TDrvdDecoratedFrame::SpeedButtonMenu( uint cmd, uint id )
{
	// Find client area coordinates of the gadget button
	TGadget* g = __tool_bar->GadgetWithId( cmd );
	TRect r = g->GetBounds();

	// Convert coordinates to screen equivalent
	TPoint p = r.BottomLeft();
	__tool_bar->ClientToScreen(p);

	// Load menu resource
	TMenu m( *GetModule(), id );

	// Remove the first two menu itens
	for ( int n = 0; n < 2; n++ )
		TMenu( m.GetSubMenu(1) ).DeleteMenu( 0, MF_BYPOSITION );

	TPopupMenu k( m.GetSubMenu(1) );
   k.TrackPopupMenu( TPM_LEFTALIGN, p.x, p.y, 0, *this );

	// Restore gadget button state to unchecked
	TButtonGadget *j = TYPESAFE_DOWNCAST( __tool_bar->GadgetWithId( cmd ),
													  TButtonGadget );
	if ( j )
		j->SetButtonState( TButtonGadget::Up );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdMDIClient
//                      CloseChildren
//    ===============================
//
bool TDrvdMDIClient::CloseChildren()
{
	if ( !FirstThat( CannotClose ) ) {

		ForEach( CloseChild );
		return true;
	}
	return false;
}

