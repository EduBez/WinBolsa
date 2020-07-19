//-------------------------------------------//
//                                           //
//    LABEL. H                               //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef  _LABEL_H
	#define _LABEL_H

#include <owl\window.h>


/*----------------------------------*
 *             TLabel               *
 *----------------------------------*/

class TLabel : public TWindow
{
	public:
		TLabel( TWindow* parent, LPCSTR title = 0, COLORREF color = TColor::LtYellow,
				  bool Ltip = true, TModule* module = 0 )

				  : TWindow( parent, title, module ) { Text   = title;
																	Color  = color;
																	LTip   = Ltip ; };
		void Paint( TDC& dc, bool erase, TRect& rect );

	protected :
		char far * GetClassName() { return "OWLTLabel"; }
		void GetWindowClass( WNDCLASS &wndClass );

	private :
		LPCSTR Text;
		COLORREF Color;
		bool LTip;
};


#endif

