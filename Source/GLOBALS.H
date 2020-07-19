//-------------------------------------------//
//                                           //
//    GLOBALS. H                             //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#ifndef  _GLOBALS_H
	#define _GLOBALS_H

#include <owl\gauge.h>
#include <owl\statusba.h>

#include "clock.h"
#include "comm.h"
#include "flybybtn.h"
#include "terminal.h"
#include "toolbar.h"
#include "winbolsa.rh"


//////////////////////////////////////////////////////////////////
//////   Global Enumerations                         /////////////

typedef enum {

	GARQBRx     = -10 ,
	GARQBRA     = -11 ,
	GARQBSx     = -12 ,
	GARQBSG     = -13 ,

	NOGARQ      = 0   ,
	GARQBOR1    = 1   ,
	GARQBOR2    = 2   ,
	GARQBOR3    = 3   ,
	GARQBOR4    = 4   ,
	GARQBOR5    = 5   ,
	GARQBR      = 6   ,
	GARQBRI     = 7   ,
	GARQBFR1    = 8   ,
	GARQBFR2    = 9   ,
	GARQBFR3    = 10  ,
	GARQBS      = 11  ,
	GARQBSI     = 12  ,
	GARQBAS1    = 13  ,
	GARQBAS2    = 14  ,
	GARQBRJDATA = 15  ,
	GARQBSPDATA = 16  ,
	GARQBIG     = 17  ,
	GARQNEG     = 18  ,
	GARQHIS     = 19  ,
	GARQIND     = 20

} GARQ_TYPE;

//////////////////////////////////////////////////////////////////
//////   Transfer Buffers for the NoteBook Tabs      /////////////

struct TRANSFER_TAB_1 {

	char Id[ MAXLEN_ID    ];
	char Passw[ MAXLEN_PASSW ];
	char Phone [ MAXLEN_PHONE  ];
};

struct TRANSFER_TAB_2 {

	uint16 Pulse;
	uint16 Tone;
	char Prefix[ MAXLEN_PREFIX ];
	uint16 UsePrefix;
	char Signal[ MAXLEN_SIGNAL ];
};

struct TRANSFER_TAB_3 {

	char InitString[ MAXLEN_INITSTRING  ];
	char TimeoutTime[ MAXLEN_TIMEOUTTIME ];
};

//////////////////////////////////////////////////////////////////
//////   Global Pointers Declaration                 /////////////

extern TCtrlBar   *__tool_bar;             // GadgetWindow ToolBar
extern TStatusBar *__status_bar;

extern TTextGadget *__status_bar_slot_1,   // Status Bar slots of information
						 *__status_bar_slot_2;

extern TFlyByTIPButton  *__speed_button_1, // Speed buttons from
								*__speed_button_2, // left to right
								*__speed_button_3;

extern TComm  *__comm;                     // Comunication Terminal
extern TClock *__clock;                    // Analogic Clock VBX
extern TGauge *__rx_gauge;                 // 'Rx' Buffer Gauge

extern TMDIChildTerminal *__terminal;      // Terminal output window

//////////////////////////////////////////////////////////////////
//////   Global Variables Declaration                /////////////

extern GARQ_TYPE __garq;          // Holds document type after 'CmFileNew' command

extern TRANSFER_TAB_1 __notebook_tab_1; // Transfer Buffers for Setup Dialog
extern TRANSFER_TAB_2 __notebook_tab_2;
extern TRANSFER_TAB_3 __notebook_tab_3;
extern unsigned int __notebook_tab_4[ MAXLEN_MODEM ];

extern bool __is_dirty,           // Flag indicator for WM_SIZE & WM_MOVE
				__is_attached,        // Host attachment indicator
				__is_valid_comm,      // Valid COMM port in use
				__is_frst_ntbf_inst,  // NoteBook first instance
				__is_query_running;   // Query running flag

extern string __ini_file_name,    // WinBolsa INI file Name & Path
				  __capture_path,     // Capture file Name & Path
				  __slash,
				  __tab;

extern ofstream __capture;        // Capture file output stream

//////////////////////////////////////////////////////////////////
//////   System Timers Declaration                   /////////////

extern const uint TIMER_SPLASHDLG_START;
extern const uint TIMER_SPLASH_TIMEOUT_START;

extern const uint TIMER_SPLASHDLG_STOP;
extern const uint TIMER_SPLASH_TIMEOUT_STOP;

extern const uint DIAL_MAX_ELAPSED_TIME;

extern const uint TIMER_DIAL_GAUGE;
extern const uint TIMER_DIAL_GAUGE_TIMEOUT;

extern const uint TIMER_DIAL_CONNECTED;
extern const uint TIMER_DIAL_CONNECTED_TIMEOUT;

//////////////////////////////////////////////////////////////////
//////   Terminal Window Limits                      /////////////

extern const uint TERMINAL_MAX_LENGTH;
extern const uint TERMINAL_RIGHT_MARGIN;

#endif	// _GLOBALS_H

