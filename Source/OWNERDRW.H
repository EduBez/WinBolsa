//-------------------------------------------//
//                                           //
//    OWNERDRW. H                            //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _OWNER_DRAW_H
	#define _OWNER_DRAW_H

#include <owl\button.h>
#include <owl\radiobut.h>

#include "label.h"


/*-----------------------------------*
 *               TTip                *
 *-----------------------------------*/

class _OWLCLASS TTip
{
	public :
		TTip( TWindow* parent, int resID );

		void DisplayFlyByWindow();
		bool MouseInsideClientArea( TPoint& point );

		void MouseMove( uint modKeys, TPoint& point );
		void LButtonDown( uint modKeys, TPoint& point );
		void LButtonUp( uint modKeys, TPoint& point );

	private :
		TWindow* HWnd;
		int id;
		HWND HWndOldCapture;

		bool Capture,
			  TipWindow,
			  TipWndClosed,
			  IsButtonDown,
			  IsButtonUp;

		TLabel* FlyByMsgWnd;
		char sbuff[ 80 ];

		TSize size;
		TRect rc;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *             TODAButton            *
 *-----------------------------------*/

class TODAButton : public TButton
{
	public :
		TODAButton( TWindow* parent, int resID, TModule* module = 0 );

	protected :
		char far* GetClassName() { return "OWLTODAButton"; }

		void Draw( DRAWITEMSTRUCT far& drawInfo, TBitmap* bmp );
		void ODADrawEntire( DRAWITEMSTRUCT far& drawInfo );
		void ODASelect( DRAWITEMSTRUCT far& drawInfo );

	private :
		TPointer<TBitmap> BmpNormal;
		TPointer<TBitmap>	BmpDown;
		TPointer<TBitmap> BmpFocus;
};
//----------------------------------------------------------------------------//

/*-----------------------------------*
 *           TODATipButton           *
 *-----------------------------------*/

class TODATipButton : public TODAButton
{
	public :
		TODATipButton( TWindow* parent, int resID, TModule* module = 0 )
							: TODAButton( parent, resID, module ) { id = resID; }

		void SetupWindow();

	protected :
		char far* GetClassName() { return "OWLTODATipButton"; }

		// Standard and user windows messages event handlers
		void EvMouseMove( uint modKeys, TPoint& point );
		void EvLButtonDown( uint modKeys, TPoint& point );
		void EvLButtonUp( uint modKeys, TPoint& point );

		DECLARE_RESPONSE_TABLE( TODATipButton );

	private :
		int id;
		TPointer<TTip> Tip;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *          TBwccODARadioBtn         *
 *-----------------------------------*/

class TBwccODARadioBtn : public TRadioButton
{
	public :
		TBwccODARadioBtn( TWindow* parent, int resID, TGroupBox* group = 0,
								TModule* module = 0 );
	protected :
		char far* GetClassName() { return "OWLTBwccODARadioBtn"; }

		void Draw( DRAWITEMSTRUCT far& drawInfo, TBitmap* bmp );
		void ODADrawEntire( DRAWITEMSTRUCT far& drawInfo );
		void ODAFocus( DRAWITEMSTRUCT far& drawInfo );

	private :
		TPointer<TBitmap> BmpNormal;
		TPointer<TBitmap>	BmpDown;
		TPointer<TBitmap> BmpFocus;
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *        TBwccODATipRadioBtn        *
 *-----------------------------------*/

class TBwccODATipRadioBtn : public TBwccODARadioBtn
{
	public :
		TBwccODATipRadioBtn( TWindow* parent, int resID, TGroupBox* group = 0,
									TModule* module = 0 )

									: TBwccODARadioBtn( parent, resID, group, module )
															  { id = resID; }
		void SetupWindow();

	protected :
		char far* GetClassName() { return "OWLTBwccODATipRadioBtn"; }

		void EvMouseMove( uint modKeys, TPoint& point );
		void EvLButtonDown( uint modKeys, TPoint& point );
		void EvLButtonUp( uint modKeys, TPoint& point );

		DECLARE_RESPONSE_TABLE( TBwccODATipRadioBtn );

	private :
		int id;
		TTip* Tip;
};

#endif	//_OWNER_DRAW_H

