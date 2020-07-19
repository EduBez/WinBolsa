//-------------------------------------------//
//                                           //
//    QRYSTKM. CPP                           //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include <owl/groupbox.h>
#include <owl/validate.h>

#include "qrystkm.h"


/////////////////////////////////////
//    TQueryStockMAINDlg
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TQueryStockMAINDlg, TAutoCenterDialog )
	EV_CHILD_NOTIFY( IDC_TODOS_TITULOS, BN_CLICKED, HandleClickTitulos  ),
	EV_CHILD_NOTIFY( IDC_MERCADO_TODOS, BN_CLICKED, HandleClickMercado  ),
	EV_COMMAND( IDOK, CmOk ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockMAINDlg
//                        CONSTRUCTOR
//    ===============================
//
TQueryStockMAINDlg::TQueryStockMAINDlg( TWindow* parent, TResId resid,
													 GARQ_TYPE garq, string (*QStr)[], TModule* module )

													 : TAutoCenterDialog( parent, resid, module )
{
	GARQCmd  = garq;
	QueryStr = QStr;

	NTStatik     = new TStatic  ( this, IDC_NO_TITULOS_TEXT       );
	NTitles      = new TEdit    ( this, IDC_NO_TITULOS, MAXLEN_TRADEDTITLES );

	NTitles      ->SetValidator( new TPXPictureValidator( "*#" )  );
	AllTitles    = new TCheckBox( this, IDC_TODOS_TITULOS         );

	Merc_AVista  = new TCheckBox( this, IDC_MERCADO_AVISTA        );
	Merc_Fracao  = new TCheckBox( this, IDC_MERCADO_FRACAO        );
	Merc_Termo   = new TCheckBox( this, IDC_MERCADO_TERMO         );
	Merc_Compra  = new TCheckBox( this, IDC_MERCADO_OPCOES_COMPRA );
	Merc_Venda   = new TCheckBox( this, IDC_MERCADO_OPCOES_VENDA  );
	Merc_Futuro  = new TCheckBox( this, IDC_MERCADO_FUTURO        );
	Merc_All     = new TCheckBox( this, IDC_MERCADO_TODOS         );

	AOGroupBox   = new TGroupBox( this, IDC_ORDEM_ALFABETICA      );

	ILStatik     = new TStatic  ( this, IDC_LETRA_INICIAL_TEXT    );
	LetraIni     = new TEdit    ( this, IDC_LETRA_INICIAL, 2      );
	LetraIni     ->SetValidator( new TPXPictureValidator( "*?" )  );

	FLStatik     = new TStatic  ( this, IDC_LETRA_FINAL_TEXT      );
	LetraFim     = new TEdit    ( this, IDC_LETRA_FINAL  , 2      );
	LetraFim     ->SetValidator( new TPXPictureValidator( "*?" )  );

	new TODAButton( this, IDOK     );
	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockMAINDlg
//                        SetupWindow
//    ===============================
//
void TQueryStockMAINDlg::SetupWindow()
{
	TAutoCenterDialog::SetupWindow();

	if ( GARQCmd == GARQBRx )
	{
		SetCaption( "Bol. de Fech. Rio - Número de Títulos e Mercado" );

		Merc_Fracao->EnableWindow( true  );
		Merc_Venda ->EnableWindow( true  );
	}

	else if ( GARQCmd == GARQBRA )
	{
		SetCaption( "Bol. de Fech. Rio - Títulos em Ordem Alfabética de Empresa" );

		NTStatik   ->EnableWindow( false );
		NTitles    ->EnableWindow( false );
		AllTitles  ->EnableWindow( false );

		Merc_Fracao->EnableWindow( true  );
		Merc_Venda ->EnableWindow( true  );

		AOGroupBox ->EnableWindow( true  );
		ILStatik   ->EnableWindow( true  );

		LetraIni   ->EnableWindow( true  );
		FLStatik   ->EnableWindow( true  );
		LetraFim   ->EnableWindow( true  );
	}

	else if ( GARQCmd == GARQBSx )
		SetCaption( "Bol. de Fech. BOVESPA - Número de Títulos e Mercado" );

	else if ( GARQCmd == GARQBIG )
		SetCaption( "Bol. Inst. - Número de Títulos e Mercado" );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockMAINDlg
//                               CmOk
//    ===============================
//
void TQueryStockMAINDlg::CmOk()
{
	char sbuff[ MAXLEN_TRADEDTITLES ] = "";
	string s = "";
   int i;

	for ( i = 0; i < MAXSTOCKLISTSIZE; i++ )	// Always clear 'Request string
		*( *QueryStr + i ) = "";		  			// array' before making a request

	i = 0;									  			// Update index to QUERY LIST

	if ( GARQCmd == GARQBRA )
	{
		if ( !LetraIni->GetTextLen() )
		{
			MessageBox( "Letra Inicial deve ser especificada", "WinBolsa® - Aviso",
							 MB_OK | MB_ICONQUESTION );
			LetraIni->SetFocus();
			return;
		}

		if ( !LetraFim->GetTextLen() )
		{
			MessageBox( "Letra Final deve ser especificada", "WinBolsa® - Aviso",
							 MB_OK | MB_ICONQUESTION );
			LetraFim->SetFocus();
			return;
		}

		char LIni, LFim;

		LetraIni->GetText( sbuff, sizeof sbuff );
		LIni = sbuff[0];

		LetraFim->GetText( sbuff, sizeof sbuff );
		LFim = sbuff[0];

		if ( LIni > LFim )
		{
			MessageBox( "Letra Final deve ser maior que Letra Inicial", "WinBolsa® - Aviso",
							 MB_OK | MB_ICONQUESTION );
			LetraFim->SetFocus();
			return;
		}

		sbuff[0] = LIni; sbuff[1] = LFim; sbuff[3] = '\x0';
	}

	if ( AllTitles->GetCheck() == BF_UNCHECKED )
	{
		if ( NTitles->GetTextLen() )
		{
			NTitles->GetText( sbuff, sizeof sbuff );

			int n = atoi( sbuff );
			wsprintf( sbuff, "%03d", n );
		}

		else if ( GARQCmd != GARQBRA )
		{
			MessageBox( "Número de Títulos deve ser especificado", "WinBolsa® - Aviso",
							 MB_OK | MB_ICONQUESTION );
			NTitles->SetFocus();
			return;
		}
	}

	if ( Merc_All->GetCheck() == BF_UNCHECKED )
	{
		TCheckBox* Merc[] = { Merc_AVista, Merc_Fracao, Merc_Termo,
									 Merc_Compra, Merc_Venda , Merc_Futuro, 0 };
		bool flag = false;

		for ( int n = 0; Merc[n]; n++ )
		{
			if ( Merc[n]->GetCheck() == BF_CHECKED )
			{
				if ( !flag ) flag = true;

				if ( GARQCmd == GARQBRx )
				{
					switch ( n )
					{
						case 0 : s = "GARQBRV" ; break; /* AVista */
						case 1 : s = "GARQBRR" ; break; /* Fracao */
						case 2 : s = "GARQBRT" ; break; /* Termo  */
						case 3 : s = "GARQBRC" ; break; /* Compra */
						case 4 : s = "GARQBRP" ; break; /* Venda  */
						case 5 : s = "GARQBRF" ; break; /* Futuro */
					}
				}

				else if ( GARQCmd == GARQBRA )
				{
					switch ( n )
					{
						case 0 : s = "GARQBRAV" ; break; /* AVista */
						case 1 : s = "GARQBRAR" ; break; /* Fracao */
						case 2 : s = "GARQBRAT" ; break; /* Termo  */
						case 3 : s = "GARQBRAC" ; break; /* Compra */
						case 4 : s = "GARQBRAP" ; break; /* Venda  */
						case 5 : s = "GARQBRAF" ; break; /* Futuro */
					}
				}

				else if ( GARQCmd == GARQBSx )
				{
					switch ( n )
					{
						case 0 : s = "GARQBSV" ; break; /* AVista */
						case 2 : s = "GARQBST" ; break; /* Termo  */
						case 3 : s = "GARQBSC" ; break; /* Compra */
						case 5 : s = "GARQBSF" ; break; /* Futuro */
					}
				}

				else if ( GARQCmd == GARQBIG )
				{
					switch ( n )
					{
						case 0 : s = "GARQBIV" ; break; /* AVista */
						case 2 : s = "GARQBIT" ; break; /* Termo  */
						case 3 : s = "GARQBIO" ; break; /* Compra */
						case 4 : s = "GARQBIP" ; break; /* Venda  */
						case 5 : s = "GARQBIF" ; break; /* Futuro */
					}
				}
				*( *QueryStr + i++ ) = s + string( sbuff ) + string( '\r' );
			}
		}

		if ( !flag )
		{
			MessageBox( "Mercado deve ser especificado", "WinBolsa® - Aviso",
							MB_OK | MB_ICONQUESTION );

			Merc_AVista->SetFocus();
			return;
		}
	}

	else
	{
		if ( GARQCmd == GARQBRx )
			*( *QueryStr + i++ ) = "GARQBRG" + string( sbuff ) + string( '\r' );

		else if ( GARQCmd == GARQBRA )
		{
			char* v[] = { "GARQBRAV", "GARQBRAR", "GARQBRAT",
							  "GARQBRAC", "GARQBRAP", "GARQBRAF", 0 };

			for ( int n = 0; v[n]; n++ )
				*( *QueryStr + n ) = v[ n ] + string( sbuff ) + string( '\r' );
		}

		else if ( GARQCmd == GARQBSx )
		{
			char* v[] = { "GARQBSV", "GARQBST", "GARQBSC", "GARQBSF", 0 };

			for ( int n = 0; v[n]; n++ )
				*( *QueryStr + n ) = v[ n ] + string( sbuff ) + string( '\r' );
		}

		else if ( GARQCmd == GARQBIG )
			*( *QueryStr + i++ ) = "GARQBIG" + string( sbuff ) + string( '\r' );
	}

	TAutoCenterDialog::CmOk();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockMAINDlg
//                 HandleClickTitulos
//    ===============================
//
void TQueryStockMAINDlg::HandleClickTitulos()
{
	if ( AllTitles->GetCheck() == BF_CHECKED )
	{
		NTitles->SetText( "999" );
		NTitles->EnableWindow( false );
	}
	else
	{
		NTitles->SetText( "" );
		NTitles->EnableWindow( true );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockMAINDlg
//                 HandleClickMercado
//    ===============================
//
void TQueryStockMAINDlg::HandleClickMercado()
{
	uint check;
	bool b;

	TCheckBox* Merc[] = { Merc_AVista, Merc_Fracao, Merc_Termo,
								 Merc_Compra, Merc_Venda , Merc_Futuro, 0 };

	if ( Merc_All->GetCheck() == BF_CHECKED )
	{
		check = BF_CHECKED;
		b  = false;
	}
	else
	{
		check = BF_UNCHECKED;
		b  = true;
	}

	for ( int n = 0; Merc[n]; n++ )
	{
		if ( n == 1 && ( GARQCmd == GARQBIG || GARQCmd == GARQBSx ))
			continue;

		if ( n == 4 && GARQCmd == GARQBSx )
			continue;

		Merc[n]->SetCheck( check );
		Merc[n]->EnableWindow( b );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDays
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TQueryStockDays, TAutoCenterDialog )
	EV_COMMAND( IDOK, CmOk ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDays
//                        CONSTRUCTOR
//    ===============================
//
TQueryStockDays::TQueryStockDays( TWindow* parent, TResId resid, int* Day, TModule* module )
											 : TAutoCenterDialog( parent, resid, module )
{
	day = Day;

	Radio_D1 = new TRadioButton( this, IDC_RADIOBUTTON1 );
	Radio_D2 = new TRadioButton( this, IDC_RADIOBUTTON2 );
	Radio_D3 = new TRadioButton( this, IDC_RADIOBUTTON3 );
	Radio_D4 = new TRadioButton( this, IDC_RADIOBUTTON4 );

	new TODAButton( this, IDOK     );
	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDays
//                        SetupWindow
//    ===============================
//
void TQueryStockDays::SetupWindow()
{
	TAutoCenterDialog::SetupWindow();
	Radio_D1->SetCheck( BF_CHECKED );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    IsThisRadioButtonChecked
//    ===============================
//
bool IsThisRadioButtonChecked( TWindow* p, void* day )
{
   TRadioButton* v = TYPESAFE_DOWNCAST( p, TRadioButton);
   if (v && v->GetCheck() == BF_CHECKED )
   {
      *(int*)day = v->GetDlgCtrlID() - IDC_RADIOBUTTON;
      return true;
   }
	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDays
//                               CmOk
//    ===============================
//
void TQueryStockDays::CmOk()
{
	FirstThat( IsThisRadioButtonChecked, (void*)day );
	TAutoCenterDialog::CmOk();
}

