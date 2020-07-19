//--------------------------------------------------------
// SAXCOMM.H generated from SAXCOMM.VBX by
// VbxGen 1.0 - Borland International
//--------------------------------------------------------

#ifdef __OWL_OWLDEFS_H
  #include <owl\vbxctl.h>
#endif

//--------------------------------------------------------
// saxComm (VB1)
//--------------------------------------------------------

// properties
#define Prop_saxComm_CtlName 0
#define Prop_saxComm_Index 1
#define Prop_saxComm_BackColor 2
#define Prop_saxComm_ForeColor 3
#define Prop_saxComm_Left 4
#define Prop_saxComm_Top 5
#define Prop_saxComm_Width 6
#define Prop_saxComm_Height 7
#define Prop_saxComm_Visible 8
#define Prop_saxComm_Parent 9
#define Prop_saxComm_DragMode 10
#define Prop_saxComm_DragIcon 11
#define Prop_saxComm_Tag 12
#define Prop_saxComm_Caption 13
#define Prop_saxComm_BorderStyle 14
#define Prop_saxComm_TabIndex 15
#define Prop_saxComm_TabStop 16
#define Prop_saxComm_Enabled 17
#define Prop_saxComm_MousePointer 18
#define Prop_saxComm_hWnd 19
#define Prop_saxComm_Port 20
#define Prop_saxComm_Speed 21
#define Prop_saxComm_Parity 22
#define Prop_saxComm_DataBits 23
#define Prop_saxComm_StopBits 24
#define Prop_saxComm_MaxReceiveLen 25
#define Prop_saxComm_Receive 26
#define Prop_saxComm_Send 27
#define Prop_saxComm_Echo 28
#define Prop_saxComm_AutoReceive 29
#define Prop_saxComm_AutoSend 30
#define Prop_saxComm_Upload 31
#define Prop_saxComm_Download 32
#define Prop_saxComm_BytesTransferred 33
#define Prop_saxComm_XonXoff 34
#define Prop_saxComm_CtsRts 35
#define Prop_saxComm_About 36
#define Prop_saxComm_Display 37
#define Prop_saxComm_DisplayLine 38

// events
#define Event_saxComm_Click 0
#define Event_saxComm_DragDrop 1
#define Event_saxComm_DragOver 2
#define Event_saxComm_GotFocus 3
#define Event_saxComm_KeyDown 4
#define Event_saxComm_KeyPress 5
#define Event_saxComm_KeyUp 6
#define Event_saxComm_LostFocus 7
#define Event_saxComm_MouseDown 8
#define Event_saxComm_MouseMove 9
#define Event_saxComm_MouseUp 10

// default form data
//
// Some VBX controls do not operate correctly when created without
// a form file.  This occurs when a program creates a control
// dynamically rather than as part of a dialog resource.  If this
// control exhibits problems in this mode, try creating it with the
// following form data:
//
// For OWL programs:
//
//   TVbxsaxComm* c = new TVbxsaxComm(..., sizeof(saxCommData), saxCommData);
//
// For C/C++ programs:
//
//   HFORMFILE file = VBXCreateFormFile(sizeof(saxCommData), saxCommData);
//   HCTL c = VBXCreate(..., file);
//   VBXDeleteFormFile(file);
//
// Note that the VBXGEN_DATA or saxComm_DATA symbol must be
// defined in order to use the default form data.
//
extern BYTE saxCommData[83L];
#if defined(VBXGEN_DATA) || defined(saxComm_DATA)
  BYTE saxCommData[83L]={
    0x00,0x04,0x43,0x6f,0x6d,0x6d,0x01,0x00,
    0x00,0x02,0x00,0x00,0x7f,0x00,0x03,0xff,
    0xff,0xff,0x00,0x04,0x08,0xff,0xff,0x0a,
    0x00,0x0c,0x00,0x0d,0x07,0x73,0x61,0x78,
    0x43,0x6f,0x6d,0x6d,0x0e,0x00,0x0f,0x00,
    0x00,0x10,0x00,0x00,0x11,0xff,0xff,0x12,
    0x00,0x14,0x00,0x15,0x60,0x09,0x00,0x00,
    0x16,0x00,0x17,0x08,0x00,0x18,0x01,0x00,
    0x19,0x00,0x00,0x1c,0x00,0x00,0x1d,0xff,
    0xff,0x1e,0xff,0xff,0x22,0x00,0x00,0x23,
    0x00,0x00,0xff,
  };
#endif

#ifdef __OWL_VBXCTL_H

// OWL class
class TVbxsaxComm : public TVbxControl {
  public:

