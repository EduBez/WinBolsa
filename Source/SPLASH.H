//-------------------------------------------//
//                                           //
//    SPLASH. H                              //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef  _SPLASH_H
	#define _SPLASH_H

#include <owl/dialog.h>


/*----------------------------------*
 *           TSplashDialog          *
 *----------------------------------*/

class TSplashDialog : public TDialog
{
	public:
		TSplashDialog( TWindow* parent, TResId resid, TModule* module = 0 );

		void SetupWindow();
		void CleanupWindow();

	protected :
		// Standard / user windows messages event handlers
		bool EvEraseBkgnd( HDC hDC );
		void EvTimer( uint timerId );

		DECLARE_RESPONSE_TABLE( TSplashDialog );

	private :
		TPointer<TBitmap> SplashBitMap;
		int W,H;
};


#endif

