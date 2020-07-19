//-------------------------------------------//
//                                           //
//    WINBOLSA. H                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef  _WINBOLSA_H
	#define _WINBOLSA_H

#include <owl\controlg.h>
#include <owl\decmdifr.h>
#include <owl\docmanag.h>
#include <owl\printer.h>

#include "globals.h"
#include "notebook.h"
#include "querymdi.h"
#include "splash.h"
#include "tabledv.h"


class TDrvdMDIClient;


/*----------------------------------*
 *          TDrvdApp                *
 *----------------------------------*/

class TDrvdApp : public TApplication
{
	public :
		TDrvdApp( const char* name );
		~TDrvdApp();

		void InitMainWindow();
		bool CanClose();

	protected :
		// Doc/View Model Event handlers
		void EvNewView( TView& view );
		void EvCloseView( TView& view );

		// Command event handlers
		void CmFileNew();

		void CmTerminal();
		void CeTerminal( TCommandEnabler& ce );

		void CmConfig();
		void CeConfig( TCommandEnabler& ce );

		void CmBoletimFechamentoRioTodoMestre()      { CreateNewDoc( GARQBOR1 ); }
		void CmBoletimFechamentoRioTodoIndice()      { CreateNewDoc( GARQBOR2 ); }
		void CmBoletimFechamentoRioTodoTotaisSENN()  { CreateNewDoc( GARQBOR3 ); }
		void CmBoletimFechamentoRioTodoIndicesSENN() { CreateNewDoc( GARQBOR4 ); }
		void CmBoletimFechamentoRioTodoCotacoes()    { CreateNewDoc( GARQBOR5 ); }

		void CmBoletimFechamentoRioMercTit()         { CreateNewDoc( GARQBR  ); }
		void CmBoletimFechamentoRioIndices()         { CreateNewDoc( GARQBRI ); }

		void CmBoletimFechamentoRio4ultMestre()      { CreateNewDoc( GARQBFR1 ); }
		void CmBoletimFechamentoRio4ultIndice()      { CreateNewDoc( GARQBFR2 ); }
		void CmBoletimFechamentoRio4ultCotacoes()    { CreateNewDoc( GARQBFR3 ); }

		void CmBoletimFechamentoBovespaMercTit()     { CreateNewDoc( GARQBS );  }
		void CmBoletimFechamentoBovespaIndices()     { CreateNewDoc( GARQBSI ); }

		void CmBoletimFechamentoBovespa4ultMestre()  { CreateNewDoc( GARQBAS1 ); }
		void CmBoletimFechamentoBovespa4ultCotacoes(){ CreateNewDoc( GARQBAS2 ); }

		void CmBoletimFechamentoDatasRio()           { CreateNewDoc( GARQBRJDATA ); }
		void CmBoletimFechamentoDatasSaoPaulo()      { CreateNewDoc( GARQBSPDATA ); }

		void CmBoletimInstantaneo()                  { CreateNewDoc( GARQBIG ); }
		void CmRelacaoDeNegocios()                   { CreateNewDoc( GARQNEG ); }

		void CmSeriesHistoricasAcoes()               { CreateNewDoc( GARQHIS ); }
		void CmSeriesHistoricasIndices()             { CreateNewDoc( GARQIND ); }

		DECLARE_RESPONSE_TABLE( TDrvdApp );

	private :
		inline void CreateNewDoc( GARQ_TYPE garq ) {
			__garq = garq;
			GetDocManager()->CreateAnyDoc( 0, dtNewDoc );
		}

		void ReadIniPrivateFile();
		void WriteIniPrivateFile();

		void PreEncode( char* str, char src, char dest, int len );
		void Encode( bool IsToEncode );

		const char* AppName;      // Name of the application

      TPointer<TSplashDialog> oSplashDlg; // 'Splash' dialog pointer
		TNoteBookFrame *NoteBookFrame;      // 'NoteBook' setup dialog

		TDrvdMDIClient* Client;   // Pointer to the MDI client object
		TQueryMDIChild* Child;    // Pointer to the MDI child window

		int EnumMDIChildWindows;  // Number of active MDI chid windows
		TRect TerminalRect;       // Terminal Window coordinates

