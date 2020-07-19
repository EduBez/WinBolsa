//-------------------------------------------//
//                                           //
//    NOTEBOOK. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include <owl/validate.h>

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
	UsePrefix = new TCheckBox(    this, IDC_USELINEPREFIX, 0  );
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

	GetApplication()->GetMainWindow()->UpdateWindow();
	GetApplication()->GetMainWindow()->Invalidate();

	TransferData( tdGetData );
	__comm->SetPropAll( __notebook_tab_4 );

	TYPESAFE_DOWNCAST( Parent, TNoteBookFrame )->IsComm = __is_valid_comm;

	__is_dirty = __is_frst_ntbf_inst = true;

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
	EV_VBXEVENTINDEX( IDC_MhTab, Event_MhTab_Click, EvClick ),
	EV_VBXEVENTINDEX( IDC_MhTab, Event_MhTab_KeyDown, EvKeyDown ),
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
	TabCtl   = new TVbxMhTab( this, IDC_MhTab );

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
	PostMessage( WM_USER_MESSAGE, 0, 0 );

	TRect rc;
	TabCtl->GetWindowRect( rc );

	TPoint p1( rc.left , rc.top    ),
			 p2( rc.right, rc.bottom );

	ScreenToClient( p1 );
	ScreenToClient( p2 );

	x = p1.x;
	y = p2.y - 3;
	w = p2.x - p1.x - 1;
	h = p2.y - p1.y;

	GetClientRect( rc );
	h = ( rc.bottom - rc.top ) - ( h + x );

	SetEachTab(4);

	Tab1Dlg->Create();
	Tab2Dlg->Create();
	Tab3Dlg->Create();
	Tab4Dlg->Create();
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
//                       EvEraseBkgnd
//    ===============================
//
bool TNoteBookFrame::EvEraseBkgnd( HDC hDC )
{
	TAutoCenterDialog::EvEraseBkgnd( hDC );

	TDC dc( hDC );
	TPen HighLight( GetSysColor( COLOR_BTNHIGHLIGHT ));
	TPen Shadow( GetSysColor( COLOR_BTNSHADOW ));

	for ( register int n = 0; n < 3; n++ )
	{
		x01 = x + ( n + 0 );
		y01 = y + ( n + 0 );
		x11 = ( x + w ) - n;
		y11 = ( y + h ) - n;

		dc.MoveTo( x01, y11 );

		if ( n > 0 ) dc.SelectObject( HighLight );
		dc.LineTo( x01, y01 );
		dc.MoveTo( x11, y01 );

		if ( n > 0 ) dc.SelectObject( Shadow );
		dc.LineTo( x11, y11 );
		dc.LineTo( x01, y11 );
	}
	return true;
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
	TabCtl->GetPropActiveFolder( TabIndex );

	if ( TabIndex != PrevTabIndex )
		UpdateTab();

	TNoteBookPage* v[] = { Tab1Dlg, Tab2Dlg, Tab3Dlg, Tab4Dlg };

	v[ PrevTabIndex ]->Show( SW_HIDE );
	v[ TabIndex]->Show( SW_SHOWNOACTIVATE );

	PrevTabIndex = TabIndex;
	TabCtl->SetFocus();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                          EvKeyDown
//    ===============================
//
void TNoteBookFrame::EvKeyDown( VBXEVENT FAR* event )
{
	int **p = (int**) event->ParamList;
	int key = *(*( p + 1 ));

	if ( key == VK_LEFT || key == VK_RIGHT )
	{
		if ( key == VK_LEFT )
		{
			if ( TabIndex == 0 )
				TabCtl->SetPropActiveFolder(3);
		}
		else if ( key == VK_RIGHT )
		{
			if ( TabIndex == 3 )
				TabCtl->SetPropActiveFolder(0);
		}
		EvClick(0);
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                         SetEachTab
//    ===============================
//
void TNoteBookFrame::SetEachTab( int numElem )
{
	TabCtl->SetPropFillColor( GetSysColor( COLOR_BTNFACE ));
	TabCtl->SetPropTabSpacing(1);

	for ( register int n = numElem; n >= 0; n-- )
	{
		TabCtl->SetPropFolder(n);

		TabCtl->SetPropTabLightColor( GetSysColor( COLOR_BTNHIGHLIGHT ));
		TabCtl->SetPropTabFillColor( GetSysColor( COLOR_BTNFACE ));

		TabCtl->SetPropPageBevelSize(2);
		TabCtl->SetPropPageBevelStyle( TVbxMhTab::PageBevelStyle_1_Raised );

		TabCtl->SetPropPageLightColor( GetSysColor( COLOR_BTNHIGHLIGHT ));
	}

	TabCtl->SetPropTabBevelSize(2);
   #ifdef BC_5x
	TabCtl->SetPropTabFillColor( GetSysColor( COLOR_WINDOW ));
   #endif
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TNoteBookFrame
//                          UpdateTab
//    ===============================
//
inline void TNoteBookFrame::UpdateTab()
{
	TabCtl->SetPropFolder( PrevTabIndex );
	TabCtl->SetPropTabBevelSize(1);
	TabCtl->SetPropTabFillColor( GetSysColor( COLOR_BTNFACE ));

	TabCtl->SetPropFolder( TabIndex );
	TabCtl->SetPropTabBevelSize(2);
	TabCtl->SetPropTabFillColor( GetSysColor( COLOR_WINDOW ));
}

