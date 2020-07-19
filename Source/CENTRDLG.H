//-------------------------------------------//
//                                           //
//    CENTRDLG. H                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _CENTER_DIALOG_H
	#define _CENTER_DIALOG_H

#include <owl\dialog.h>


/*-----------------------------------*
 *          TAutoCenterDialog        *
 *-----------------------------------*/

class TAutoCenterDialog : public TDialog
{
	public :
		TAutoCenterDialog( TWindow* parent, TResId resid, TModule* module = 0 )
								 : TDialog( parent, resid, module ),
									TWindow( parent, "", module ) { };
		void SetupWindow();

	private :
		void MoveWindowToCenter();
};

#endif   //  _CENTER_DIALOG_H

