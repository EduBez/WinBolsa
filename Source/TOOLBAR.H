//-------------------------------------------//
//                                           //
//    TOOLBAR. H                             //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef  _TOOLBAR_H
	#define _TOOLBAR_H

#include <owl\controlb.h>


/*----------------------------------*
 *             TCtrlBar             *
 *----------------------------------*/

class TCtrlBar: public TControlBar
{
	public :
		TCtrlBar( TWindow* parent = 0, TTileDirection direction = Horizontal,
					 TFont* font = new TGadgetWindowFont, TModule* module = 0 );

      void SetupWindow();

	protected :
		// Standard / user windows messages event handlers
		bool EvEraseBkgnd( HDC hDC );

		DECLARE_RESPONSE_TABLE( TCtrlBar );

	private :
		TPointer<TBitmap> Bitmap;
		TPointer<TBrush>  Brush;
};

#endif
