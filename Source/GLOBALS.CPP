//-------------------------------------------//
//                                           //
//    GLOBALS. CPP                           //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include "globals.h"


// _________________________________________________
//       Global Pointers Definition
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TCtrlBar   *__tool_bar   = 0;
TStatusBar *__status_bar = 0;

TTextGadget *__status_bar_slot_1 = 0;
TTextGadget *__status_bar_slot_2 = 0;

TFlyByTIPButton  *__speed_button_1 = 0;
TFlyByTIPButton  *__speed_button_2 = 0;
TFlyByTIPButton  *__speed_button_3 = 0;

TComm  *__comm     = 0;
TClock *__clock    = 0;
TGauge *__rx_gauge = 0;

TMDIChildTerminal *__terminal = 0;

// _________________________________________________
//       Global Variables Definition
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

GARQ_TYPE __garq = NOGARQ;

TRANSFER_TAB_1  __notebook_tab_1;
TRANSFER_TAB_2  __notebook_tab_2;
TRANSFER_TAB_3  __notebook_tab_3;

unsigned int __notebook_tab_4[ MAXLEN_MODEM ];

bool __is_dirty          = false;
bool __is_attached       = false;
bool __is_valid_comm     = false;
bool __is_frst_ntbf_inst = true;
bool __is_query_running  = false;

string __ini_file_name,
		 __capture_path;

string __slash = '/'  ;
string __tab   = '\t' ;

ofstream __capture;
extern unsigned _stklen = 15000;

// _________________________________________________
//       System Timers Definition
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const uint TIMER_SPLASHDLG_START         = 1001;
const uint TIMER_SPLASH_TIMEOUT_START    = 4000;	// milisecs

const uint TIMER_SPLASHDLG_STOP          = 1002;
const uint TIMER_SPLASH_TIMEOUT_STOP     = 1;		// milisecs

const uint DIAL_MAX_ELAPSED_TIME         = 9;      // milisecs

const uint TIMER_DIAL_GAUGE              = 1002;
const uint TIMER_DIAL_GAUGE_TIMEOUT      = 1;		// milisecs

const uint TIMER_DIAL_CONNECTED          = 1003;
const uint TIMER_DIAL_CONNECTED_TIMEOUT  = 250;		// milisecs

// _________________________________________________
//       Terminal Window Limits
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const uint TERMINAL_MAX_LENGTH   = 8192;
const uint TERMINAL_RIGHT_MARGIN = 80;

