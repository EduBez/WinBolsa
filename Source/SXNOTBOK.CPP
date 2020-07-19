//-------------------------------------------//
//                                           //
//    NOTEBOOK. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "globals.h"
#include "notebook.h"


/////////////////////////////////////
//    TNoteBookPage
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TNoteBookPage, TDialog )
	EV_COMMAND( IDOK, CmOk ),
	EV_COMMAND( IDCANCEL, CmCancel ),
	EV_WM_SHOWWINDOW,
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookPage
//                        CONSTRUCTOR
//    ===============================
//
TNoteBookPage::TNoteBookPage( TWindow* parent, const char* title, TResId resid,
										TModule* module )
										: TDialog( parent, resid, module )
{
	Init( parent, title, module );
	Caption = title;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookPage
//                           CmCancel
//    ===============================
//
void TNoteBookPage::CmCancel()
{ 
	Parent->Destroy();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookPage
//                           CanClose
//    ===============================
//
bool TNoteBookPage::CanClose()
{
	__is_frst_ntbf_inst = true;
	TransferData( tdGetData );
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookPage
//                      PreProcessMsg
//    ===============================
//
bool TNoteBookPage::PreProcessMsg( MSG& Msg )
{
	if ( Msg.message == WM_KEYDOWN && Msg.wParam == VK_TAB )
	{
      TWindow* Control;

      if ( GetKeyState( VK_SHIFT ) < 0 )
         Control = new TWindow( GetNextDlgTabItem( ::GetFocus(), true ));

      else
         Control = new TWindow( ::GetFocus() );

      if ( Control->GetId() == IDCANCEL )
      {
         Parent->SetFocus();
         return true;
      }
	}
	return TDialog::PreProcessMsg( Msg);
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookPage
//                       EvShowWindow
//    ===============================
//
void TNoteBookPage::EvShowWindow( bool show, uint status )
{
	if ( show != SW_HIDE )
	{
		Parent->SetCaption( Caption );
		SetFocus();
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookTab1
//                        CONSTRUCTOR
//    ===============================
//
TNoteBookTab1::TNoteBookTab1( TWindow* parent, const char* title, TResId resid,
										TModule* module )
										: TNoteBookPage( parent, title, resid, module )
{
	SetTransferBuffer( &__notebook_tab_1 );

	Id       = new TEdit( this, IDC_ID,       sizeof( __notebook_tab_1.Id    ));
	PassWord = new TEdit( this, IDC_PASSWORD, sizeof( __notebook_tab_1.Passw ));
	Phone		= new TEdit( this, IDC_PHONE,		sizeof( __notebook_tab_1.Phone ));

	Phone->SetValidator( new TPXPictureValidator( "*#" ));

	new TODAButton( this, IDOK     );
	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookTab2
//                        CONSTRUCTOR
//    ===============================
//
TNoteBookTab2::TNoteBookTab2( TWindow* parent, const char* title, TResId resid,
										TModule* module )
										: TNoteBookPage( parent, title, resid, module )
{
	SetTransferBuffer( &__notebook_tab_2 );

	Pulse     = new TRadioButton( this, IDC_PULSE );
	Tone      = new TRadioButton( this, IDC_TONE  );
	Prefix    = new TEdit(        this, IDC_LINEPREFIX, sizeof( __notebook_tab_2.Prefix ));
	UsePrefix = new TCheckBox(    this, IDC_USELINEPREFIX, 0 );
	Signal    = new TEdit(        this, IDC_LINESIGNAL, sizeof( __notebook_tab_2.Signal ));

	Prefix->SetValidator( new TPXPictureValidator( "*#" ));
	Signal->SetValidator( new TPXPictureValidator( "*#" ));

	new TODAButton( this, IDOK     );
	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookTab3
//                        CONSTRUCTOR
//    ===============================
//
TNoteBookTab3::TNoteBookTab3( TWindow* parent, const char* title, TResId resid,
										TModule* module )
										: TNoteBookPage( parent, title, resid, module )
{
	SetTransferBuffer( &__notebook_tab_3 );

	InitString  = new TEdit( this, IDC_INITSTRING,  sizeof( __notebook_tab_3.InitString  ));
	TimeOutTime = new TEdit( this, IDC_TIMEOUTTIME, sizeof( __notebook_tab_3.TimeoutTime ));

	TimeOutTime->SetValidator( new TPXPictureValidator( "*#" ));

	new TODAButton( this, IDOK     );
	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookTab4
//                        CONSTRUCTOR
//    ===============================
//
TNoteBookTab4::TNoteBookTab4( TWindow* parent, const char* title, TResId resid,
										TModule* module )
										: TNoteBookPage( parent, title, resid, module )
{
	SetTransferBuffer( &__notebook_tab_4 );

	Baud300      = new TRadioButton ( this, IDC_BAUD300      );
	Baud600      = new TRadioButton ( this, IDC_BAUD600      );
	Baud1200     = new TRadioButton ( this, IDC_BAUD1200     );
	Baud2400     = new TRadioButton ( this, IDC_BAUD2400     );
	Baud4800     = new TRadioButton ( this, IDC_BAUD4800     );
	Baud9600     = new TRadioButton ( this, IDC_BAUD9600     );
	Baud19200    = new TRadioButton ( this, IDC_BAUD19200    );
	Data5        = new TRadioButton ( this, IDC_DATA5        );
	Data6        = new TRadioButton ( this, IDC_DATA6        );
	Data7        = new TRadioButton ( this, IDC_DATA7        );
	Data8        = new TRadioButton ( this, IDC_DATA8        );
	Stop1        = new TRadioButton ( this, IDC_STOP1        );
	Stop15       = new TRadioButton ( this, IDC_STOP15       );
	Stop2        = new TRadioButton ( this, IDC_STOP2        );
	ParityNone   = new TRadioButton ( this, IDC_PARITYNONE   );
	ParityOdd    = new TRadioButton ( this, IDC_PARITYODD    );
	ParityEven   = new TRadioButton ( this, IDC_PARITYEVEN   );
	ParityMark   = new TRadioButton ( this, IDC_PARITYMARK   );
	ParitySpace  = new TRadioButton ( this, IDC_PARITYSPACE  );
	FlowHardware = new TRadioButton ( this, IDC_FLOWHARDWARE );
	FlowXonXoff  = new TRadioButton ( this, IDC_FLOWXONXOFF  );
	FlowNone     = new TRadioButton ( this, IDC_FLOWNONE     );
	Com1         = new TRadioButton ( this, IDC_COM1         );
	Com2         = new TRadioButton ( this, IDC_COM2         );
	Com3         = new TRadioButton ( this, IDC_COM3         );
	Com4         = new TRadioButton ( this, IDC_COM4         );
	ComNone      = new TRadioButton ( this, IDC_COMNONE      );

	new TODAButton( this, IDOK     );
	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookTab4
//                        SetupWindow
//    ===============================
//
void TNoteBookTab4::SetupWindow()
{
	TDialog::SetupWindow();
	memset( &__notebook_tab_4, '\x0', sizeof( __notebook_tab_4 ));

	__comm->GetPropAll( &__notebook_tab_4 );
	TransferData( tdSetData );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookTab4
//                           CanClose
//    ===============================
//
bool TNoteBookTab4::CanClose()
{
	::SetCursor( ::LoadCursor( 0, IDC_WAIT ));
	__status_bar->SetText( "Inicializando Modem..." );

	Frame->Invalidate();
	Frame->UpdateWindow();

	TransferData( tdGetData );

	__comm->SetPropAll( __notebook_tab_4 );
	__is_dirty = true;

	TYPESAFE_DOWNCAST( Parent, TNoteBookFrame )->IsComm = __is_valid_comm;
	__is_frst_ntbf_inst = true;

	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE2( TNoteBookFrame, TDialog, TVbxEventHandler )
	EV_WM_ERASEBKGND,
	EV_COMMAND( IDOK, CmOk ),
	EV_COMMAND( IDCANCEL, CmCancel ),
	EV_MESSAGE( WM_USER_MESSAGE, EvMessage ),
	EV_VBXEVENTINDEX( IDC_MhTab, Event_SaxTab_Click, EvClick ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                        CONSTRUCTOR
//    ===============================
//
TNoteBookFrame::TNoteBookFrame( TWindow* parent, TResId resid, TModule* module )
										  : TAutoCenterDialog( parent, resid, module )
{
	IsComm = __is_valid_comm;

	__is_valid_comm     = false;
	__is_frst_ntbf_inst = false;

	__speed_button_1->CommandEnable();
	__speed_button_3->CommandEnable();

	TabIndex = PrevTabIndex = 0;
	TabCtl   = new TVbxSaxTab( this, IDC_MhTab, "MhTab", 0,0,0,0 );

	Tab1Dlg  = new TNoteBookTab1( this, "Configurar - Bolsa",       ModemDlgTab1 );
	Tab2Dlg  = new TNoteBookTab2( this, "Configurar - Discagem",    ModemDlgTab2 );
	Tab3Dlg  = new TNoteBookTab3( this, "Configurar - Modem",       ModemDlgTab3 );
	Tab4Dlg  = new TNoteBookTab4( this, "Configurar - Comunicação", ModemDlgTab4 );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                        SetupWindow
//    ===============================
//
void TNoteBookFrame::SetupWindow()
{
	TAutoCenterDialog::SetupWindow();

	Tab1Dlg->Create();
	Tab2Dlg->Create();
	Tab3Dlg->Create();
	Tab4Dlg->Create();

	SetupTabCtl();
	PostMessage( WM_USER_MESSAGE, 0, 0 );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                            Destroy
//    ===============================
//
void TNoteBookFrame::Destroy( int retVal )
{
	__is_valid_comm     = IsComm;
	__is_frst_ntbf_inst = true;

	TAutoCenterDialog::Destroy( IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                      PreProcessMsg
//    ===============================
//
bool TNoteBookFrame::PreProcessMsg( MSG& Msg )
{
	TNoteBookPage* v[] = { Tab1Dlg, Tab2Dlg, Tab3Dlg, Tab4Dlg };
	bool RetVal = TAutoCenterDialog::PreProcessMsg( Msg);

	if ( Msg.message == WM_SYSKEYDOWN )
	{
		::PostMessage( (HWND)v[ TabIndex ], Msg.message, Msg.wParam, Msg.lParam );
		v[ TabIndex ]->SetFocus();

		TabCtl->Refresh();
	}

	if ( Msg.message == WM_KEYDOWN && Msg.wParam == VK_TAB )
	{
		if ( GetKeyState( VK_SHIFT ) < 0 )
		{
			TWindow* ChildWnd = v[ TabIndex ]->ChildWithId( IDCANCEL );
			ChildWnd->SetFocus();

			ChildWnd->Invalidate();
			ChildWnd->UpdateWindow();
		}
		else
			v[ TabIndex ]->SetFocus();

		TabCtl->Refresh();
	}
	return RetVal;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                        SetupTabCtl
//    ===============================
//
inline void TNoteBookFrame::SetupTabCtl()
{
	TRect rc1, rc2;

	Tab1Dlg->GetWindowRect( rc1 );
	GetWindowRect( rc2 );

	TPoint p0( rc1.left  , rc1.top    );
	TPoint p1( rc1.right , rc1.bottom );

	TPoint p2( rc2.left  , rc2.top    );
	TPoint p3( rc2.right , rc2.bottom );

	ScreenToClient( p0 );
	ScreenToClient( p1 );

	ScreenToClient( p2 );
	ScreenToClient( p3 );

	TabCtl->MoveWindow( 0, p1.y, p3.x + p2.x, p3.y - p1.y );

	TabCtl->SetPropCaption( string( " Bolsa | Discagem | Modem | Comunicação " ));
	TabCtl->SetPropFontName( string( "MS Sans Serif" ));

	TabCtl->SetPropFontSize( 180.0 );
	TabCtl->SetPropFontBold( true );

	TabCtl->SetPropActiveTabColor( TColor::LtGray  );
	TabCtl->SetPropInactiveTabColor( TColor::White );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                          EvMessage
//    ===============================
//
LRESULT TNoteBookFrame::EvMessage( WPARAM wParam, LPARAM lParam )
{
	// Creates event structure to be fired
	VBXEVENT event;
	event.Control    = TabCtl->GetHCTL();
	event.Window     = HWND( TabCtl );
	event.ID         = IDC_MhTab;
	event.EventIndex = TabIndex;
	event.EventName  = "Click";
	event.NumParams  = 0;
	event.ParamList  = 0;

	EvClick( &event );      // Fires simulated Click event
	return (LRESULT) 0;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                            EvClick
//    ===============================
//
void TNoteBookFrame::EvClick( VBXEVENT FAR* click )
{
	TabCtl->GetPropActiveTab(  TabIndex );

	TNoteBookPage* v[] = { Tab1Dlg, Tab2Dlg, Tab3Dlg, Tab4Dlg };

	v[ PrevTabIndex ]->Show( SW_HIDE );
	v[ TabIndex]->Show( SW_SHOWNOACTIVATE );

	PrevTabIndex = TabIndex;
	TabCtl->SetFocus();
}

