//-------------------------------------------//
//                                           //
//    COMM. H                                //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef _COMM_H
   #define _COMM_H

#include <saxcomm.h>


/*-----------------------------------*
 *               TComm               *
 *-----------------------------------*/

class TComm : public TVbxsaxComm
{
	public :
		TComm( TWindow* parent, int id, LPCSTR title, int x, int y, int w, int h )
				 : TVbxsaxComm( parent, id, title, x, y, w, h ) { };

		void SetupWindow();

		void GetPropAll( unsigned int (*TBuff)[] );
		void SetPropAll( unsigned int TBuff[] );

		bool IsValidPort( string& Port );
		void SetDescription();

		void Delay( unsigned long n = 1L );
		bool Initialize( string& v );

		void DropDTR();
		bool SendATCommand( string command, string* result = 0 );

		bool HangUp();
		uint RxUsed();

		void ReadIniPrivateFile();
		void WriteIniPrivateFile();

		int GetCommId() { return CommId; }

	private :
		string IniCommPort;
		int CommId;

      COMSTAT comstat;
		char sbuff[6];
};

#endif   // _COMM_H

