//-------------------------------------------//
//                                           //
//    TABLEDV. H                             //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _TABLEDV_H
	#define _TABLEDV_H

#include <owl\doctpl.h>
#include <owl\docview.h>

#include "browse.h"
#include "centrdlg.h"
#include "globals.h"
#include "label.h"
#include "ownerdrw.h"


/*-----------------------------------*
 *           TFileNewDialog          *
 *-----------------------------------*/

class TFileNewDialog : public TAutoCenterDialog
{
	public :
		TFileNewDialog( TWindow* parent, TResId resid, TModule* module = 0 );
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *           TTableDocument          *
 *-----------------------------------*/

class TTableDocument : public TDocument
{
	public :
		TTableDocument( TDocument* parent = 0 );
		~TTableDocument();

		// Implement virtual methods of TDocument
		bool CanClose();
		bool Close();
		bool Open( int mode, const char far* path = 0 );

		bool Commit( bool force = false );
		bool Revert( bool clear = false );

		bool AppendData( string& INdata );
		void UpdateView();

		GARQ_TYPE GetTableType() { return TableType; }

	private :
		bool AppendStart( const char* v[] );
		bool IsValidField( Field4& field, char* str );

		bool CopyIndex();
		bool CopyFile( char* INFile, char* OUTFile );
		bool CopyMemo();

		bool CreateTable( int type );
		void CloseTable();

		void EraseTmpFile();
		bool Error( bool CommitError = false );

		void ExtractStockCode( string& INdata );
		bool FindCtrlDigit( string& INdata, size_t cdp, size_t cdp_2 = 0 );

		bool MatchTableType( GARQ_TYPE& type );

		string DocFileName,
				 DocName;

		string	abe ,	//  Abertura
					bole, //  Boletim parcial ou total
					bols, //  Bolsa
               cdo , //  Codigo do papel
					cod ,	//  Codigo da empresa
					com ,	//  Melhor oferta de compra
					cto , //  Contrato
					cra , //  Corretora A
					crb , //  Corretora B
					date,	//  Data
					dir ,	//  Direitos
					esp , //  Especie
					evol, //  Evolucao
					fec ,	//  Fechamento
					hor ,	//  Hora
					iano, //  Indice ano
					ibvf, //  IBV de fechamento
					ibvm, //  IBV Medio de fechamento
					idr , //  Indicador de participacao
					imes, //  Indice mes
					ind ,	//  Indice de lucratividade
					mai , //  Maior
					maxd,	//  Maxima do dia
					maxi,	//  Maxima
					med ,	//  Media
					men , //  Menor
					mer ,	//  Mercado
					mind,	//  Minima do dia
					mini,	//  Minima
					nbr , //  Numero
					neg ,	//  Negociados
					ngc , //  Negocios
					nom ,	//  Nome da empresa
					num , //  Numero da empresa
					opc ,	//  Preco exercicio de opcoes
					osc ,	//  Oscilacao
					osc1,	//  Oscilacao
					pap , //  Especificacao do papel
					per ,	//  Percentual sobre volume negociado
					prca, //  Praca
					pri , //  Primeiro
					prz , //  Prazo
					qtd , //  Quantidade
					rea ,	//  Numero de negocios realizados
					regs, //  Numero de registros gravados
					set , //  Setor
					sin ,	//  Sinal
					sin1,	//  Sinal
					sit ,	//  Situacao da empresa
					ten , //  Tendencia
					tip ,	//  Tipo
               tpo , //  Tipo negocio
					ult ,	//  Ultima
					uni ,	//  Unidade monetaria
					vda ,	//  Melhor oferta de venda
					ven ,	//  Vencimento
					vol ;	//  Volume total negociado

		Tag4 tag;
		File4 IN,
				OUT;

		Data4 table;
		GARQ_TYPE TableType;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *            TTableView             *
 *-----------------------------------*/

class TTableView : public TView, public TLayoutWindow, public TVbxEventHandler
{
	public :
		TTableView( TTableDocument& doc, TWindow* parent = 0 );

		static LPCSTR StaticName() { return "Table View";   }
		LPCSTR GetViewName()       { return StaticName();   }
		TWindow* GetWindow()       { return (TWindow*)this; }

		bool CanClose();
		bool SetDocTitle( LPCSTR docname, int index );

		// 'TView' event handlers
		bool VnIsWindow( HWND hWnd );

		bool VnTableOpened( long table );
		bool VnTableSaved ( long table );
		bool VnSetViewType( long type  );
		bool VnViewUpdate ( long dummy );

		GARQ_TYPE GetViewType() { return ViewType; }

	private :
		DECLARE_RESPONSE_TABLE( TTableView );

		TBrowseCtl* GridVBX;
		TLabel* Label;

		TLayoutMetrics lm1,
							lm2;
		Data4* table;
		GARQ_TYPE ViewType;
};


#endif

