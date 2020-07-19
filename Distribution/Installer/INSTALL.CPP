//-------------------------------------------------//
//                                                 //
//    INSTALL. CPP                                 //
//                                                 //
//    Copyright (C) 1994, 1995 by Eduardo Bezerra  //
//                                                 //
//-------------------------------------------------//


#include "install.rh"
#include "install.h"
#include "dde_prog.h"


/////////////////////////////////////
//    TInstallApplication
//                     InitMainWindow
//    ===============================
//
void TInstallApplication::InitMainWindow()
{
	TInstallFrameWnd *FrameWnd
      = new TInstallFrameWnd( 0, "Instalador 1.0", new TInstallClientWnd(0) );

	nCmdShow = SW_SHOWMAXIMIZED;

	FrameWnd->SetIcon( ::Module, InstallIcon );
	SetMainWindow( FrameWnd );
}


DEFINE_RESPONSE_TABLE1(TInstallClientWnd, TWindow)
   EV_WM_TIMER,
END_RESPONSE_TABLE;

/////////////////////////////////////
//    TInstallClientWnd
//                        SetupWindow
//    ===============================
//
void TInstallClientWnd::SetupWindow()
{
   TWindow::SetupWindow();
   SetTimer(1, 1000);
}

/////////////////////////////////////
//    TInstallClientWnd
//                            EvTimer
//    ===============================
//
void TInstallClientWnd::EvTimer(uint timerId)
{
   KillTimer(1);
   DdeProgMan ProgMan;

   if ( ProgMan.DdeConnect() )
      if ( ProgMan.CreateGroup("WinBolsa") )

         if ( ProgMan.AddItem("C:\\WINBOLSA\\WINBOLSA.EXE", "WinBolsa 1.0") )
            if ( ProgMan.ShowGroup("WinBolsa", 1) )

               ::MessageBox(NULL,"Instalação efetuada, Grupo de Programas criado.",
                  "Aviso", MB_ICONEXCLAMATION);
   MoveCtrl3d();
}

/////////////////////////////////////
//    TInstallClientWnd
//                              Paint
//    ===============================
//
void TInstallClientWnd::Paint( TDC& dc, bool erase, TRect& rect )
{
	TRect rc;

	long nWidth  = (long)GetClientRect().Width();
	long nHeight = (long)GetClientRect().Height();

	GetClientRect( rc );
	rc += 12;

	nHeight = ( dc.GetDeviceCaps( LOGPIXELSY ) * 36 ) / 72;
	TFont Font( "Arial", nHeight);

	dc.SelectObject( Font );
	dc.SetBkMode( TRANSPARENT );

	dc.SetTextColor( TColor::Black );
	dc.DrawText( "Instalador do WinBolsa®", -1, rc.OffsetBy( 3, 3 ), DT_SINGLELINE );

	dc.SetTextColor( TColor::White );
	dc.DrawText( "Instalador do WinBolsa®", -1, rc, DT_SINGLELINE );
}

/////////////////////////////////////
//    TInstallClientWnd
//                         MoveCtrl3d
//    ===============================
//
void TInstallClientWnd::MoveCtrl3d()
{
   char winPath[_MAX_PATH];
   GetSystemDirectory(winPath, sizeof(winPath));

   ofstream ostr("movctl3d.bat");

   ostr << "@Copy Ctl3d*.Dll " << winPath << endl;
   ostr << "@Del Ctl3d*.Dll"   << endl;

   ostr.close();
   ::WinExec("movctl3d.pif", SW_HIDE);
}



/*****************************
 *     OWL Main Function     *
 *****************************/

int OwlMain( int /*argc*/, char* /*argv*/ [] )
{
	TInstallApplication( "" ).Run();
	return 0;
}

