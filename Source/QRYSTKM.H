//-------------------------------------------//
//                                           //
//    QRYSTKM .H                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _QRYSTKM_H
	#define _QRYSTKM_H

#include "centrdlg.h"
#include "globals.h"
#include "ownerdrw.h"


/*-----------------------------------*
 *        TQueryStockMAINDlg         *
 *-----------------------------------*/

class TQueryStockMAINDlg : public TAutoCenterDialog
{
	public :
		TQueryStockMAINDlg( TWindow* parent, TResId resid,
								  GARQ_TYPE garq, string (*QStr)[], TModule* module = 0 );
		void SetupWindow();
		void CmOk();

	protected :
		// WM_COMMAND messages event handlers
		void HandleClickTitulos();
		void HandleClickMercado();

		DECLARE_RESPONSE_TABLE( TQueryStockMAINDlg );

	private :
		GARQ_TYPE GARQCmd;
		string (*QueryStr)[];

		TEdit *NTitles,
				*LetraIni,
				*LetraFim;

		TStatic *NTStatik,
				  *ILStatik,
				  *FLStatik;

		TGroupBox *AOGroupBox;

		TCheckBox *AllTitles,
					 *Merc_AVista,
					 *Merc_Fracao,
					 *Merc_Termo,
					 *Merc_Compra,
					 *Merc_Venda,
					 *Merc_Futuro,
					 *Merc_All;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *          TQueryStockDays          *
 *-----------------------------------*/

class TQueryStockDays: public TAutoCenterDialog
{
	public :
		TQueryStockDays( TWindow* parent, TResId resid, int* Day, TModule* module = 0 );

		void SetupWindow();
		void CmOk();

	protected :
		DECLARE_RESPONSE_TABLE( TQueryStockDays );

	private :
		int* day;

		TRadioButton *Radio_D1,
						 *Radio_D2,
						 *Radio_D3,
						 *Radio_D4;
};


#endif   // _QRYSTKM_H

