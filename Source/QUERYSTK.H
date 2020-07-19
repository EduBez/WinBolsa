//-------------------------------------------//
//                                           //
//    QUERYSTK .H                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _QUERYSTOCK_H
	#define _QUERYSTOCK_H

#include <owl\combobox.h>

#include "centrdlg.h"
#include "globals.h"
#include "ownerdrw.h"


/*-----------------------------------*
 *       TQryStkTransferStruct       *
 *-----------------------------------*/

struct TQryStkTransferStruct {

	TQryStkTransferStruct();

	char CodCia[ MAXLEN_CODCIA ];
	TComboBoxData Tipo;

	char Corretora[ MAXLEN_CORRETORA ];
	TComboBoxData D, B, S;

	char DtBolsaINI[ MAXLEN_DTBOLSA ];
	char DtBolsaFIM[ MAXLEN_DTBOLSA ];

	uint16 Vista,
			 Fracao,
			 Termo_30,
			 Termo_60,
			 Termo_90,
			 Termo_120,
			 Termo_150,
			 Termo_180;

	TComboBoxData CompraVenda,
					  MesVenc,
					  Serie,
					  Futuro;

	TListBoxData StkList;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *         TQueryStockDialog         *
 *-----------------------------------*/

class TQueryStockDialog : public TAutoCenterDialog
{
	public :
		TQueryStockDialog( TWindow* parent, TResId ResId, GARQ_TYPE garq,
								 string (*QStr)[], TModule* module = 0 );

		void SetupWindow();
		void CleanupWindow();
		void CmOk();

	protected :
		// WM_COMMAND messages event handlers
		void CmMercAVista();
		void CmMercTermo();
		void CmMercOpcoes();
		void CmMercFuturo();

		void CmAdd();
		void CmRemove();
		void CmClear();

		DECLARE_RESPONSE_TABLE( TQueryStockDialog );

	private :
		void ShowControl( int SW );
		TRadioButton* GetFirstChecked( int start, int stop );

		void Expand( string& s );
		void Compress( string& s );

		bool Parse_TIPO( string& s, char* sbuff );
		void Parse_DBS( string& s, char* sbuff );

		void Parse_MERC_AVISTA( string& s );
		void Parse_MERC_TERMO( string& s );

		bool Parse_MERC_OPCOES( string& s, char* sbuff );
		bool Parse_MERC_FUTURO( string& s );

		bool Parse_DtBolsa( string& s );

		void EnableDateSelect();
		void HideSpeedButtons();

		TFont *StkLstFont;

		GARQ_TYPE GARQCmd;
		string (*QueryStr)[];

		int Button;

		TStatic   *CodCiaText;
		TEdit     *CodCia;

		TStatic   *TipoText;
		TComboBox *Tipo;

		TStatic   *CorretoraText;
		TEdit     *Corretora;

		TStatic *DividendoText,
				  *BonificacaoText,
				  *SubscricaoText;

		TComboBox *Dividendo,
					 *Bonificacao,
					 *Subscricao;

		TGroupBox *DireitosGroup,
					 *DtBolsaGroup;

		TStatic   *DtBolsaIniText,
					 *DtBolsaFimText;

		TEdit *DtBolsaIni,
				*DtBolsaFim;

		TRadioButton *Vista,
						 *Fracao;

		TRadioButton *Termo_30,
						 *Termo_60,
						 *Termo_90,
						 *Termo_120,
						 *Termo_150,
						 *Termo_180;

		TComboBox *CompraVenda,
					 *MesVenc,
					 *Serie;

		TComboBox *Futuro;
		TListBox  *StockList;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *         TQueryStockCombine        *
 *-----------------------------------*/

class TQueryStockCombine : public TAutoCenterDialog
{
	public :
		TQueryStockCombine( TWindow* parent, TResId ResId, int* CombineType,
								  TModule* module = 0 );
		void CmOk();
		void SetupWindow();

	protected :
		DECLARE_RESPONSE_TABLE( TQueryStockCombine );

	private :
		int* combine;
		TRadioButton *Radio_1,
						 *Radio_2,
						 *Radio_3,
						 *Radio_4,
						 *Radio_5;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *         Function Prototypes       *
 *-----------------------------------*/

bool IsThisRadioChecked( TWindow* p, void* param );


#endif   // _QUERYSTOCK_H

