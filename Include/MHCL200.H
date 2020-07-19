//--------------------------------------------------------
// MHCL200.H generated from MHCL200.VBX by
// VbxGen 1.0 - Borland International
//--------------------------------------------------------

#ifdef __OWL_OWLDEFS_H
  #include <owl\vbxctl.h>
#endif

//--------------------------------------------------------
// MhClock (VB2)
//--------------------------------------------------------

// properties
#define Prop_MhClock_CtlName 0
#define Prop_MhClock_Index 1
#define Prop_MhClock_Parent 2
#define Prop_MhClock_BackColor 3
#define Prop_MhClock_ForeColor 4
#define Prop_MhClock_Left 5
#define Prop_MhClock_Top 6
#define Prop_MhClock_Width 7
#define Prop_MhClock_Height 8
#define Prop_MhClock_Enabled 9
#define Prop_MhClock_Visible 10
#define Prop_MhClock_MousePointer 11
#define Prop_MhClock_DragMode 12
#define Prop_MhClock_DragIcon 13
#define Prop_MhClock_TabIndex 14
#define Prop_MhClock_TabStop 15
#define Prop_MhClock_Tag 16
#define Prop_MhClock_Style 17
#define Prop_MhClock_PictureAClock 18
#define Prop_MhClock_PictureDClock 19
#define Prop_MhClock_Hour 20
#define Prop_MhClock_Minute 21
#define Prop_MhClock_Second 22
#define Prop_MhClock_ShowMinimized 23
#define Prop_MhClock_HourHandLen 24
#define Prop_MhClock_HourHandWidth 25
#define Prop_MhClock_MinuteHandLen 26
#define Prop_MhClock_MinuteHandWidth 27
#define Prop_MhClock_SecondHandLen 28
#define Prop_MhClock_SecondHandWidth 29
#define Prop_MhClock_HourTop 30
#define Prop_MhClock_HourLeft 31
#define Prop_MhClock_MinuteTop 32
#define Prop_MhClock_MinuteLeft 33
#define Prop_MhClock_SecondTop 34
#define Prop_MhClock_SecondLeft 35
#define Prop_MhClock_AlarmHour 36
#define Prop_MhClock_AlarmMinute 37
#define Prop_MhClock_AlarmSecond 38
#define Prop_MhClock_HourWidth 40
#define Prop_MhClock_HourHeight 41
#define Prop_MhClock_MinuteWidth 42
#define Prop_MhClock_MinuteHeight 43
#define Prop_MhClock_SecondWidth 44
#define Prop_MhClock_SecondHeight 45
#define Prop_MhClock_FontName 46
#define Prop_MhClock_FontSize 47
#define Prop_MhClock_FontBold 48
#define Prop_MhClock_FontItalic 49
#define Prop_MhClock_FontStrikethru 50
#define Prop_MhClock_FontUnderline 51
#define Prop_MhClock_Interval 52
#define Prop_MhClock_BestFit 53
#define Prop_MhClock_HourBottom 54
#define Prop_MhClock_HourRight 55
#define Prop_MhClock_MinuteBottom 56
#define Prop_MhClock_MinuteRight 57
#define Prop_MhClock_SecondBottom 58
#define Prop_MhClock_SecondRight 59
#define Prop_MhClock_ScaleMode 60
#define Prop_MhClock_hWnd 61
#define Prop_MhClock_HelpContextID 62
#define Prop_MhClock_TextColor 63
#define Prop_MhClock_LightColor 64
#define Prop_MhClock_ShadowColor 65
#define Prop_MhClock_FillColor 66
#define Prop_MhClock_BorderColor 67
#define Prop_MhClock_FontStyle 68

