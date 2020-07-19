//-------------------------------------------//
//                                           //
//    FLYBYBTN. H                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef  _FLYBYBTN_H
	#define _FLYBYBTN_H

#include <owl/buttonga.h>
#include <owl/gadgetwi.h>

#include "label.h"


/*----------------------------------*
 *          TFlyByTIPButton         *
 *----------------------------------*/

class TFlyByTIPButton : public TButtonGadget
{
	public :
		TFlyByTIPButton( TResId uiBitmap, int id, TType type = Command,
							  bool enable = false, TState state = Up,
							  bool repeat = false );
	protected :
		void LButtonDown( uint modkeys, TPoint& point );
		void MouseEnter ( uint modkeys, TPoint& point );
		void MouseLeave ( uint modkeys, TPoint& point );

		char sbuff[ 80 ];
		bool IsWindow;

		TSize size;
		TRect r;

		TLabel* FlyByMsgWnd;
};

#endif   // _FLYBYBTN_H