		bool checked;             // Check mark of the Terminal Window menu
};

//----------------------------------------------------------------------------//

/*----------------------------------*
 *        TDrvdDecoratedFrame       *
 *----------------------------------*/

class TDrvdDecoratedFrame : public TDecoratedMDIFrame
{
	public :
		TDrvdDecoratedFrame( const char far* title, TResId menuResId,
									TMDIClient& clientWnd = *new TMDIClient,
									bool trackMenuSelection = true, TModule* module = 0 );

		~TDrvdDecoratedFrame();

		void SetupWindow();
		bool CanClose();

		void VCRShow( bool show );

	protected :
		// Standard / user windows messages event handlers
		void EvCommNotify( uint CommId, uint Notify );
		void EvMove( TPoint& clientOrigin );
		void EvSize( uint sizeType, TSize& size );

		LRESULT EvInitializeComm( WPARAM wParam, LPARAM lParam );
		LRESULT EvRequest( WPARAM wParam, LPARAM lParam );

		DECLARE_RESPONSE_TABLE( TDrvdDecoratedFrame );

	private :
		// WM_COMMAND messages event handlers
		void CmStockDial();
		void CeStockDial( TCommandEnabler& ce );
		void CmStockHangUp();

		void Cm_GARQ_BOR();

		void Cm_GARQ_BR();
		void Cm_GARQ_BRx();
		void Cm_GARQ_BRA();
		void Cm_GARQ_BRG();

		void Cm_GARQ_BRI();
		void Cm_GARQ_BFR();

		void Cm_GARQ_BS();
		void Cm_GARQ_BSx();
		void Cm_GARQ_BSG();

		void Cm_GARQ_BSI();
		void Cm_GARQ_BAS();

		void Cm_GARQ_BRJDATA();
		void Cm_GARQ_BSPDATA();

		void Cm_GARQ_BIG();
		void Cm_GARQ_BIG_Negociados();
		void Cm_GARQ_BIG_Especificos();

		void Cm_GARQ_NEG();
		void Cm_GARQ_HIS();
		void Cm_GARQ_IND();

		void Ce_GARQ( TCommandEnabler& ce );

		void CmFilePrint();
		void CeFilePrint( TCommandEnabler& ce );

		void CmFilePrinterSetup();

		void CmHelpIndex();
		void CmHelpHelp();

		void CmAbout();

		bool ExecStockDlg( GARQ_TYPE garq );
		bool GetActiveDoc();

		bool IsValidComm();
		bool OpenCapture();

		void AppendFromCapture();
		void Connect();
		void SpeedButtonMenu( uint cmd, uint id );

		void PostRequest();
		void Request();

		inline void ClearQuery() { scrap = ""; RQST_Buff = ""; StkLstIndex = 0;
											__is_query_running = false; }

		void InsertRec( string& line, long& rec, long& err, size_t A, size_t B );
		void XtractRec( string& line, long& rec, long& err );
		void XtractTot( string& line, long& tot );

		int IsAMultRecTable();
		bool IsAMultRecQuery();

		void CountMultRec( string& s, long& count );
		inline void AdjustMultRecFieldLength( string& s );

		inline void AssignNewQuery( const char* s );

		TSize FrameWndSize;                  // Tracks last saved window position
		TTableDocument* doc;                 // Pointer to the current document

		string RQST_Str[ MAXSTOCKLISTSIZE ], // Request string array
				 RQST_Buff,							 // Request buffer ( stacked data )
				 scrap;								 // Scrap receive buffer

		int StkLstIndex;							 // Index to QUERY LIST
		COMSTAT comstat;							 // 'COMSTAT' struct for 'GetCommError'

      TFlyByTIPButton* aVCR[6];            // VCR gadget buttons
      TSeparatorGadget* oSpc;              // Separator gadget
};

//----------------------------------------------------------------------------//

/*----------------------------------*
 *          TDrvdMDIClient          *
 *----------------------------------*/

class TDrvdMDIClient : public TMDIClient
{
	public :
		TDrvdMDIClient( TModule* module = 0 )
							 : TMDIClient( module ) { };

		bool CloseChildren();
};


#endif   // _WINBOLSA_H

