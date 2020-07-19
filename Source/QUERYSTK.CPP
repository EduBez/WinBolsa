//-------------------------------------------//
//                                           //
//    QUERYSTK .CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include <classlib\date.h>

#include <owl/groupbox.h>
#include <owl/validate.h>

#include "querystk.h"


//--------------------------------------------//
//                  Local Data                //
//--------------------------------------------//

struct tag_QryStkMonths {
	char om;
	char *fm;
	char *month;

} QryStkMonths[] = {

	{ {'A'}, { "RJR" }, { "janeiro"   } },
	{ {'B'}, { "RFR" }, { "fevereiro" } },
	{ {'C'}, { "RMR" }, { "março"     } },
	{ {'D'}, { "RAB" }, { "abril"     } },
	{ {'E'}, { "RMI" }, { "maio"      } },
	{ {'F'}, { "RJN" }, { "junho"     } },
	{ {'G'}, { "RJL" }, { "julho"     } },
	{ {'H'}, { "RAG" }, { "agosto"    } },
	{ {'I'}, { "RST" }, { "setembro"  } },
	{ {'J'}, { "ROT" }, { "outubro"   } },
	{ {'K'}, { "RNV" }, { "novembro"  } },
	{ {'L'}, { "RDZ" }, { "dezembro"  } },
	{ { 0 }, {   0   }, {     0       } },
};

