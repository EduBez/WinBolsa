//-------------------------------------------//
//                                           //
//    BROWSE. H                              //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _BROWSE_H
	#define _BROWSE_H

#include <d4all.hpp>
#include <fpgrid10.h>


/*-----------------------------------*
 *            TBrowseCtl             *
 *-----------------------------------*/

class TBrowseCtl : public TVbxSpreadSheet
{
	public :
		TBrowseCtl( Data4* table, TWindow* parent, int id = -1, LPCSTR title = 0,
						int x = 0, int y = 0, int w = 0, int h = 0, long initLen = 0,
						void far* initData = 0, TModule* module = 0 );

		void SetupWindow();
      void UpdateDisplay();

	protected:
		// WM_COMMAND messages event handlers
		void CmEditCopy();
		void CeEditCopy( TCommandEnabler& ce );

		void CmBegin();
		void CeBegin( TCommandEnabler& ce );

		void CmFastBackward();

		void CmBackward();
		void CeBackward( TCommandEnabler& ce );

		void CmForward();
		void CeForward( TCommandEnabler& ce );

		void CmFastForward();

		void CmEnd();
		void CeEnd( TCommandEnabler& ce );

		void EvQueryData( VBXEVENT FAR* event );

		DECLARE_RESPONSE_TABLE( TBrowseCtl );

	private :
		void DataLoad( long Row, long RowsNeeded );
		void Do_Layout();
		void GoRec( long Row );

		inline void SetColRow( long x, long y ) { SetPropCol(x); SetPropRow(y); }
		inline void SetCol2Row2( long x, long y ) { SetPropCol2(x); SetPropRow2(y); }

		inline void GetBlockColRow( long& x, long& y ) { GetPropSelBlockCol( x );
																		 GetPropSelBlockRow( y ); }

		inline void GetBlockCol2Row2( long& x, long& y ) { GetPropSelBlockCol2( x );
																			GetPropSelBlockRow2( y ); }

		inline void SetText( long Col, long Row, string& v )
									{ SetColRow( Col, Row ); SetPropText(v); }

		inline void GetText( long Col, long Row, string& v )
									{ SetColRow( Col, Row ); GetPropText(v); }

		inline void SetGridRange( long f, long l) { First = f; Last = f + l - 1; }

		//----------------------------------------------------------------------//

		Data4 DBF;
		Field4memo field;

		char sbuff[20];

		string sField,
				 sREC,
				 recNo;

		bool QryDataFlag;

		long MAX_RECS,
			  MAX_COLS,
			  First,
			  Last;
};


#endif	// _BROWSE_H