// events
#define Event_MhClock_Alarm 0
#define Event_MhClock_ChangeHour 1
#define Event_MhClock_ChangeMinute 2
#define Event_MhClock_ChangeSecond 3
#define Event_MhClock_DragDrop 4
#define Event_MhClock_DragOver 5
#define Event_MhClock_GotFocus 6
#define Event_MhClock_LostFocus 7

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
//   TVbxMhClock* c = new TVbxMhClock(..., sizeof(MhClockData), MhClockData);
//
// For C/C++ programs:
//
//   HFORMFILE file = VBXCreateFormFile(sizeof(MhClockData), MhClockData);
//   HCTL c = VBXCreate(..., file);
//   VBXDeleteFormFile(file);
//
// Note that the VBXGEN_DATA or MhClock_DATA symbol must be
// defined in order to use the default form data.
//
extern BYTE MhClockData[212L];
#if defined(VBXGEN_DATA) || defined(MhClock_DATA)
  BYTE MhClockData[212L]={
    0x3c,0x00,0x00,0x07,0x4d,0x68,0x43,0x6c,
    0x6f,0x63,0x6b,0x01,0x00,0x00,0x03,0xe0,
    0xe0,0xc0,0x00,0x04,0x00,0x00,0x00,0x00,
    0x05,0x09,0xff,0xff,0x0a,0xff,0xff,0x0b,
    0x00,0x0c,0x00,0x0e,0x00,0x00,0x0f,0x00,
    0x00,0x10,0x00,0x11,0x01,0x14,0xff,0xff,
    0x15,0xff,0xff,0x16,0xff,0xff,0x17,0x00,
    0x00,0x18,0x32,0x00,0x19,0x04,0x00,0x1a,
    0x5a,0x00,0x1b,0x02,0x00,0x1c,0x64,0x00,
    0x1d,0x01,0x00,0x1e,0x00,0x00,0x1f,0x00,
    0x00,0x20,0x00,0x00,0x21,0x21,0x00,0x22,
    0x00,0x00,0x23,0x42,0x00,0x24,0xff,0xff,
    0x25,0xff,0xff,0x26,0xff,0xff,0x28,0x22,
    0x00,0x29,0x65,0x00,0x2a,0x22,0x00,0x2b,
    0x65,0x00,0x2c,0x23,0x00,0x2d,0x65,0x00,
    0x2e,0x40,0x01,0x07,0x00,0x00,0x00,0x00,
    0x00,0xbc,0x02,0x00,0x00,0x00,0x00,0x01,
    0x02,0x02,0x22,0x53,0x79,0x73,0x74,0x65,
    0x6d,0x00,0x17,0xe0,0x17,0x50,0x00,0x5e,
    0x13,0x47,0x4f,0x6f,0x53,0x61,0x1f,0x1f,
    0x11,0x50,0x00,0x5e,0x13,0xf8,0x17,0xe0,
    0x17,0x36,0x06,0x34,0xe8,0x03,0x00,0x00,
    0x35,0xff,0xff,0x3e,0x00,0x00,0x00,0x00,
    0x3f,0x08,0x00,0x00,0x80,0x40,0x05,0x00,
    0x00,0x80,0x41,0x10,0x00,0x00,0x80,0x42,
    0x0f,0x00,0x00,0x80,0x43,0x06,0x00,0x00,
    0x80,0x44,0x00,0xff,
  };
#endif

#ifdef __OWL_VBXCTL_H

// OWL class
class TVbxMhClock : public TVbxControl {
  public:

    // constructors
    TVbxMhClock(TWindow* parent, int id, LPCSTR title,
        int x, int y, int w, int h,
        long initLen=0, void far* initData=0, TModule* module=0) :
      TVbxControl(parent, id, "MHCL200.VBX", "MhClock",
          title, x, y, w, h, initLen, initData, module) {}

