//-------------------------------------------//
//                                           //
//    WINBOLS0. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "winbolsa.h"
#include <dir.h>


// 	TDrvdApp function definition directory
// 	--------------------------------------
//
// 	1) RESPONSE_TABLE
// 	2) CONSTRUCTOR
// 	3) DESTRUCTOR
// 	4) InitMainWindow
//		5) CanClose
//	   6)	CmFileNew
//	   7)	CmTerminal
//	   8)	CeTerminal
//    9) CmConfig
//   10) CeConfig
//	  11) EvNewView
//	  12) EvCloseView


/////////////////////////////////////
//    TDrvdApp
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TDrvdApp, TApplication )
	EV_OWLVIEW( dnCreate                                     , EvNewView   ),
	EV_OWLVIEW( dnClose                                      , EvCloseView ),
	EV_COMMAND(	CM_FILENEW                                   , CmFileNew   ),
	EV_COMMAND(	CM_TERMINAL                                  , CmTerminal  ),
	EV_COMMAND( CM_CONFIG                                    , CmConfig    ),
	EV_COMMAND_ENABLE( CM_CONFIG                             , CeConfig    ),
	EV_COMMAND_ENABLE( CM_TERMINAL                           , CeTerminal  ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_TODO_MESTRE			, CmBoletimFechamentoRioTodoMestre        ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_TODO_INDICE			, CmBoletimFechamentoRioTodoIndice        ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_TODO_TOTAIS_SENN	, CmBoletimFechamentoRioTodoTotaisSENN    ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_TODO_INDICES_SENN	, CmBoletimFechamentoRioTodoIndicesSENN   ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_TODO_COTACOES		, CmBoletimFechamentoRioTodoCotacoes      ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_MERCTIT			   , CmBoletimFechamentoRioMercTit           ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_INDICES			   , CmBoletimFechamentoRioIndices           ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_4ULT_MESTRE			, CmBoletimFechamentoRio4ultMestre        ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_4ULT_INDICE			, CmBoletimFechamentoRio4ultIndice        ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_RIO_4ULT_COTACOES		, CmBoletimFechamentoRio4ultCotacoes      ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_BOVESPA_MERCTIT			, CmBoletimFechamentoBovespaMercTit       ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_BOVESPA_INDICES			, CmBoletimFechamentoBovespaIndices       ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_BOVESPA_4ULT_MESTRE		, CmBoletimFechamentoBovespa4ultMestre    ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_BOVESPA_4ULT_COTACOES	, CmBoletimFechamentoBovespa4ultCotacoes  ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_DATAS_RIO			      , CmBoletimFechamentoDatasRio             ),
	EV_COMMAND( CM_BOLETIM_FECHAMENTO_DATAS_SAOPAULO			, CmBoletimFechamentoDatasSaoPaulo        ),
	EV_COMMAND( CM_BOLETIM_INSTANTANEO			               , CmBoletimInstantaneo                    ),
	EV_COMMAND( CM_SERIES_HISTORICAS_ACOES			            , CmSeriesHistoricasAcoes                 ),
	EV_COMMAND( CM_SERIES_HISTORICAS_INDICES			         , CmSeriesHistoricasIndices               ),
	EV_COMMAND( CM_RELACAO_DE_NEGOCIOS			               , CmRelacaoDeNegocios                     ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                        CONSTRUCTOR
//    ===============================
//
TDrvdApp::TDrvdApp( const char* name ) : TApplication( name )
{
	memset( &__notebook_tab_1, '\x0', sizeof( __notebook_tab_1 ) );
	memset( &__notebook_tab_2, '\x0', sizeof( __notebook_tab_2 ) );
	memset( &__notebook_tab_3, '\x0', sizeof( __notebook_tab_3 ) );
	memset( &__notebook_tab_4, '\x0', sizeof( __notebook_tab_4 ) );

	NoteBookFrame       = 0;
	EnumMDIChildWindows = 0;

	TerminalRect.SetNull();

	char sbuff[255] = "";
	getcwd( sbuff, sizeof( sbuff ));

	__ini_file_name = sbuff + string( "\\WINBOLSA.INI" );

	AppName = name;
	checked = false;

	EnableCtl3d( true );
	EnableBWCC( false );

	if ( AddFontResource( "DIGITAL.FON" ))
		::SendMessage( HWND_BROADCAST, WM_FONTCHANGE, 0, 0L );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                         DESTRUCTOR
//    ===============================
//
TDrvdApp::~TDrvdApp()
{
	if ( RemoveFontResource( "DIGITAL.FON" ))
		::SendMessage( HWND_BROADCAST, WM_FONTCHANGE, 0, 0L );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                     InitMainWindow
//    ===============================
//
void TDrvdApp::InitMainWindow()
{
	oSplashDlg = new TSplashDialog( 0, SplashDialog );
	oSplashDlg->Create();

	HAccTable = LoadAccelerators( ID_MENUACCEL );

	SetMainWindow( new TDrvdDecoratedFrame( AppName, IDM_FRAME_MENU,
														 *( Client = new TDrvdMDIClient )));

	GetMainWindow()->SetMenuDescr( TMenuDescr( IDM_FRAME_MENU, 1, 0, 0, 1, 1, 1 ));

	SetDocManager( new TDocManager( dmMDI ));
	ReadIniPrivateFile();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                           CanClose
//    ===============================
//
bool TDrvdApp::CanClose()
{
	if ( TApplication::CanClose() )
	{
		if ( __is_valid_comm )
			__comm->HangUp();            // Sends HangUp just in case

		WriteIniPrivateFile();          // Saves Appl. info to INI file
		__comm->WriteIniPrivateFile();  // Saves Comm. info to INI file
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                          CmFileNew
//    ===============================
//
void TDrvdApp::CmFileNew()
{
	// Find client area coordinates of the gadget button
	TGadget* g = __tool_bar->GadgetWithId( CM_FILENEW );
	TRect r = g->GetBounds();

	// Convert coordinates to screen equivalent
	TPoint p = r.BottomLeft();
	__tool_bar->ClientToScreen(p);

	// Load 'Frame Menu' resource
   TMenu v( *GetMainWindow()->GetModule(), IDM_FRAME_MENU );
   TMenu m( v.GetSubMenu(0) );

	TPopupMenu k( m.GetSubMenu(0) );
	k.TrackPopupMenu( TPM_LEFTALIGN, p.x, p.y, 0, *GetMainWindow() );

	// Restore gadget button state to unchecked
	TButtonGadget *j = TYPESAFE_DOWNCAST( __tool_bar->GadgetWithId( CM_FILENEW ),
													  TButtonGadget );
	if ( j )
		j->SetButtonState( TButtonGadget::Up );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                         CmTerminal
//    ===============================
//
void TDrvdApp::CmTerminal()
{
	TButtonGadget *v = TYPESAFE_DOWNCAST( __tool_bar->GadgetWithId( CM_TERMINAL ),
													  TButtonGadget );
	if ( !checked )
	{
		v->SetButtonState( TButtonGadget::Down );

		checked = true;
		Child   = TYPESAFE_DOWNCAST( Client->GetActiveMDIChild(), TQueryMDIChild );

		__terminal->Show( SW_SHOW );
		__terminal->SetFocus();
	}
	else
	{
		v->SetButtonState( TButtonGadget::Up );

		checked    = false;
		bool focus = false;

		if ( (HWND)Client->GetActiveMDIChild() == (HWND)__terminal )
			focus = true;

		__terminal->Show( SW_HIDE );

		if ( Child && focus && EnumMDIChildWindows )
			Child->SetFocus();
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                         CeTerminal
//    ===============================
//
void TDrvdApp::CeTerminal( TCommandEnabler& ce )
{
	if ( checked )
		ce.SetText( "Ocultar &Terminal" );
	else
		ce.SetText( "Exibir &Terminal" );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                           CmConfig
//    ===============================
//
void TDrvdApp::CmConfig()
{
	delete NoteBookFrame;
	NoteBookFrame = new TNoteBookFrame( GetMainWindow(), ModemDlgFrame );
	NoteBookFrame->Create();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                           CeConfig
//    ===============================
//
void TDrvdApp::CeConfig( TCommandEnabler& ce )
{
	ce.Enable( __is_frst_ntbf_inst );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                          EvNewView
//    ===============================
//
void TDrvdApp::EvNewView( TView& view )
{
	TTableView* vw = TYPESAFE_DOWNCAST( &view, TTableView );

	if ( vw ) {
		Child = new TQueryMDIChild( vw->GetViewType(), *Client, 0, view.GetWindow() );

		if ( view.IsOK() )
		{
			if ( 	++EnumMDIChildWindows == 1 )
				// Show VCR speed buttons
				TYPESAFE_DOWNCAST( GetMainWindow(), TDrvdDecoratedFrame )->VCRShow( true );

			Child->Create();
		}
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDrvdApp
//                        EvCloseView
//    ===============================
//
void TDrvdApp::EvCloseView( TView& view )
{
	if ( view.IsOK() )
	{
		if ( 	--EnumMDIChildWindows == 0 )
			// Hide VCR speed buttons
			TYPESAFE_DOWNCAST( GetMainWindow(), TDrvdDecoratedFrame )->VCRShow( false );

		if ( 	EnumMDIChildWindows < 0 )
			EnumMDIChildWindows = 0;
	}
}





////////////////////////////////////////////////
Code4 __code4;      ///// GLOBAL VARIALBLE /////



/*****************************
 *     OWL Main Function     *
 *****************************/

int OwlMain( int /*argc*/, char* /*argv*/ [] )
{
	#if 0
		Date4 today;
		today.today();

		today.format( "CCYYMMDD" );
		string date = today.ptr();

		// Dead line for demo version
		if ( date >= "19951130" )
		{
			::MessageBox( 0, "Versão de demonstração. Prazo de validade está vencido.",
							  "WinBolsa® - Aviso", MB_OK | MB_ICONINFORMATION );
			return 0;
		}
	#endif

	int QueueSize = 120;

	while ( ! ::SetMessageQueue( QueueSize ) && QueueSize > 0 )
		QueueSize -= 8;

	__code4.exclusive     = 0;
	__code4.lockAttempts  = 1;
	__code4.optimize      = 1;
	__code4.optimizeWrite = 1;
	__code4.safety        = 0;

	TBIVbxLibrary VBX;	// Loads BIVBX'xx'.DLL
	TDrvdApp( "WinBolsa® 1.0" ).Run();

	return 0;
}

