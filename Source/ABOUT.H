//-------------------------------------------------//
//                                                 //
//    ABOUT. H                                     //
//                                                 //
//    Copyright (C) 1994, 1995 by Eduardo Bezerra  //
//                                                 //
//-------------------------------------------------//


#ifndef _ABOUT_DIALOG_H
	#define _ABOUT_DIALOG_H

#include "centrdlg.h"
#include "ownerdrw.h"
#include "winbolsa.rh"


/*-----------------------------------*
 *             TAboutDlg             *
 *-----------------------------------*/

class TAboutDlg : public TAutoCenterDialog
{
	public :
		TAboutDlg( TWindow* parent, TResId resid, TModule* module = 0 );

	protected :
		// Standard / user windows messages event handlers
		bool EvEraseBkgnd( HDC hDC );

		DECLARE_RESPONSE_TABLE( TAboutDlg );

	private :
      TPointer<TBitmap> AboutBmp;
};

#endif   //  _ABOUT_DIALOG_H

