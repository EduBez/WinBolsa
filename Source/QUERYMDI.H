//-------------------------------------------//
//                                           //
//    QUERYMDI. H                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef  _QUERYMDI_H
	#define _QUERYMDI_H

#include "flybybtn.h"


/*----------------------------------*
 *           TQueryMDIChild         *
 *----------------------------------*/

class TQueryMDIChild : public TMDIChild
{
	public :
		TQueryMDIChild( int CmId, TMDIClient &parent, const char far* title = 0,
							 TWindow* clientWnd = 0, bool shrinkToClient = false,
							 TModule* module = 0 );

		~TQueryMDIChild();

	protected :
		// Standard / user windows messages event handlers
		void EvMDIActivate( HWND hWndActivated, HWND hWndDeactivated );

		DECLARE_RESPONSE_TABLE( TQueryMDIChild );

	private :
		TFlyByTIPButton  *ButtonGadget;
		TSeparatorGadget *Separator;

		int command;
};


#endif

