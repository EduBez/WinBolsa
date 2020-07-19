//-------------------------------------------------//
//                                                 //
//    INSTALL. H                                   //
//                                                 //
//    Copyright (C) 1994, 1995 by Eduardo Bezerra  //
//                                                 //
//-------------------------------------------------//


#include <owl\applicat.h>
#include <owl\framewin.h>

#include <ddeml.h>


/*----------------------------------*
 *         TInstallClientWnd        *
 *----------------------------------*/
class TInstallClientWnd : public TWindow
{
	public :
		TInstallClientWnd( TWindow* parent, const char far* title = 0,
         TModule* module = 0 )

      : TWindow( parent, title, module ) { };

      void SetupWindow();
      void Paint( TDC& dc, bool erase, TRect& rect );

   protected:
      void EvTimer(uint timerId);
      void MoveCtrl3d();

      DECLARE_RESPONSE_TABLE(TInstallClientWnd);
};



/*----------------------------------*
 *         TInstallFrameWnd         *
 *----------------------------------*/
class TInstallFrameWnd : public TFrameWindow
{
	public :
		TInstallFrameWnd( TWindow* Parent, const char far* title = 0,
         TWindow* clientWnd = 0, bool shrinkToClient = false,
            TModule* module = 0 )

      : TFrameWindow( Parent, title, clientWnd, shrinkToClient, module ) { };

	protected :
		void GetWindowClass( WNDCLASS& wndClass )
		{
			TFrameWindow::GetWindowClass( wndClass );
         wndClass.hbrBackground = TBrush(TColor(0, 128, 128));;
		}
};



/*----------------------------------*
 *       TInstallApplication        *
 *----------------------------------*/
class TInstallApplication : public TApplication
{
	public :
		TInstallApplication( const char* name )
		: TApplication( name ) { };

		void InitMainWindow();
};

