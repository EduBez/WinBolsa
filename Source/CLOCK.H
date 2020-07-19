//-------------------------------------------//
//                                           //
//    CLOCK. H                               //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _CLOCK_H
	#define _CLOCK_H

#include <mhcl200.h>
#include "winbolsa.rh"


/*-----------------------------------*
 *               TClock              *
 *-----------------------------------*/

class TClock : public TVbxMhClock
{
   public :
		TClock( TWindow* Parent, int x, int y, int w, int h )
				  : TVbxMhClock( Parent, -1, 0, x, y, w, h ) { };

		TClock( TWindow* Parent, int ResourceId, TModule* Module = 0 )
				  : TVbxMhClock( Parent, ResourceId, Module) { };

		void SetupWindow();
		void CleanupWindow();

		void SetTime( int Hour = -1, int Minute = -1, int Second = -1 );
		void Reset();

	private :
		void Show( bool Boolean );
		void GetTime( int& Hour, int& Minute, int& Second );

      HPIC hPict;
};

#endif // _CLOCK_H

