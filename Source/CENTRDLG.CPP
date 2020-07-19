//-------------------------------------------//
//                                           //
//    CENTRDLG. CPP                          //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "centrdlg.h"


/////////////////////////////////////
//    TAutoCenterDialog
//                        SetupWindow
//    ===============================
//
void TAutoCenterDialog::SetupWindow()
{
	TDialog::SetupWindow();
	MoveWindowToCenter();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TAutoCenterDialog
//                 MoveWindowToCenter
//    ===============================
//
void TAutoCenterDialog::MoveWindowToCenter()
{
	int W, H;

	TRect R;
	GetWindowRect(R);

	W = R.Width();
	H = R.Height();

	POINT P;
	Parent->GetClientRect(R);

	P.x = ( R.Width()  - W ) / 2;
	P.y = ( R.Height() - H ) / 2;

	::MapWindowPoints( *Parent, 0, &P, 1 );
	MoveWindow( P.x, P.y, W, H , false );
}