    TVbxMhClock(TWindow* parent, int resourceId, TModule* module=0) :
        TVbxControl(parent, resourceId, module) {}

#if 0
    // event handlers
    void EvAlarm(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvChangeHour(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvChangeMinute(VBXEVENT FAR*)
    {
      // no arguments
    }

    void EvChangeSecond(VBXEVENT FAR*)
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

    void EvLostFocus(VBXEVENT FAR*)
    {
      // no arguments
    }

#endif

    // enumerations
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

    enum { // values for property DragMode
      DragMode_0_Manual,
      DragMode_1_Automatic,
    };

    enum { // values for property Style
      Style_0_12_hour_digital,
      Style_1_12_hour_digital_with_seconds,
      Style_2_24_hour_digital,
      Style_3_24_hour_digital_with_seconds,
      Style_4_12_hour_analog,
      Style_5_12_hour_analog_with_seconds,
      Style_6_24_hour_analog,
      Style_7_24_hour_analog_with_seconds,
    };

    enum { // values for property ScaleMode
      ScaleMode_0_Reserved,
      ScaleMode_1_Twip,
      ScaleMode_2_Reserved,
      ScaleMode_3_Pixel,
    };

    enum { // values for property FontStyle
      FontStyle_0_None,
      FontStyle_1_Raised,
      FontStyle_2_Raised_with_more_shading,
      FontStyle_3_Lowered,
      FontStyle_4_Lowered_with_more_Shading,
    };


    // properties
    BOOL GetPropCtlName(string& v) {return GetProp(0,v);}
    BOOL SetPropCtlName(string& v) {return SetProp(0,v);}

    BOOL GetPropIndex(int& v) {return GetProp(1,v);}
    BOOL SetPropIndex(int v) {return SetProp(1,v);}

    BOOL GetPropParent(int& v) {return GetProp(2,v);}
    BOOL SetPropParent(int v) {return SetProp(2,v);}

    BOOL GetPropBackColor(COLORREF& v) {return GetProp(3,v);}
    BOOL SetPropBackColor(COLORREF v) {return SetProp(3,v);}

    BOOL GetPropForeColor(COLORREF& v) {return GetProp(4,v);}
    BOOL SetPropForeColor(COLORREF v) {return SetProp(4,v);}

    BOOL GetPropLeft(long& v) {return GetProp(5,v);}
    BOOL SetPropLeft(long v) {return SetProp(5,v);}

    BOOL GetPropTop(long& v) {return GetProp(6,v);}
    BOOL SetPropTop(long v) {return SetProp(6,v);}

    BOOL GetPropWidth(long& v) {return GetProp(7,v);}
    BOOL SetPropWidth(long v) {return SetProp(7,v);}

    BOOL GetPropHeight(long& v) {return GetProp(8,v);}
    BOOL SetPropHeight(long v) {return SetProp(8,v);}

    BOOL GetPropEnabled(BOOL& v) {return GetProp(9,v);}
    BOOL SetPropEnabled(BOOL v) {return SetProp(9,v);}

    BOOL GetPropVisible(BOOL& v) {return GetProp(10,v);}
    BOOL SetPropVisible(BOOL v) {return SetProp(10,v);}

    BOOL GetPropMousePointer(ENUM& v) {return GetProp(11,v);}
    BOOL SetPropMousePointer(ENUM v) {return SetProp(11,v);}

    BOOL GetPropDragMode(ENUM& v) {return GetProp(12,v);}
    BOOL SetPropDragMode(ENUM v) {return SetProp(12,v);}

    BOOL GetPropDragIcon(HPIC& v) {return GetProp(13,v);}
    BOOL SetPropDragIcon(HPIC v) {return SetProp(13,v);}

    BOOL GetPropTabIndex(int& v) {return GetProp(14,v);}
    BOOL SetPropTabIndex(int v) {return SetProp(14,v);}

    BOOL GetPropTabStop(BOOL& v) {return GetProp(15,v);}
    BOOL SetPropTabStop(BOOL v) {return SetProp(15,v);}

    BOOL GetPropTag(string& v) {return GetProp(16,v);}
    BOOL SetPropTag(string& v) {return SetProp(16,v);}

    BOOL GetPropStyle(ENUM& v) {return GetProp(17,v);}
    BOOL SetPropStyle(ENUM v) {return SetProp(17,v);}

    BOOL GetPropPictureAClock(HPIC& v) {return GetProp(18,v);}
    BOOL SetPropPictureAClock(HPIC v) {return SetProp(18,v);}

    BOOL GetPropPictureDClock(HPIC& v) {return GetProp(19,v);}
    BOOL SetPropPictureDClock(HPIC v) {return SetProp(19,v);}

    BOOL GetPropHour(int& v) {return GetProp(20,v);}
    BOOL SetPropHour(int v) {return SetProp(20,v);}

    BOOL GetPropMinute(int& v) {return GetProp(21,v);}
    BOOL SetPropMinute(int v) {return SetProp(21,v);}

    BOOL GetPropSecond(int& v) {return GetProp(22,v);}
    BOOL SetPropSecond(int v) {return SetProp(22,v);}

    BOOL GetPropShowMinimized(BOOL& v) {return GetProp(23,v);}
    BOOL SetPropShowMinimized(BOOL v) {return SetProp(23,v);}

    BOOL GetPropHourHandLen(int& v) {return GetProp(24,v);}
    BOOL SetPropHourHandLen(int v) {return SetProp(24,v);}

    BOOL GetPropHourHandWidth(int& v) {return GetProp(25,v);}
    BOOL SetPropHourHandWidth(int v) {return SetProp(25,v);}

    BOOL GetPropMinuteHandLen(int& v) {return GetProp(26,v);}
    BOOL SetPropMinuteHandLen(int v) {return SetProp(26,v);}

    BOOL GetPropMinuteHandWidth(int& v) {return GetProp(27,v);}
    BOOL SetPropMinuteHandWidth(int v) {return SetProp(27,v);}

    BOOL GetPropSecondHandLen(int& v) {return GetProp(28,v);}
    BOOL SetPropSecondHandLen(int v) {return SetProp(28,v);}

    BOOL GetPropSecondHandWidth(int& v) {return GetProp(29,v);}
    BOOL SetPropSecondHandWidth(int v) {return SetProp(29,v);}

    BOOL GetPropHourTop(int& v) {return GetProp(30,v);}
    BOOL SetPropHourTop(int v) {return SetProp(30,v);}

    BOOL GetPropHourLeft(int& v) {return GetProp(31,v);}
    BOOL SetPropHourLeft(int v) {return SetProp(31,v);}

    BOOL GetPropMinuteTop(int& v) {return GetProp(32,v);}
    BOOL SetPropMinuteTop(int v) {return SetProp(32,v);}

    BOOL GetPropMinuteLeft(int& v) {return GetProp(33,v);}
    BOOL SetPropMinuteLeft(int v) {return SetProp(33,v);}

    BOOL GetPropSecondTop(int& v) {return GetProp(34,v);}
    BOOL SetPropSecondTop(int v) {return SetProp(34,v);}

    BOOL GetPropSecondLeft(int& v) {return GetProp(35,v);}
    BOOL SetPropSecondLeft(int v) {return SetProp(35,v);}

    BOOL GetPropAlarmHour(int& v) {return GetProp(36,v);}
    BOOL SetPropAlarmHour(int v) {return SetProp(36,v);}

    BOOL GetPropAlarmMinute(int& v) {return GetProp(37,v);}
    BOOL SetPropAlarmMinute(int v) {return SetProp(37,v);}

    BOOL GetPropAlarmSecond(int& v) {return GetProp(38,v);}
    BOOL SetPropAlarmSecond(int v) {return SetProp(38,v);}

    BOOL GetPropHourWidth(int& v) {return GetProp(40,v);}
    BOOL SetPropHourWidth(int v) {return SetProp(40,v);}

    BOOL GetPropHourHeight(int& v) {return GetProp(41,v);}
    BOOL SetPropHourHeight(int v) {return SetProp(41,v);}

    BOOL GetPropMinuteWidth(int& v) {return GetProp(42,v);}
    BOOL SetPropMinuteWidth(int v) {return SetProp(42,v);}

    BOOL GetPropMinuteHeight(int& v) {return GetProp(43,v);}
    BOOL SetPropMinuteHeight(int v) {return SetProp(43,v);}

    BOOL GetPropSecondWidth(int& v) {return GetProp(44,v);}
    BOOL SetPropSecondWidth(int v) {return SetProp(44,v);}

    BOOL GetPropSecondHeight(int& v) {return GetProp(45,v);}
    BOOL SetPropSecondHeight(int v) {return SetProp(45,v);}

    BOOL GetPropFontName(string& v) {return GetProp(46,v);}
    BOOL SetPropFontName(string& v) {return SetProp(46,v);}

    BOOL GetPropFontSize(float& v) {return GetProp(47,v);}
    BOOL SetPropFontSize(float v) {return SetProp(47,v);}

    BOOL GetPropFontBold(BOOL& v) {return GetProp(48,v);}
    BOOL SetPropFontBold(BOOL v) {return SetProp(48,v);}

    BOOL GetPropFontItalic(BOOL& v) {return GetProp(49,v);}
    BOOL SetPropFontItalic(BOOL v) {return SetProp(49,v);}

    BOOL GetPropFontStrikethru(BOOL& v) {return GetProp(50,v);}
    BOOL SetPropFontStrikethru(BOOL v) {return SetProp(50,v);}

    BOOL GetPropFontUnderline(BOOL& v) {return GetProp(51,v);}
    BOOL SetPropFontUnderline(BOOL v) {return SetProp(51,v);}

    BOOL GetPropInterval(long& v) {return GetProp(52,v);}
    BOOL SetPropInterval(long v) {return SetProp(52,v);}

    BOOL GetPropBestFit(BOOL& v) {return GetProp(53,v);}
    BOOL SetPropBestFit(BOOL v) {return SetProp(53,v);}

    BOOL GetPropHourBottom(int& v) {return GetProp(54,v);}
    BOOL SetPropHourBottom(int v) {return SetProp(54,v);}

    BOOL GetPropHourRight(int& v) {return GetProp(55,v);}
    BOOL SetPropHourRight(int v) {return SetProp(55,v);}

    BOOL GetPropMinuteBottom(int& v) {return GetProp(56,v);}
    BOOL SetPropMinuteBottom(int v) {return SetProp(56,v);}

    BOOL GetPropMinuteRight(int& v) {return GetProp(57,v);}
    BOOL SetPropMinuteRight(int v) {return SetProp(57,v);}

    BOOL GetPropSecondBottom(int& v) {return GetProp(58,v);}
    BOOL SetPropSecondBottom(int v) {return SetProp(58,v);}

    BOOL GetPropSecondRight(int& v) {return GetProp(59,v);}
    BOOL SetPropSecondRight(int v) {return SetProp(59,v);}

    BOOL GetPropScaleMode(ENUM& v) {return GetProp(60,v);}
    BOOL SetPropScaleMode(ENUM v) {return SetProp(60,v);}

    BOOL GetProphWnd(int& v) {return GetProp(61,v);}
    BOOL SetProphWnd(int v) {return SetProp(61,v);}

    BOOL GetPropHelpContextID(long& v) {return GetProp(62,v);}
    BOOL SetPropHelpContextID(long v) {return SetProp(62,v);}

    BOOL GetPropTextColor(COLORREF& v) {return GetProp(63,v);}
    BOOL SetPropTextColor(COLORREF v) {return SetProp(63,v);}

    BOOL GetPropLightColor(COLORREF& v) {return GetProp(64,v);}
    BOOL SetPropLightColor(COLORREF v) {return SetProp(64,v);}

    BOOL GetPropShadowColor(COLORREF& v) {return GetProp(65,v);}
    BOOL SetPropShadowColor(COLORREF v) {return SetProp(65,v);}

    BOOL GetPropFillColor(COLORREF& v) {return GetProp(66,v);}
    BOOL SetPropFillColor(COLORREF v) {return SetProp(66,v);}

    BOOL GetPropBorderColor(COLORREF& v) {return GetProp(67,v);}
    BOOL SetPropBorderColor(COLORREF v) {return SetProp(67,v);}

    BOOL GetPropFontStyle(ENUM& v) {return GetProp(68,v);}
    BOOL SetPropFontStyle(ENUM v) {return SetProp(68,v);}

#if 0
  DECLARE_RESPONSE_TABLE(TVbxMhClock);
#endif
};

#if 0
// OWL response table
DEFINE_RESPONSE_TABLE1(TVbxMhClock, TVbxControl)
  EV_VBXEVENTINDEX( IDC_MhClock, Event_MhClock_Alarm, EvAlarm ),
  EV_VBXEVENTINDEX( IDC_MhClock, Event_MhClock_ChangeHour, EvChangeHour ),
  EV_VBXEVENTINDEX( IDC_MhClock, Event_MhClock_ChangeMinute, EvChangeMinute ),
  EV_VBXEVENTINDEX( IDC_MhClock, Event_MhClock_ChangeSecond, EvChangeSecond ),
  EV_VBXEVENTINDEX( IDC_MhClock, Event_MhClock_DragDrop, EvDragDrop ),
  EV_VBXEVENTINDEX( IDC_MhClock, Event_MhClock_DragOver, EvDragOver ),
  EV_VBXEVENTINDEX( IDC_MhClock, Event_MhClock_GotFocus, EvGotFocus ),
  EV_VBXEVENTINDEX( IDC_MhClock, Event_MhClock_LostFocus, EvLostFocus ),
END_RESPONSE_TABLE;
#endif

#endif

