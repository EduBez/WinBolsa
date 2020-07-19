//-------------------------------------------//
//                                           //
//    DIAL .CPP                              //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "dial.h"
#include "globals.h"


//--------------------------------------------//
//                  Local Data                //
//--------------------------------------------//

struct tag_Msg {

	unsigned show;
	unsigned shrink;
	unsigned logged;
	char*    message;

} MsgLookup [] = {

  {{ 1 }, { 1 }, { 1 }, { "CONNECT 2400" }},					/* 0  */
  {{ 1 }, { 1 }, { 1 }, { "CONNECT 1200" }},             /* 1  */
  {{ 1 }, { 1 }, { 1 }, { "CONNECT"      }},             /* 2  */
  {{ 1 }, { 1 }, { 0 }, { "NO CARRIER"   }},             /* 3  */
  {{ 1 }, { 1 }, { 0 }, { "NO DIALTONE"  }},             /* 4  */
  {{ 1 }, { 1 }, { 0 }, { "BUSY"         }},             /* 5  */

  {{ 0 }, { 1 }, { 1 }, { "BVRJ"         }},             /* 6  */
  {{ 0 }, { 1 }, { 1 }, { "DISQUE"       }},             /* 7  */
  {{ 0 }, { 1 }, { 1 }, { "BOLSA"        }},             /* 8  */
  {{ 0 }, { 1 }, { 1 }, { "INFORME"      }},             /* 9  */
  {{ 0 }, { 1 }, { 1 }, { "SOLICITACAO"  }},             /* 10 */
  {{ 0 }, { 1 }, { 1 }, { "COMUNICACAO"  }},             /* 11 */

  {{ 0 }, { 1 }, { 1 }, { "CONSULTA INVALIDA"      }},   /* 12 */
  {{ 0 }, { 1 }, { 1 }, { "SOLICITACAO INVALIDA"   }},   /* 13 */

  {{ 1 }, { 1 }, { 0 }, { "SERVICO NAO DISPONIVEL" }},   /* 14 */
  {{ 1 }, { 1 }, { 0 }, { "CPU FORA DE SERVICO"    }},   /* 15 */
  {{ 1 }, { 1 }, { 0 }, { "TEMPO ESGOTADO"         }},   /* 16 */

  {{ 0 }, { 0 }, { 1 }, { "COM" }},                      /* 17 */
  {{ 0 }, { 0 }, { 0 }, { "MEN" }},                      /* 18 */
  {{ 0 }, { 0 }, { 0 }, { 0 }}                           /* 19 */
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TDialDialog, TAutoCenterDialog )
	EV_WM_COMMNOTIFY,
	EV_WM_TIMER,
	EV_MESSAGE( WM_DIAL, EvDial ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                        CONSTRUCTOR
//    ===============================
//
TDialDialog::TDialDialog( TWindow* parent, TResId resid, TModule* module )
								  : TAutoCenterDialog( parent, resid, module )
{
	DialStatus = new TListBox( this, IDC_DIALSTATUS );
	LedGauge   = new TGauge( this, "", IDC_LEDGAUGE, 0,0,0,0, true, 4 );

	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                        SetupWindow
//    ===============================
//
void TDialDialog::SetupWindow()
{
	TAutoCenterDialog::SetupWindow();
	SetupLedGauge();

	ComposeDialStr( DialStr );
	SetTimer( TIMER_DIAL_GAUGE,  TIMER_DIAL_GAUGE_TIMEOUT );

	// Enable 'WM_COMMNOTIFY' for this window
	::EnableCommNotification( __comm->GetCommId(), *this, 1024, 1024 );
	__rx_gauge->Show( SW_SHOW );

	PostMessage( WM_DIAL, 0, 0L );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                      CleanupWindow
//    ===============================
//
void TDialDialog::CleanupWindow()
{
	KillTimer( TIMER_DIAL_CONNECTED );
	KillTimer( TIMER_DIAL_GAUGE     );

	if ( !__is_attached )
	{
		__comm->HangUp();
		__rx_gauge->Show( SW_HIDE );
	}

	// Disable 'WM_COMMNOTIFY' for this window
	::EnableCommNotification( __comm->GetCommId(), NULL, -1, -1 );
	__rx_gauge->SetValue(0);

	TDialog::CleanupWindow();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                            EvTimer
//    ===============================
//
void TDialDialog::EvTimer( uint timerId )
{
	if ( timerId == TIMER_DIAL_GAUGE )
	{
		LedValue < 100 ? LedValue++ : LedValue = 0;
		LedGauge->SetValue( LedValue );
	}

	else if ( timerId == TIMER_DIAL_CONNECTED )
	{
		// When "TickCnt" is EVEN
		if ( TickCnt % 2L == 0L )
			__status_bar_slot_2->SetText(" ");
		else
		// When "TickCnt" is ODD
			__status_bar_slot_2->SetText( "CONECTADO" );

		MessageBeep(-1);

		if ( TickCnt++ >= DIAL_MAX_ELAPSED_TIME / 1.7 )
		{
			__status_bar_slot_2->SetText( "CONECTADO" );
			PostMessage( WM_CLOSE, 0, 0L );
		}
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                             EvDial
//    ===============================
//
LRESULT TDialDialog::EvDial( WPARAM wParam, LPARAM lParam )
{
	__rx_gauge->SetValue(0);

	GetApplication()->GetMainWindow()->Invalidate();
	GetApplication()->GetMainWindow()->UpdateWindow();

	size_t n = DialStr.find( '\r' );

	if (  n != NPOS )
		DialStr.put_at( n, ' ' );

	Display( "Discando..." );
	Display( DialStr.c_str(), false );

	TickCnt  = 0L;
	DialStr += '\r';
	InBuffer = "";

	__comm->SendATCommand( DialStr );
	return (LRESULT) 1;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                       EvCommNotify
//    ===============================
//
void TDialDialog::EvCommNotify( uint CommId, uint Notify )
{
	if ( !__is_attached )
	{
		::GetCommError( CommId, &comstat );
		__rx_gauge->SetValue( comstat.cbInQue );

		if ( Notify == CN_RECEIVE  )
		{
			int i = -1;
			string scrap;

			__comm->GetPropReceive( scrap );

			if ( scrap.is_null() )
				return;

			InBuffer += scrap;
			*__terminal << scrap;

			for ( int n = 0; MsgLookup [n].message; n++ )
			{
				if ( InBuffer.contains( MsgLookup [n].message ) )
				{
					if ( MsgLookup [n].shrink )
					{
						do {
							InBuffer = InBuffer.substr( InBuffer.find( MsgLookup
										  [n].message ) + strlen( MsgLookup [n].message ) );

						} while ( InBuffer.contains( MsgLookup [n].message ) );
					}

					i = n;
				}
			}

			if ( i != -1 )
			{
				if ( MsgLookup [i].show )
					Display( MsgLookup [i].message );

				if ( MsgLookup [i].logged )
				{
					if ( i >= /*CONNECT 2400*/ 0 && i <= /*CONNECT*/ 2 )
					{
						__comm->SetPropSend( string( '\r' ) );
						Display( "Negociando...", false );
					}

					if ( i >= /*BVRJ*/ 6 && i <= /*SOLICITACAO INVALIDA*/ 13 )
					{
						__comm->SetPropSend( MemberID );
						Display( "Enviando indentificação...", false );
					}

					if ( i == /*COM*/ 17 )
					{
						string v = InBuffer;
						size_t k = v.find_last_of( "COM" );

						v = v.substr( k + 1, 11 );
						size_t p = v.find( '&' );

						if ( p == 10 )
						{
							__is_attached = true;

							v = v.substr( 0, p );
							string s = "Tempo disponível (Seg): " + v;

							Display( "Participante aceito" );
							Display( s.c_str(), false );

							SetTimer( TIMER_DIAL_CONNECTED, TIMER_DIAL_CONNECTED_TIMEOUT );
						}
					}
				}

				else
				{
					if ( i == /*MEN*/ 18 )
					{
						size_t p1 = InBuffer.find( "MEN" );
						InBuffer = InBuffer.substr( p1 + 11 );

						size_t p2 = InBuffer.find( '&' );
						InBuffer = InBuffer.substr( 0, p2 );

						Display( InBuffer.c_str() );
					}

					if ( i == /*SERVICO NAO DISPONIVEL*/ 14 || i == /*CPU FORA DE SERVICO*/ 15 )
						PostMessage( WM_CLOSE, 0, 0L );
					else
					{
						__comm->HangUp();
						PostMessage( WM_DIAL, 0, 0L );
					}
				}
			}
		}

		if ( Notify == CN_EVENT )
			uint mask = ::GetCommEventMask( CommId, 0xFFFF );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                     ComposeDialStr
//    ===============================
//
void TDialDialog::ComposeDialStr( string& DialStr )
{
	MemberID  = "GCOM";
	MemberID += __notebook_tab_1.Id;
	MemberID += __notebook_tab_1.Passw + string( '\r' );

	if ( __notebook_tab_2.Pulse )
		DialStr = "ATDP";

	if ( __notebook_tab_2.Tone )
		DialStr = "ATDT";

	if ( __notebook_tab_2.UsePrefix == 1 )
		DialStr += __notebook_tab_2.Prefix + string( ',' );

	DialStr += __notebook_tab_1.Phone;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                            Display
//    ===============================
//
void TDialDialog::Display( const char* s, bool ClrList )
{
	if ( ClrList )
		DialStatus->ClearList();

	DialStatus->AddString( s );
	Repaint();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TDialDialog
//                      SetupLedGauge
//    ===============================
//
void TDialDialog::SetupLedGauge()
{
	TRect rc;
	DialStatus->GetWindowRect( rc );

	TPoint p( rc.left, rc.bottom );
	ScreenToClient( p );

	GetWindowRect( rc );
	LedGauge->MoveWindow( p.x, p.y + 13,( rc.right - rc.left ) - ( 2.5 * p.x ), 18 );

	LedValue = 0;
	LedGauge->SetRange( 0, 100 );
	LedGauge->SetLed( 3, 70 );

	LedGauge->SetValue(0);
	LedGauge->SetColor( ::GetSysColor( COLOR_HIGHLIGHT ));
}