    // constructors
    TVbxsaxComm(TWindow* parent, int id, LPCSTR title,
        int x, int y, int w, int h,
        long initLen=0, void far* initData=0, TModule* module=0) :
      TVbxControl(parent, id, "SAXCOMM.VBX", "saxComm",
          title, x, y, w, h, initLen, initData, module) {}

    TVbxsaxComm(TWindow* parent, int resourceId, TModule* module=0) :
        TVbxControl(parent, resourceId, module) {}

#if 0
    // event handlers
    void EvClick(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvDragDrop(VBXEVENT FAR*)
    {
      // Source As Control,X As Integer,Y As Integer
    }

    void EvDragOver(VBXEVENT FAR*)
    {
      // Source As Control,X As Integer,Y As Integer,State As Integer
    }

    void EvGotFocus(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvKeyDown(VBXEVENT FAR*)
    {
      // KeyCode As Integer,Shift As Integer
    }

    void EvKeyPress(VBXEVENT FAR*)
    {
      // KeyAscii As Integer
    }

    void EvKeyUp(VBXEVENT FAR*)
    {
      // KeyCode As Integer,Shift As Integer
    }

    void EvLostFocus(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvMouseDown(VBXEVENT FAR*)
    {
      // Button As Integer,Shift As Integer,X As Integer,Y As Integer
    }

    void EvMouseMove(VBXEVENT FAR*)
    {
      // Button As Integer,Shift As Integer,X As Integer,Y As Integer
    }

    void EvMouseUp(VBXEVENT FAR*)
    {
      // Button As Integer,Shift As Integer,X As Integer,Y As Integer
    }

#endif

    // enumerations
    enum { // values for property DragMode
      DragMode_0_Manual,
      DragMode_1_Automatic,
    };

    enum { // values for property BorderStyle
      BorderStyle_0_None,
      BorderStyle_1_Fixed_Single,
    };

    enum { // values for property MousePointer
      MousePointer_0_Default,
      MousePointer_1_Arrow,
      MousePointer_2_Cross,
      MousePointer_3_IBeam,
      MousePointer_4_Icon,
      MousePointer_5_Size,
      MousePointer_6_Size_NE_SW,
      MousePointer_7_Size_NS,
      MousePointer_8_Size_NW_SE,
      MousePointer_9_Size_WE,
      MousePointer_10_Up_Arrow,
      MousePointer_11_Hourglass,
      MousePointer_12_No_Drop,
    };

    enum { // values for property Parity
      Parity_0_None,
      Parity_1_Even,
      Parity_2_Odd,
      Parity_3_Mark,
      Parity_4_Space,
    };


    // properties
    BOOL GetPropCtlName(string& v) {return GetProp(0,v);}
    BOOL SetPropCtlName(string& v) {return SetProp(0,v);}

    BOOL GetPropIndex(int& v) {return GetProp(1,v);}
    BOOL SetPropIndex(int v) {return SetProp(1,v);}

    BOOL GetPropBackColor(COLORREF& v) {return GetProp(2,v);}
    BOOL SetPropBackColor(COLORREF v) {return SetProp(2,v);}

    BOOL GetPropForeColor(COLORREF& v) {return GetProp(3,v);}
    BOOL SetPropForeColor(COLORREF v) {return SetProp(3,v);}

    BOOL GetPropLeft(long& v) {return GetProp(4,v);}
    BOOL SetPropLeft(long v) {return SetProp(4,v);}

    BOOL GetPropTop(long& v) {return GetProp(5,v);}
    BOOL SetPropTop(long v) {return SetProp(5,v);}

    BOOL GetPropWidth(long& v) {return GetProp(6,v);}
    BOOL SetPropWidth(long v) {return SetProp(6,v);}

    BOOL GetPropHeight(long& v) {return GetProp(7,v);}
    BOOL SetPropHeight(long v) {return SetProp(7,v);}

    BOOL GetPropVisible(BOOL& v) {return GetProp(8,v);}
    BOOL SetPropVisible(BOOL v) {return SetProp(8,v);}

    BOOL GetPropParent(int& v) {return GetProp(9,v);}
    BOOL SetPropParent(int v) {return SetProp(9,v);}

    BOOL GetPropDragMode(ENUM& v) {return GetProp(10,v);}
    BOOL SetPropDragMode(ENUM v) {return SetProp(10,v);}

    BOOL GetPropDragIcon(HPIC& v) {return GetProp(11,v);}
    BOOL SetPropDragIcon(HPIC v) {return SetProp(11,v);}

    BOOL GetPropTag(string& v) {return GetProp(12,v);}
    BOOL SetPropTag(string& v) {return SetProp(12,v);}

    BOOL GetPropCaption(string& v) {return GetProp(13,v);}
    BOOL SetPropCaption(string& v) {return SetProp(13,v);}

    BOOL GetPropBorderStyle(ENUM& v) {return GetProp(14,v);}
    BOOL SetPropBorderStyle(ENUM v) {return SetProp(14,v);}

    BOOL GetPropTabIndex(int& v) {return GetProp(15,v);}
    BOOL SetPropTabIndex(int v) {return SetProp(15,v);}

    BOOL GetPropTabStop(BOOL& v) {return GetProp(16,v);}
    BOOL SetPropTabStop(BOOL v) {return SetProp(16,v);}

    BOOL GetPropEnabled(BOOL& v) {return GetProp(17,v);}
    BOOL SetPropEnabled(BOOL v) {return SetProp(17,v);}

    BOOL GetPropMousePointer(ENUM& v) {return GetProp(18,v);}
    BOOL SetPropMousePointer(ENUM v) {return SetProp(18,v);}

    BOOL GetProphWnd(int& v) {return GetProp(19,v);}
    BOOL SetProphWnd(int v) {return SetProp(19,v);}

    BOOL GetPropPort(string& v) {return GetProp(20,v);}
    BOOL SetPropPort(string& v) {return SetProp(20,v);}

    BOOL GetPropSpeed(long& v) {return GetProp(21,v);}
    BOOL SetPropSpeed(long v) {return SetProp(21,v);}

    BOOL GetPropParity(ENUM& v) {return GetProp(22,v);}
    BOOL SetPropParity(ENUM v) {return SetProp(22,v);}

    BOOL GetPropDataBits(int& v) {return GetProp(23,v);}
    BOOL SetPropDataBits(int v) {return SetProp(23,v);}

    BOOL GetPropStopBits(int& v) {return GetProp(24,v);}
    BOOL SetPropStopBits(int v) {return SetProp(24,v);}

    BOOL GetPropMaxReceiveLen(int& v) {return GetProp(25,v);}
    BOOL SetPropMaxReceiveLen(int v) {return SetProp(25,v);}

    BOOL GetPropReceive(string& v) {return GetProp(26,v);}
    BOOL SetPropReceive(string& v) {return SetProp(26,v);}

    BOOL GetPropSend(string& v) {return GetProp(27,v);}
    BOOL SetPropSend(string& v) {return SetProp(27,v);}

    BOOL GetPropEcho(BOOL& v) {return GetProp(28,v);}
    BOOL SetPropEcho(BOOL v) {return SetProp(28,v);}

    BOOL GetPropAutoReceive(BOOL& v) {return GetProp(29,v);}
    BOOL SetPropAutoReceive(BOOL v) {return SetProp(29,v);}

    BOOL GetPropAutoSend(BOOL& v) {return GetProp(30,v);}
    BOOL SetPropAutoSend(BOOL v) {return SetProp(30,v);}

    BOOL GetPropUpload(string& v) {return GetProp(31,v);}
    BOOL SetPropUpload(string& v) {return SetProp(31,v);}

    BOOL GetPropDownload(string& v) {return GetProp(32,v);}
    BOOL SetPropDownload(string& v) {return SetProp(32,v);}

    BOOL GetPropBytesTransferred(long& v) {return GetProp(33,v);}
    BOOL SetPropBytesTransferred(long v) {return SetProp(33,v);}

    BOOL GetPropXonXoff(BOOL& v) {return GetProp(34,v);}
    BOOL SetPropXonXoff(BOOL v) {return SetProp(34,v);}

    BOOL GetPropCtsRts(BOOL& v) {return GetProp(35,v);}
    BOOL SetPropCtsRts(BOOL v) {return SetProp(35,v);}

    BOOL GetPropAbout(string& v) {return GetProp(36,v);}
    BOOL SetPropAbout(string& v) {return SetProp(36,v);}

    BOOL GetPropDisplay(string& v) {return GetProp(37,v);}
    BOOL SetPropDisplay(string& v) {return SetProp(37,v);}

    BOOL GetPropDisplayLine(string& v) {return GetProp(38,v);}
    BOOL SetPropDisplayLine(string& v) {return SetProp(38,v);}

#if 0
  DECLARE_RESPONSE_TABLE(TVbxsaxComm);
#endif
};

#if 0
// OWL response table
DEFINE_RESPONSE_TABLE1(TVbxsaxComm, TVbxControl)
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_Click, EvClick ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_DragDrop, EvDragDrop ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_DragOver, EvDragOver ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_GotFocus, EvGotFocus ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_KeyDown, EvKeyDown ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_KeyPress, EvKeyPress ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_KeyUp, EvKeyUp ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_LostFocus, EvLostFocus ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_MouseDown, EvMouseDown ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_MouseMove, EvMouseMove ),
  EV_VBXEVENTINDEX( IDC_saxComm, Event_saxComm_MouseUp, EvMouseUp ),
END_RESPONSE_TABLE;
#endif

#endif