TQryStkTransferStruct TB_QryStk;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQryStkTransferStruct
//                        CONSTRUCTOR
//    ===============================
//
TQryStkTransferStruct::TQryStkTransferStruct()
{
	Tipo.AddString("AN");	Tipo.AddString("EH");	Tipo.AddString("OP");
	Tipo.AddString("AR");	Tipo.AddString("EN");	Tipo.AddString("OS");
	Tipo.AddString("AS");	Tipo.AddString("EP");	Tipo.AddString("PA");
	Tipo.AddString("BN");	Tipo.AddString("ER");	Tipo.AddString("PB");
	Tipo.AddString("BE");	Tipo.AddString("ES");	Tipo.AddString("PC");
	Tipo.AddString("BP");	Tipo.AddString("FN");	Tipo.AddString("PD");
	Tipo.AddString("BR");	Tipo.AddString("FR");	Tipo.AddString("PE");
	Tipo.AddString("BS");	Tipo.AddString("FS");	Tipo.AddString("PN");
	Tipo.AddString("CI");	Tipo.AddString("GN");	Tipo.AddString("PP");
	Tipo.AddString("CN");	Tipo.AddString("GR");	Tipo.AddString("PS");
	Tipo.AddString("CR");	Tipo.AddString("GS");	Tipo.AddString("RA");
	Tipo.AddString("CS");	Tipo.AddString("HN");	Tipo.AddString("RB");
	Tipo.AddString("D ");	Tipo.AddString("HR");	Tipo.AddString("RC");
	Tipo.AddString("DC");	Tipo.AddString("HS");	Tipo.AddString("RD");
	Tipo.AddString("DB");	Tipo.AddString("NA");	Tipo.AddString("RE");
	Tipo.AddString("DN");	Tipo.AddString("NB");	Tipo.AddString("RN");
	Tipo.AddString("DR");	Tipo.AddString("NC");	Tipo.AddString("RP");
	Tipo.AddString("DS");	Tipo.AddString("ND");	Tipo.AddString("RS");
	Tipo.AddString("EA");	Tipo.AddString("NE");	Tipo.AddString("SA");
	Tipo.AddString("EB");	Tipo.AddString("NF");	Tipo.AddString("SB");
	Tipo.AddString("EC");	Tipo.AddString("NG");	Tipo.AddString("SC");
	Tipo.AddString("ED");	Tipo.AddString("NH");	Tipo.AddString("SD");
	Tipo.AddString("EE");	Tipo.AddString("OB");	Tipo.AddString("SE");
	Tipo.AddString("EF");	Tipo.AddString("OE");	Tipo.AddString("SF");
	Tipo.AddString("EG");	Tipo.AddString("ON");	Tipo.AddString("ZN");

	D.AddString( " " );
	D.AddString( "E" );
	D.AddString( "C" );
	D.AddString( "B" );

	B.AddString( " " );
	B.AddString( "E" );
	B.AddString( "C" );
	B.AddString( "B" );
	B.AddString( "R" );
	B.AddString( "G" );
	B.AddString( "H" );

	S.AddString( " " );
	S.AddString( "E" );
	S.AddString( "C" );
	S.AddString( "B" );
	S.AddString( "R" );
	S.AddString( "D" );

	Vista    = true;
	Termo_30 = true;

	CompraVenda.AddString( "C = compra" );
	CompraVenda.AddString( "V = venda"  );

	string s;
	for ( int j = 0; QryStkMonths[j].om; j++ )
	{
		s = QryStkMonths[j].om + string( " = " ) + string( QryStkMonths[j].month );
		MesVenc.AddString( s.c_str() );

		s = QryStkMonths[j].fm + string( " = " ) + string( QryStkMonths[j].month );
		Futuro .AddString( s.c_str() );
	}

	char sbuff[2] = "";
	for ( char n = 'A'; n <= 'Z'; n++ )
	{
		sbuff[0] = n; sbuff[1] = '\x0';
		Serie.AddString( sbuff );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TQueryStockDialog, TAutoCenterDialog )
	EV_COMMAND( IDC_MERCADO_AVISTA, CmMercAVista ),
	EV_COMMAND( IDC_MERCADO_TERMO,  CmMercTermo  ),
	EV_COMMAND( IDC_MERCADO_OPCOES, CmMercOpcoes ),
	EV_COMMAND( IDC_MERCADO_FUTURO, CmMercFuturo ),
	EV_COMMAND( IDC_ADD,            CmAdd        ),
	EV_COMMAND( IDC_REMOVE,         CmRemove     ),
	EV_COMMAND( IDC_CLEAR,          CmClear      ),
	EV_COMMAND( IDOK,               CmOk         ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                        CONSTRUCTOR
//    ===============================
//
TQueryStockDialog::TQueryStockDialog( TWindow* parent, TResId ResId,
												  GARQ_TYPE garq, string (*QStr)[],
												  TModule* module )

												  : TAutoCenterDialog( parent, ResId, module )
{
	SetTransferBuffer( &TB_QryStk );

	StkLstFont  = new TFont( "Courier New", 16 );
	GARQCmd     = garq;
	QueryStr    = QStr;
	Button      = IDC_MERCADO_AVISTA;

	new TODATipButton( this, IDC_MERCADO_AVISTA );
	new TODATipButton( this, IDC_MERCADO_TERMO  );
	new TODATipButton( this, IDC_MERCADO_OPCOES );
	new TODATipButton( this, IDC_MERCADO_FUTURO );

	CodCiaText = new TStatic( this, IDC_CODCIA_TEXT            );
	CodCia     = new TEdit( this, IDC_CODCIA, MAXLEN_CODCIA    );
	CodCia     ->SetValidator( new TPXPictureValidator( "*?" ) );

	TipoText      = new TStatic  ( this, IDC_TIPO_TEXT         );
	Tipo          = new TComboBox( this, IDC_TIPO, MAXLEN_TIPO );

	CorretoraText = new TStatic( this, IDC_CORRETORA_TEXT              );
	Corretora     = new TEdit  ( this, IDC_CORRETORA, MAXLEN_CORRETORA );
	Corretora     ->SetValidator( new TPXPictureValidator( "*#" ) );

	DireitosGroup = new TGroupBox( this, IDC_DIREITOS_GROUP );

	DividendoText   = new TStatic( this, IDC_DIVIDENDO_TEXT   );
	BonificacaoText = new TStatic( this, IDC_BONIFICACAO_TEXT );
	SubscricaoText  = new TStatic( this, IDC_SUBSCRICAO_TEXT  );

	Dividendo      = new TComboBox( this, IDC_DIVIDENDO,   MAXLEN_DBS );
	Bonificacao    = new TComboBox( this, IDC_BONIFICACAO, MAXLEN_DBS );
	Subscricao     = new TComboBox( this, IDC_SUBSCRICAO,  MAXLEN_DBS );

	DtBolsaGroup   = new TGroupBox( this, IDC_DT_BOLSA_GROUP );

	DtBolsaIniText = new TStatic  ( this, IDC_DT_BOLSA_INI_TEXT );
	DtBolsaFimText = new TStatic  ( this, IDC_DT_BOLSA_FIM_TEXT );

	DtBolsaIni  = new TEdit( this, IDC_MHDATEINPUT1, MAXLEN_DTBOLSA );
	DtBolsaIni  ->SetValidator( new TPXPictureValidator( "##/##/##", true ));

	DtBolsaFim  = new TEdit( this, IDC_MHDATEINPUT2, MAXLEN_DTBOLSA );
	DtBolsaFim  ->SetValidator( new TPXPictureValidator( "##/##/##", true ));

					  new TGroupBox(    this, IDC_GBX_AVISTA    );
	Vista       = new TRadioButton( this, IDC_AVISTA        );
	Fracao      = new TRadioButton( this, IDC_AVISTA_FRACAO );

					  new TGroupBox(    this, IDC_GBX_TERMO );
	Termo_30    = new TRadioButton( this, IDC_TERMO_30  );
	Termo_60    = new TRadioButton( this, IDC_TERMO_60  );
	Termo_90    = new TRadioButton( this, IDC_TERMO_90  );
	Termo_120   = new TRadioButton( this, IDC_TERMO_120 );
	Termo_150   = new TRadioButton( this, IDC_TERMO_150 );
	Termo_180   = new TRadioButton( this, IDC_TERMO_180 );

					  new TGroupBox( this, IDC_GBX_OPCOES                        );
					  new TStatic(   this, IDC_TEXT_OPERACAO                     );
	CompraVenda = new TComboBox( this, IDC_COMPRA_VENDA, MAXLEN_COMPRA_VENDA );
					  new TStatic(   this, IDC_TEXT_MESVENC                      );
	MesVenc     = new TComboBox( this, IDC_MESVENC,      MAXLEN_MES          );
					  new TStatic(   this, IDC_TEXT_SERIE                        );
	Serie       = new TComboBox( this, IDC_SERIE,        MAXLEN_SERIE        );

					  new TGroupBox( this, IDC_GBX_FUTURO                 );
					  new TStatic(   this, IDC_TEXT_FUTURO                );
	Futuro      = new TComboBox( this, IDC_FUTURO_MESVENC, MAXLEN_MES );

	StockList   = new TListBox(  this, IDC_STOCKLIST );

	new TODAButton( this, IDC_ADD    );
	new TODAButton( this, IDC_REMOVE );
	new TODAButton( this, IDC_CLEAR  );

	new TODAButton( this, IDOK     );
	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                        SetupWindow
//    ===============================
//
void TQueryStockDialog::SetupWindow()
{
	TAutoCenterDialog::SetupWindow();
	TRect rc;

	StockList->GetClientRect( rc );
	StockList->SendMessage( LB_SETHORIZONTALEXTENT, rc.Width() + ( rc.Width() / 6 ), 0L );

	StockList->SendMessage( WM_SETFONT, (WPARAM(HFONT(*StkLstFont))), 0L );
	StockList->ClearList();

	if ( GARQCmd == GARQBIG )
		SetCaption( "Boletim Instantâneo - Código de títulos" );
	else
	{
		if ( GARQCmd == GARQBR )
			SetCaption( "Bol. de Fech. Rio - Código de Títulos" );

		else if ( GARQCmd == GARQBSG )
		{
			SetCaption( "Bol. de Fech. BOVESPA - Código de Títulos" );
			HideSpeedButtons();

			TipoText ->EnableWindow( false );
			Tipo     ->EnableWindow( false );
		}

		else if ( GARQCmd == GARQNEG )
		{
			SetCaption( "Relação de Negócios" );

			CorretoraText ->EnableWindow( true );
			Corretora     ->EnableWindow( true );
		}

		else if ( GARQCmd == GARQHIS )
		{
			SetCaption( "Séries Históricas de Ações" );
			EnableDateSelect();
		}

		else if ( GARQCmd == GARQIND )
		{
			SetCaption( "Séries Históricas de Índices" );

			EnableDateSelect();
			HideSpeedButtons();

			CodCiaText ->SetText( "&Setor" );
			TipoText   ->EnableWindow( false );
			Tipo       ->EnableWindow( false );
		}

		DireitosGroup   ->EnableWindow( false );

		DividendoText   ->EnableWindow( false );
		Dividendo       ->EnableWindow( false );

		BonificacaoText ->EnableWindow( false );
		Bonificacao     ->EnableWindow( false );

		SubscricaoText  ->EnableWindow( false );
		Subscricao      ->EnableWindow( false );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                      CleanupWindow
//    ===============================
//
void TQueryStockDialog::CleanupWindow()
{
	delete StkLstFont;
	TAutoCenterDialog::CleanupWindow();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                               CmOk
//    ===============================
//
void TQueryStockDialog::CmOk()
{
	if ( StockList->GetCount() > 0 )
	{
		char sbuff[32];

		for ( int i = 0; i < MAXSTOCKLISTSIZE; i++ )
		{
			memset( sbuff, '\x0', sizeof( sbuff ) );
			StockList->GetString( sbuff, i );

			if ( strlen( sbuff ) > 0 )
			{
				string s2, s1 = string( sbuff );

				if ( GARQCmd != GARQBSG && GARQCmd != GARQIND && GARQCmd != GARQNEG )
					Compress( s1 );

				if ( GARQCmd == GARQBR )
					s2 = "GARQBRG" + s1 + string( '\r' );

				else if ( GARQCmd == GARQBSG )
					s2 = "GARQBSG" + s1 + string( '\r' );

				else if ( GARQCmd == GARQBIG )
					s2 = "GARQBIG" + s1 + string( '\r' );

				else if ( GARQCmd == GARQNEG )
					s2 = "GARQNEG" + s1 + string( '\r' );

				else if ( GARQCmd == GARQHIS )
					s2 = "GARQHIS" + s1 + string( '\r' );

				else if ( GARQCmd == GARQIND )
					s2 = "GARQIND" + s1 + string( '\r' );

				*( *QueryStr + i ) = s2;
			}
			else
				*( *QueryStr + i ) = "";
		}
		TAutoCenterDialog::CmOk();
	}
	else
		MessageBox( "Lista de seleção se encontra vazia", "WinBolsa® - Aviso",
                   MB_OK | MB_ICONEXCLAMATION );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                       CmMercAVista
//    ===============================
//
void TQueryStockDialog::CmMercAVista()
{
	ShowControl( SW_HIDE );
	Button = IDC_MERCADO_AVISTA;
	ShowControl( SW_SHOWNORMAL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                        CmMercTermo
//    ===============================
//
void TQueryStockDialog::CmMercTermo()
{
	ShowControl( SW_HIDE );
	Button = IDC_MERCADO_TERMO;
	ShowControl( SW_SHOWNORMAL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                       CmMercOpcoes
//    ===============================
//
void TQueryStockDialog::CmMercOpcoes()
{
	ShowControl( SW_HIDE );
	Button = IDC_MERCADO_OPCOES;
	ShowControl( SW_SHOWNORMAL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                       CmMercFuturo
//    ===============================
//
void TQueryStockDialog::CmMercFuturo()
{
	ShowControl( SW_HIDE );
	Button = IDC_MERCADO_FUTURO;
	ShowControl( SW_SHOWNORMAL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                              CmAdd
//    ===============================
//
void TQueryStockDialog::CmAdd()
{
	char sbuff[ MAXLEN_MES ] = "";
	string s;
	bool ParseError = false;

	if ( StockList->GetCount() < MAXSTOCKLISTSIZE )
	{
		if ( GARQCmd == GARQNEG )
		{
			int i = 0;

			if ( TQueryStockCombine( this, QueryStockCombine, &i ).Execute() == IDOK )
			{
				if ( i == 0 || i == 1 || i == 2 || i == 3 )
				{
					if ( CodCia->GetText( sbuff, MAXLEN_CODCIA ) )
						s = sbuff;
					else
					{
						MessageBox( "Código do Cia. deve ser preenchido", "WinBolsa® - Aviso",
										 MB_OK | MB_ICONEXCLAMATION );

						CodCia->SetFocus();
						return;
					}
				}

				if ( i == 0 || i == 1 || i == 2 || i == 3 )
					if ( Parse_TIPO( s, sbuff ))
						return;

				if ( i == 0 || i == 1 )
					switch( Button )
					{
						case IDC_MERCADO_AVISTA :
							Parse_MERC_AVISTA( s );
							break;

						case IDC_MERCADO_TERMO  :
							Parse_MERC_TERMO( s );
							break;

						case IDC_MERCADO_OPCOES :
							if ( Parse_MERC_OPCOES( s, sbuff ))
								ParseError = true;

							break;

						case IDC_MERCADO_FUTURO :
							if ( Parse_MERC_FUTURO( s ))
								ParseError = true;

							break;
					}

				if ( i == 0 || i == 2 || i == 4 )
				{
					if ( Corretora->GetText( sbuff, MAXLEN_CORRETORA ) )
						s += sbuff;
					else
					{
						MessageBox( "Corretora deve ser preenchido", "WinBolsa® - Aviso",
										 MB_OK | MB_ICONEXCLAMATION );

						Corretora->SetFocus();
						return;
					}
				}

				if ( !ParseError )
				{
					StockList->SetSelIndex( StockList->AddString( s.c_str() ) );
					CodCia->SetFocus();
				}
			}
		}

		else
		{
			if ( CodCia->GetText( sbuff, MAXLEN_CODCIA ) )
			{
				if ( GARQCmd != GARQBSG )
				{
					if ( GARQCmd != GARQIND )
					{
						if ( Parse_TIPO( s, sbuff ))
							return;
					}
					else
						s = sbuff;

					if ( GARQCmd == GARQBIG )
						Parse_DBS ( s, sbuff );

					if ( GARQCmd != GARQIND )
						switch( Button )
						{
							case IDC_MERCADO_AVISTA :
								Parse_MERC_AVISTA( s );
								break;

							case IDC_MERCADO_TERMO  :
								Parse_MERC_TERMO( s );
								break;

							case IDC_MERCADO_OPCOES :
								if ( Parse_MERC_OPCOES( s, sbuff ))
									ParseError = true;

								break;

							case IDC_MERCADO_FUTURO :
								if ( Parse_MERC_FUTURO( s ))
									ParseError = true;

								break;
						}

					if ( GARQCmd == GARQHIS )
						if ( Parse_DtBolsa( s ))
							ParseError = true;

					if ( GARQCmd == GARQIND )
					{
						char v[ MAXLEN_DTBOLSA ] = "";

						if ( DtBolsaIni->GetText( v, MAXLEN_DTBOLSA ) &&
							  DtBolsaIni->GetText( v, MAXLEN_DTBOLSA ) )

							if ( Parse_DtBolsa( s ))
								ParseError = true;
					}
				}
				else
					s = sbuff;

				if ( !ParseError )
				{
					if ( GARQCmd != GARQBSG && GARQCmd != GARQIND )
						Expand( s );

					StockList->SetSelIndex( StockList->AddString( s.c_str() ) );
					CodCia->SetFocus();
				}
			}
			else
			{
				MessageBox( "Código do Cia. (ou Setor) deve ser preenchido", "WinBolsa® - Aviso",
								 MB_OK | MB_ICONEXCLAMATION );
				CodCia->SetFocus();
			}
		}
	}
	else
		MessageBox( "Limite de 10 seleções atingido", "WinBolsa® - Aviso",
						 MB_OK | MB_ICONEXCLAMATION );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                           CmRemove
//    ===============================
//
void TQueryStockDialog::CmRemove()
{
	int i = StockList->GetSelIndex();

	if ( i >= 0 )
	{
		StockList->DeleteString(i);
		StockList->SetSelIndex( i > 0 ? i-1 : 0 );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                            CmClear
//    ===============================
//
void TQueryStockDialog::CmClear()
{
	if ( StockList->GetCount() > 0 )
		if ( MessageBox( "Remover todos os títulos selecionados ?", "WinBolsa® - Aviso",
                        MB_YESNO | MB_ICONQUESTION ) == IDYES )
			StockList->ClearList();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                        ShowControl
//    ===============================
//
void TQueryStockDialog::ShowControl( int SW )
{
	register int Id;

	switch( Button )
	{
		case IDC_MERCADO_AVISTA :
			for ( Id = IDC_GBX_AVISTA; Id <= IDC_AVISTA_FRACAO; Id++ )
				ChildWithId( Id )->Show( SW );
			break;

		case IDC_MERCADO_TERMO  :
			for ( Id = IDC_GBX_TERMO; Id <= IDC_TERMO_180 ; Id++ )
				ChildWithId( Id )->Show( SW );
			break;

		case IDC_MERCADO_OPCOES :
			for ( Id = IDC_GBX_OPCOES; Id <= IDC_SERIE; Id++ )
				ChildWithId( Id )->Show( SW );
			break;

		case IDC_MERCADO_FUTURO :
			for ( Id = IDC_GBX_FUTURO; Id <= IDC_FUTURO_MESVENC; Id++ )
				ChildWithId( Id )->Show( SW );
			break;
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                    GetFirstChecked
//    ===============================
//
TRadioButton* TQueryStockDialog::GetFirstChecked( int start, int stop )
{
	DWORD dw = MAKELONG(start,stop);
   return
      TYPESAFE_DOWNCAST
         ( FirstThat( (TCondFunc)IsThisRadioChecked, (void*)&dw ), TRadioButton );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//                 IsThisRadioChecked
//    ===============================
//
bool IsThisRadioChecked( TWindow* p, void* param )
{
   TRadioButton* Child = TYPESAFE_DOWNCAST( p, TRadioButton);
   if (Child)
   {
      int Id = Child->GetId();
      int tp = LOWORD( *((DWORD*)param) );
      int bt = HIWORD( *((DWORD*)param) );

      if ( Id >= tp && Id <= bt )
         return Child->GetCheck() == BF_CHECKED;
   }
	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                             Expand
//    ===============================
//
void TQueryStockDialog::Expand( string& s )
{
	s.insert(  4, " " );
	s.insert(  7, " " );
	s.insert( 11, " " );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                           Compress
//    ===============================
//
void TQueryStockDialog::Compress( string& s )
{
	s.remove( 11, 1 );
	s.remove(  7, 1 );
	s.remove(  4, 1 );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                         Parse_TIPO
//    ===============================
//
bool TQueryStockDialog::Parse_TIPO( string& s, char* sbuff )
{
	s = sbuff;

	if ( strlen( s.c_str() ) < MAXLEN_CODCIA-1 ) // Verify string size
	{
		for ( register int n = 0; n < MAXLEN_CODCIA-1; n++ )
			s += " ";                              // Adjust padding with spaces
		s = s.substr( 0, MAXLEN_CODCIA-1 );       // TRIM trailing blanks
	}

	if ( Tipo->GetText( sbuff, MAXLEN_TIPO ) )
		s += sbuff;

	else
	{
		MessageBox( "Tipo do título deve ser preenchido", "WinBolsa® - Aviso",
						 MB_OK | MB_ICONEXCLAMATION );

		Tipo->SetFocus();
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                          Parse_DBS
//    ===============================
//
void TQueryStockDialog::Parse_DBS( string& s, char* sbuff )
{
	int pos;

	pos = Dividendo->GetSelIndex();
   if ( pos == -1 )
   	s += " ";

   else {
		Dividendo->GetString( sbuff, pos );
		s += sbuff;
   }

	pos = Bonificacao->GetSelIndex();
   if ( pos == -1 )
   	s += " ";

   else {
		Bonificacao->GetString( sbuff, pos );
		s += sbuff;
   }

	pos = Subscricao->GetSelIndex();
   if ( pos == -1 )
   	s += " ";

   else {
		Subscricao->GetString( sbuff, pos );
		s += sbuff;
   }
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                  Parse_MERC_AVISTA
//    ===============================
//
void TQueryStockDialog::Parse_MERC_AVISTA( string& s )
{
	TRadioButton* RadioBtn;
	int Id;

	RadioBtn = GetFirstChecked( IDC_AVISTA, IDC_AVISTA_FRACAO );

	if ( RadioBtn )
		Id = RadioBtn->GetId();

   switch (Id)
   {
      case IDC_AVISTA :
         s += "VST"; break;

      case IDC_AVISTA_FRACAO :
         s += "FRC"; break;
   }
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                   Parse_MERC_TERMO
//    ===============================
//
void TQueryStockDialog::Parse_MERC_TERMO( string& s )
{
	TRadioButton* RadioBtn;
	int Id;

	RadioBtn = GetFirstChecked( IDC_TERMO_30, IDC_TERMO_180 );

	if ( RadioBtn )
		Id = RadioBtn->GetId();

   switch (Id)
   {
      case IDC_TERMO_30 :
         s += "030"; break;

      case IDC_TERMO_60 :
         s += "060"; break;

      case IDC_TERMO_90 :
         s += "090"; break;

		case IDC_TERMO_120 :
         s += "120"; break;

      case IDC_TERMO_150 :
         s += "150"; break;

      case IDC_TERMO_180 :
         s += "180"; break;
   }
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                  Parse_MERC_OPCOES
//    ===============================
//
bool TQueryStockDialog::Parse_MERC_OPCOES( string& s, char* sbuff )
{
	int i = CompraVenda->GetSelIndex();

	if ( i == -1 ) {
		MessageBox( "Operação deve ser selecionada", "WinBolsa® - Aviso",
                   MB_OK | MB_ICONEXCLAMATION );

		CompraVenda->SetFocus();
   	return true;
   }
	else
		s += i == 0 ? 'C' : 'V';

	i = MesVenc->GetSelIndex();

	if ( i == -1 ) {
		MessageBox( "Mês de Vencimento deve ser selecionado", "WinBolsa® - Aviso",
                   MB_OK | MB_ICONEXCLAMATION );

		MesVenc->SetFocus();
   	return true;
   }
	else
		s += QryStkMonths[i].om;

	i = Serie->GetSelIndex();

	if ( i == -1 ) {
		MessageBox( "Série do Título deve ser selecionada", "WinBolsa® - Aviso",
						 MB_OK | MB_ICONEXCLAMATION );

		Serie->SetFocus();
		return true;
	}
	else
	{
		sbuff[0] = 'A'+i; sbuff[1] = '\x0';
		s += sbuff;
	}
   
   return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                  Parse_MERC_FUTURO
//    ===============================
//
bool TQueryStockDialog::Parse_MERC_FUTURO( string& s )
{
	int i = Futuro->GetSelIndex();

	if ( i == -1 ) {
		MessageBox( "Mês de Vencimento deve ser selecionado", "WinBolsa® - Aviso",
						 MB_OK | MB_ICONEXCLAMATION );

		Futuro->SetFocus();
		return true;
	}
	else
	{
		s += QryStkMonths[i].fm;
		return false;
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                      Parse_DtBolsa
//    ===============================
//
bool TQueryStockDialog::Parse_DtBolsa( string& s )
{
	TEdit* v[] = { DtBolsaIni,
						DtBolsaFim, 0 };

	char sbuff[ MAXLEN_DTBOLSA ] = "";
	int  n   = 0;
	bool ret = false;

	while ( v[n] )
	{
		if ( v[n]->GetText( sbuff, MAXLEN_DTBOLSA ) )
		{
			string DT, DD, MM, YY;

			DT = sbuff;
			YY = DT.substr( 6, 2 );
			MM = DT.substr( 3, 2 );
			DD = DT.substr( 0, 2 );

			DT = YY+MM+DD;
			unsigned Day, Month, Year;

			Day   = atoi( DD.c_str() );
			Month = atoi( MM.c_str() );
			Year  = atoi( YY.c_str() );

			TDate d( Day, Month, Year );

			if ( !d.IsValid() )
			{
				MessageBox( "Data de Bolsa inválida", "WinBolsa® - Aviso",
								 MB_OK | MB_ICONEXCLAMATION );

				v[n]->SetFocus(); ret = true; break;
			}
			s += DT;
			n++;
		}
		else
		{
			MessageBox( "Data de Bolsa deve ser preenchida", "WinBolsa® - Aviso",
							 MB_OK | MB_ICONEXCLAMATION );

			v[n]->SetFocus(); ret = true; break;
		}
	}
	return ret;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                   EnableDateSelect
//    ===============================
//
void TQueryStockDialog::EnableDateSelect()
{
	DtBolsaGroup    ->EnableWindow( true );

	DtBolsaIniText  ->EnableWindow( true );
	DtBolsaIni      ->EnableWindow( true );

	DtBolsaFimText  ->EnableWindow( true );
	DtBolsaFim      ->EnableWindow( true );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockDialog
//                   HideSpeedButtons
//    ===============================
//
void TQueryStockDialog::HideSpeedButtons()
{
	int v[] = { IDC_MERCADO_AVISTA, IDC_MERCADO_TERMO ,
					IDC_MERCADO_OPCOES, IDC_MERCADO_FUTURO, 0 };

	for ( int Id = 0; v[ Id ]; Id++ )
		ChildWithId( v[ Id ] )->Show( SW_HIDE );

	for ( int Id = IDC_GBX_AVISTA; Id <= IDC_AVISTA_FRACAO; Id++ )
		ChildWithId( Id )->Show( SW_HIDE );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockCombine
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE1( TQueryStockCombine, TAutoCenterDialog )
	EV_COMMAND( IDOK, CmOk ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockCombine
//                        CONSTRUCTOR
//    ===============================
//
TQueryStockCombine::TQueryStockCombine( TWindow* parent, TResId ResId,
													 int* CombineType, TModule* module )

						  : TAutoCenterDialog( parent, ResId, module )
{
	combine = CombineType;

	Radio_1 = new TRadioButton( this, IDC_RADIOBUTTON5 );
	Radio_2 = new TRadioButton( this, IDC_RADIOBUTTON6 );
	Radio_3 = new TRadioButton( this, IDC_RADIOBUTTON7 );
	Radio_4 = new TRadioButton( this, IDC_RADIOBUTTON8 );
	Radio_5 = new TRadioButton( this, IDC_RADIOBUTTON9 );

	new TODAButton( this, IDOK     );
	new TODAButton( this, IDCANCEL );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockCombine
//                        SetupWindow
//    ===============================
//
void TQueryStockCombine::SetupWindow()
{
	TAutoCenterDialog::SetupWindow();

	Radio_1->SetCheck( BF_CHECKED );
	Radio_1->SetFocus();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TQueryStockCombine
//                               CmOk
//    ===============================
//
void TQueryStockCombine::CmOk()
{
	TRadioButton* v[] = { Radio_1, Radio_2, Radio_3, Radio_4, Radio_5 };

	for ( int i = 0; i < 5; i++ )
		if ( v[i]->GetCheck() == BF_CHECKED )
		{
			*combine = i;
			break;
		}

	TAutoCenterDialog::CmOk();
}

