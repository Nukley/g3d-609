/**
  @file Win32Window_di8.cpp

  @maintainer Corey Taylor 
  @created 	  2004-10-16
  @edited  	  2005-02-24
    
*/

#ifndef DIRECTINPUT8_H
#define DIRECTINPUT8_H

#ifndef G3D_WIN32
    #error This is a Win32-only file
#endif

#include <unknwn.h>
#include <initguid.h>


namespace G3D {

const uint32 DIRECTINPUT_VERSION    = 0x0800;

/*
    These define the structures required to use IDirectInput8
    and IDirectInputDevice8.  The only ones left not commented
    out are the ones used.  Akward ordering is left in-case other
    structures are needed later.
*/

// DIDEVICEINSTANCEA
typedef struct DIDEVICEINSTANCEA {
    DWORD   dwSize;
    GUID    guidInstance;
    GUID    guidProduct;
    DWORD   dwDevType;
    CHAR    tszInstanceName[MAX_PATH];
    CHAR    tszProductName[MAX_PATH];
    GUID    guidFFDriver;
    WORD    wUsagePage;
    WORD    wUsage;
} DIDEVICEINSTANCEA, *LPDIDEVICEINSTANCEA;

typedef const DIDEVICEINSTANCEA *LPCDIDEVICEINSTANCEA;
typedef BOOL (FAR PASCAL * LPDIENUMDEVICESCALLBACKA)(LPCDIDEVICEINSTANCEA, LPVOID);

// DIDEVICEOBJECTINSTANCEA
typedef struct DIDEVICEOBJECTINSTANCEA {
    DWORD   dwSize;
    GUID    guidType;
    DWORD   dwOfs;
    DWORD   dwType;
    DWORD   dwFlags;
    CHAR    tszName[MAX_PATH];
    DWORD   dwFFMaxForce;
    DWORD   dwFFForceResolution;
    WORD    wCollectionNumber;
    WORD    wDesignatorIndex;
    WORD    wUsagePage;
    WORD    wUsage;
    DWORD   dwDimension;
    WORD    wExponent;
    WORD    wReportId;
} DIDEVICEOBJECTINSTANCEA, *LPDIDEVICEOBJECTINSTANCEA;
typedef DIDEVICEOBJECTINSTANCEA DIDEVICEOBJECTINSTANCE;
typedef LPDIDEVICEOBJECTINSTANCEA LPDIDEVICEOBJECTINSTANCE;
typedef const DIDEVICEOBJECTINSTANCEA *LPCDIDEVICEOBJECTINSTANCEA;

// LPDIENUMDEVICEOBJECTSCALLBACKA
//    typedef BOOL (FAR PASCAL * LPDIENUMDEVICEOBJECTSCALLBACKA)(LPCDIDEVICEOBJECTINSTANCEA, LPVOID);


// DIDEVCAPS
typedef struct DIDEVCAPS {
    DWORD   dwSize;
    DWORD   dwFlags;
    DWORD   dwDevType;
    DWORD   dwAxes;
    DWORD   dwButtons;
    DWORD   dwPOVs;
    DWORD   dwFFSamplePeriod;
    DWORD   dwFFMinTimeResolution;
    DWORD   dwFirmwareRevision;
    DWORD   dwHardwareRevision;
    DWORD   dwFFDriverVersion;
} DIDEVCAPS, *LPDIDEVCAPS;


// DIPROPHEADER
typedef struct DIPROPHEADER {
    DWORD   dwSize;
    DWORD   dwHeaderSize;
    DWORD   dwObj;
    DWORD   dwHow;
} DIPROPHEADER, *LPDIPROPHEADER;
typedef const DIPROPHEADER *LPCDIPROPHEADER;


// DIPROPWORD
typedef struct DIPROPDWORD {
    DIPROPHEADER diph;
    DWORD   dwData;
} DIPROPDWORD, *LPDIPROPDWORD;
typedef const DIPROPDWORD *LPCDIPROPDWORD;


// DIDEVICEOBJECTDATA
typedef struct DIDEVICEOBJECTDATA {
    DWORD       dwOfs;
    DWORD       dwData;
    DWORD       dwTimeStamp;
    DWORD       dwSequence;
    UINT_PTR    uAppData;
} DIDEVICEOBJECTDATA, *LPDIDEVICEOBJECTDATA;
typedef const DIDEVICEOBJECTDATA *LPCDIDEVICEOBJECTDATA;


// DIOBJECTDATAFORMAT
typedef struct _DIOBJECTDATAFORMAT {
    const GUID *pguid;
    DWORD   dwOfs;
    DWORD   dwType;
    DWORD   dwFlags;
} DIOBJECTDATAFORMAT, *LPDIOBJECTDATAFORMAT;
typedef const DIOBJECTDATAFORMAT *LPCDIOBJECTDATAFORMAT;


// DIDATAFORMAT
typedef struct _DIDATAFORMAT {
    DWORD   dwSize;
    DWORD   dwObjSize;
    DWORD   dwFlags;
    DWORD   dwDataSize;
    DWORD   dwNumObjs;
    LPDIOBJECTDATAFORMAT rgodf;
} DIDATAFORMAT, *LPDIDATAFORMAT;
typedef const DIDATAFORMAT *LPCDIDATAFORMAT;


// DIENVELOPE
//    typedef struct DIENVELOPE {
//        DWORD dwSize;                   /* sizeof(DIENVELOPE)   */
//        DWORD dwAttackLevel;
//        DWORD dwAttackTime;             /* Microseconds         */
//        DWORD dwFadeLevel;
//        DWORD dwFadeTime;               /* Microseconds         */
//    } DIENVELOPE, *LPDIENVELOPE;
//    typedef const DIENVELOPE *LPCDIENVELOPE;


// DIEFFECT
//    typedef struct DIEFFECT {
//        DWORD dwSize;                   /* sizeof(DIEFFECT)     */
//        DWORD dwFlags;                  /* DIEFF_*              */
//        DWORD dwDuration;               /* Microseconds         */
//        DWORD dwSamplePeriod;           /* Microseconds         */
//        DWORD dwGain;
//        DWORD dwTriggerButton;          /* or DIEB_NOTRIGGER    */
//        DWORD dwTriggerRepeatInterval;  /* Microseconds         */
//        DWORD cAxes;                    /* Number of axes       */
//        LPDWORD rgdwAxes;               /* Array of axes        */
//        LPLONG rglDirection;            /* Array of directions  */
//        LPDIENVELOPE lpEnvelope;        /* Optional             */
//        DWORD cbTypeSpecificParams;     /* Size of params       */
//        LPVOID lpvTypeSpecificParams;   /* Pointer to params    */
//        DWORD  dwStartDelay;            /* Microseconds         */
//    } DIEFFECT, *LPDIEFFECT;
//    typedef DIEFFECT DIEFFECT_DX6;
//    typedef LPDIEFFECT LPDIEFFECT_DX6;
//    typedef const DIEFFECT *LPCDIEFFECT;


// DIEFFESCAPE
//    typedef struct DIEFFESCAPE {
//        DWORD   dwSize;
//        DWORD   dwCommand;
//        LPVOID  lpvInBuffer;
//        DWORD   cbInBuffer;
//        LPVOID  lpvOutBuffer;
//        DWORD   cbOutBuffer;
//    } DIEFFESCAPE, *LPDIEFFESCAPE;


// IDirectInputEffect
//    #undef INTERFACE
//    #define INTERFACE IDirectInputEffect

//    DECLARE_INTERFACE_(IDirectInputEffect, IUnknown)
//    {
//        /*** IUnknown methods ***/
//        STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
//        STDMETHOD_(ULONG,AddRef)(THIS) PURE;
//        STDMETHOD_(ULONG,Release)(THIS) PURE;

//        /*** IDirectInputEffect methods ***/
//        STDMETHOD(Initialize)(THIS_ HINSTANCE,DWORD,REFGUID) PURE;
//        STDMETHOD(GetEffectGuid)(THIS_ LPGUID) PURE;
//        STDMETHOD(GetParameters)(THIS_ LPDIEFFECT,DWORD) PURE;
//        STDMETHOD(SetParameters)(THIS_ LPCDIEFFECT,DWORD) PURE;
//        STDMETHOD(Start)(THIS_ DWORD,DWORD) PURE;
//        STDMETHOD(Stop)(THIS) PURE;
//        STDMETHOD(GetEffectStatus)(THIS_ LPDWORD) PURE;
//        STDMETHOD(Download)(THIS) PURE;
//        STDMETHOD(Unload)(THIS) PURE;
//        STDMETHOD(Escape)(THIS_ LPDIEFFESCAPE) PURE;
//    };
//    typedef struct IDirectInputEffect *LPDIRECTINPUTEFFECT;


// DIEFFECTINFOA
//    typedef struct DIEFFECTINFOA {
//        DWORD   dwSize;
//        GUID    guid;
//        DWORD   dwEffType;
//        DWORD   dwStaticParams;
//        DWORD   dwDynamicParams;
//        CHAR    tszName[MAX_PATH];
//    } DIEFFECTINFOA, *LPDIEFFECTINFOA;
//    typedef DIEFFECTINFOA DIEFFECTINFO;
//    typedef LPDIEFFECTINFOA LPDIEFFECTINFO;
//    typedef const DIEFFECTINFOA *LPCDIEFFECTINFOA;
//    typedef const DIEFFECTINFO  *LPCDIEFFECTINFO;


// DIENUMEFFECTSCALLBACKA
//    typedef BOOL (FAR PASCAL * LPDIENUMEFFECTSCALLBACKA)(LPCDIEFFECTINFOA, LPVOID);

// DIENUMCREATEEFFECTOBJECTSCALLBACK
//    typedef BOOL (FAR PASCAL * LPDIENUMCREATEDEFFECTOBJECTSCALLBACK)(LPDIRECTINPUTEFFECT, LPVOID);


// DIFILEEFFECT
//    typedef struct DIFILEEFFECT{
//        DWORD       dwSize;
//        GUID        GuidEffect;
//        LPCDIEFFECT lpDiEffect;
//        CHAR        szFriendlyName[MAX_PATH];
//    }DIFILEEFFECT, *LPDIFILEEFFECT;
//    typedef const DIFILEEFFECT *LPCDIFILEEFFECT;
//    typedef BOOL (FAR PASCAL * LPDIENUMEFFECTSINFILECALLBACK)(LPCDIFILEEFFECT , LPVOID);


// DIACTIONA
//    typedef struct _DIACTIONA {
//                    UINT_PTR    uAppData;
//                    DWORD       dwSemantic;
//        OPTIONAL    DWORD       dwFlags;
//        OPTIONAL    union {
//                        LPCSTR      lptszActionName;
//                        UINT        uResIdString;
//                    };
//        OPTIONAL    GUID        guidInstance;
//        OPTIONAL    DWORD       dwObjID;
//        OPTIONAL    DWORD       dwHow;
//    } DIACTIONA, *LPDIACTIONA ;


// DIACTIONFORMATA
//    typedef struct _DIACTIONFORMATA {
//                    DWORD       dwSize;
//                    DWORD       dwActionSize;
//                    DWORD       dwDataSize;
//                    DWORD       dwNumActions;
//                    LPDIACTIONA rgoAction;
//                    GUID        guidActionMap;
//                    DWORD       dwGenre;
//                    DWORD       dwBufferSize;
//        OPTIONAL    LONG        lAxisMin;
//        OPTIONAL    LONG        lAxisMax;
//        OPTIONAL    HINSTANCE   hInstString;
//                    FILETIME    ftTimeStamp;
//                    DWORD       dwCRC;
//                    CHAR        tszActionMap[MAX_PATH];
//    } DIACTIONFORMATA, *LPDIACTIONFORMATA;


// DIDEVICEIMAGEINFOA
//    typedef struct _DIDEVICEIMAGEINFOA {
//        CHAR        tszImagePath[MAX_PATH];
//        DWORD       dwFlags; 
//        // These are valid if DIDIFT_OVERLAY is present in dwFlags.
//        DWORD       dwViewID;      
//        RECT        rcOverlay;             
//        DWORD       dwObjID;
//        DWORD       dwcValidPts;
//        POINT       rgptCalloutLine[5];  
//        RECT        rcCalloutRect;  
//        DWORD       dwTextAlign;     
//    } DIDEVICEIMAGEINFOA, *LPDIDEVICEIMAGEINFOA;


// DIDEVICEIMAGEINFOHEADER
//    typedef struct _DIDEVICEIMAGEINFOHEADERA {
//        DWORD       dwSize;
//        DWORD       dwSizeImageInfo;
//        DWORD       dwcViews;
//        DWORD       dwcButtons;
//        DWORD       dwcAxes;
//        DWORD       dwcPOVs;
//        DWORD       dwBufferSize;
//        DWORD       dwBufferUsed;
//        LPDIDEVICEIMAGEINFOA lprgImageInfoArray;
//    } DIDEVICEIMAGEINFOHEADERA, *LPDIDEVICEIMAGEINFOHEADERA;


/*
    IDirectInputDevice8A

    This defines the DirectInput8 interface needed to 
    access a direct input device.  
*/
#undef INTERFACE
#define INTERFACE IDirectInputDevice8A

DECLARE_INTERFACE_(IDirectInputDevice8A, IUnknown)
{
    //
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    //
/*
    STDMETHOD(GetCapabilities)(THIS_ LPDIDEVCAPS) PURE;
    STDMETHOD(EnumObjects)(THIS_ LPDIENUMDEVICEOBJECTSCALLBACKA,LPVOID,DWORD) PURE;
    STDMETHOD(GetProperty)(THIS_ REFGUID,LPDIPROPHEADER) PURE;
    STDMETHOD(SetProperty)(THIS_ REFGUID,LPCDIPROPHEADER) PURE;
    STDMETHOD(Acquire)(THIS) PURE;
    STDMETHOD(Unacquire)(THIS) PURE;
    STDMETHOD(GetDeviceState)(THIS_ DWORD,LPVOID) PURE;
    STDMETHOD(GetDeviceData)(THIS_ DWORD,LPDIDEVICEOBJECTDATA,LPDWORD,DWORD) PURE;
    STDMETHOD(SetDataFormat)(THIS_ LPCDIDATAFORMAT) PURE;
    STDMETHOD(SetEventNotification)(THIS_ HANDLE) PURE;
    STDMETHOD(SetCooperativeLevel)(THIS_ HWND,DWORD) PURE;
    STDMETHOD(GetObjectInfo)(THIS_ LPDIDEVICEOBJECTINSTANCEA,DWORD,DWORD) PURE;
    STDMETHOD(GetDeviceInfo)(THIS_ LPDIDEVICEINSTANCEA) PURE;
    STDMETHOD(RunControlPanel)(THIS_ HWND,DWORD) PURE;
    STDMETHOD(Initialize)(THIS_ HINSTANCE,DWORD,REFGUID) PURE;
    STDMETHOD(CreateEffect)(THIS_ REFGUID,LPCDIEFFECT,LPDIRECTINPUTEFFECT *,LPUNKNOWN) PURE;
    STDMETHOD(EnumEffects)(THIS_ LPDIENUMEFFECTSCALLBACKA,LPVOID,DWORD) PURE;
    STDMETHOD(GetEffectInfo)(THIS_ LPDIEFFECTINFOA,REFGUID) PURE;
    STDMETHOD(GetForceFeedbackState)(THIS_ LPDWORD) PURE;
    STDMETHOD(SendForceFeedbackCommand)(THIS_ DWORD) PURE;
    STDMETHOD(EnumCreatedEffectObjects)(THIS_ LPDIENUMCREATEDEFFECTOBJECTSCALLBACK,LPVOID,DWORD) PURE;
    STDMETHOD(Escape)(THIS_ LPDIEFFESCAPE) PURE;
    STDMETHOD(Poll)(THIS) PURE;
    STDMETHOD(SendDeviceData)(THIS_ DWORD,LPCDIDEVICEOBJECTDATA,LPDWORD,DWORD) PURE;
    STDMETHOD(EnumEffectsInFile)(THIS_ LPCSTR,LPDIENUMEFFECTSINFILECALLBACK,LPVOID,DWORD) PURE;
    STDMETHOD(WriteEffectToFile)(THIS_ LPCSTR,DWORD,LPDIFILEEFFECT,DWORD) PURE;
    STDMETHOD(BuildActionMap)(THIS_ LPDIACTIONFORMATA,LPCSTR,DWORD) PURE;
    STDMETHOD(SetActionMap)(THIS_ LPDIACTIONFORMATA,LPCSTR,DWORD) PURE;
    STDMETHOD(GetImageInfo)(THIS_ LPDIDEVICEIMAGEINFOHEADERA) PURE;
*/
    STDMETHOD(GetCapabilities)(THIS_ LPDIDEVCAPS) PURE;
    STDMETHOD(EnumObjects)(THIS_ LPVOID,LPVOID,DWORD) PURE;
    STDMETHOD(GetProperty)(THIS_ REFGUID,LPVOID) PURE;
    STDMETHOD(SetProperty)(THIS_ REFGUID,LPCDIPROPHEADER) PURE;
    STDMETHOD(Acquire)(THIS) PURE;
    STDMETHOD(Unacquire)(THIS) PURE;
    STDMETHOD(GetDeviceState)(THIS_ DWORD,LPVOID) PURE;
    STDMETHOD(GetDeviceData)(THIS_ DWORD,LPDIDEVICEOBJECTDATA,LPDWORD,DWORD) PURE;
    STDMETHOD(SetDataFormat)(THIS_ LPCDIDATAFORMAT) PURE;
    STDMETHOD(SetEventNotification)(THIS_ HANDLE) PURE;
    STDMETHOD(SetCooperativeLevel)(THIS_ HWND,DWORD) PURE;
    STDMETHOD(GetObjectInfo)(THIS_ LPVOID,DWORD,DWORD) PURE;
    STDMETHOD(GetDeviceInfo)(THIS_ LPVOID) PURE;
    STDMETHOD(RunControlPanel)(THIS_ HWND,DWORD) PURE;
    STDMETHOD(Initialize)(THIS_ HINSTANCE,DWORD,REFGUID) PURE;
    STDMETHOD(CreateEffect)(THIS_ REFGUID,LPVOID,LPVOID *,LPUNKNOWN) PURE;
    STDMETHOD(EnumEffects)(THIS_ LPVOID,LPVOID,DWORD) PURE;
    STDMETHOD(GetEffectInfo)(THIS_ LPVOID,REFGUID) PURE;
    STDMETHOD(GetForceFeedbackState)(THIS_ LPDWORD) PURE;
    STDMETHOD(SendForceFeedbackCommand)(THIS_ DWORD) PURE;
    STDMETHOD(EnumCreatedEffectObjects)(THIS_ LPVOID,LPVOID,DWORD) PURE;
    STDMETHOD(Escape)(THIS_ LPVOID) PURE;
    STDMETHOD(Poll)(THIS) PURE;
    STDMETHOD(SendDeviceData)(THIS_ DWORD,LPVOID,LPDWORD,DWORD) PURE;
    STDMETHOD(EnumEffectsInFile)(THIS_ LPCSTR,LPVOID,LPVOID,DWORD) PURE;
    STDMETHOD(WriteEffectToFile)(THIS_ LPCSTR,DWORD,LPVOID,DWORD) PURE;
    STDMETHOD(BuildActionMap)(THIS_ LPVOID,LPCSTR,DWORD) PURE;
    STDMETHOD(SetActionMap)(THIS_ LPVOID,LPCSTR,DWORD) PURE;
    STDMETHOD(GetImageInfo)(THIS_ LPVOID) PURE;
};
typedef struct IDirectInputDevice8A *LPDIRECTINPUTDEVICE8A;


/*
    IDirectInput8A

    This defines the DirectInput8 interface needed to 
    find and create direct input device interfaces.  
*/
#undef INTERFACE
#define INTERFACE IDirectInput8A

DECLARE_INTERFACE_(IDirectInput8A, IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    /*** IDirectInput8A methods ***/
    STDMETHOD(CreateDevice)(THIS_ REFGUID,LPDIRECTINPUTDEVICE8A *,LPUNKNOWN) PURE;
    STDMETHOD(EnumDevices)(THIS_ DWORD,LPDIENUMDEVICESCALLBACKA,LPVOID,DWORD) PURE;
    STDMETHOD(GetDeviceStatus)(THIS_ REFGUID) PURE;
    STDMETHOD(RunControlPanel)(THIS_ HWND,DWORD) PURE;
    STDMETHOD(Initialize)(THIS_ HINSTANCE,DWORD) PURE;
    STDMETHOD(FindDevice)(THIS_ REFGUID,LPCSTR,LPGUID) PURE;
    STDMETHOD(EnumDevicesBySemantics)(THIS_ LPCSTR,LPVOID,LPVOID,LPVOID,DWORD) PURE;
    STDMETHOD(ConfigureDevices)(THIS_ LPVOID,LPVOID,DWORD,LPVOID) PURE;
};

/*
    dinput.h defines

    These are the defines, turned into const uint32, that
    are normally found in dinput.h . Only the ones needed
    in the IDirectInput8A and IDirectInputDevice8A interface
    methods are defined.
*/


const uint32 DIPH_DEVICE           = 0;
const uint32 DIPH_BYOFFSET         = 1;
const uint32 DIPH_BYID             = 2;
const uint32 DIPH_BYUSAGE          = 3;

const uint32 DIEDFL_ATTACHEDONLY   = 0x00000001;
const uint32 DI8DEVCLASS_GAMECTRL  = 4;
const uint32 DISCL_EXCLUSIVE       = 0x00000001;
const uint32 DISCL_NONEXCLUSIVE    = 0x00000002;
const uint32 DISCL_FOREGROUND      = 0x00000004;
const uint32 DISCL_BACKGROUND      = 0x00000008;
const uint32 DISCL_NOWINKEY        = 0x00000010;

const uint32 DIDFT_RELAXIS         = 0x00000001;
const uint32 DIDFT_ABSAXIS         = 0x00000002;
const uint32 DIDFT_AXIS            = 0x00000003;
const uint32 DIDFT_BUTTON          = 0x0000000C;
const uint32 DIDFT_POV             = 0x00000010;
const uint32 DIDFT_ANYINSTANCE     = 0x00FFFF00;

const uint32 DIDF_ABSAXIS          = 0x00000001;
const uint32 DIDF_RELAXIS          = 0x00000002;
const uint32 DIDFT_OPTIONAL        = 0x80000000;

DEFINE_GUID(IID_IDirectInput8A,    0xBF798030,0x483A,0x4DA2,0xAA,0x99,0x5D,0x64,0xED,0x36,0x97,0x00);
DEFINE_GUID(IID_IDirectInputDevice8A,0x54D41080,0xDC15,0x4833,0xA4,0x1B,0x74,0x8F,0x73,0xA3,0x81,0x79);
DEFINE_GUID(GUID_Joystick   ,0x6F1D2B70,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_SysKeyboard,0x6F1D2B61,0xD5A0,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);

DEFINE_GUID(GUID_XAxis,   0xA36D02E0,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_YAxis,   0xA36D02E1,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_ZAxis,   0xA36D02E2,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_RxAxis,  0xA36D02F4,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_RyAxis,  0xA36D02F5,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_RzAxis,  0xA36D02E3,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_Slider,  0xA36D02E4,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);

DEFINE_GUID(GUID_Button,  0xA36D02F0,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);
DEFINE_GUID(GUID_Key,     0x55728220,0xD33C,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);

DEFINE_GUID(GUID_POV,     0xA36D02F2,0xC9F3,0x11CF,0xBF,0xC7,0x44,0x45,0x53,0x54,0x00,0x00);

/*
    These declarations mimic the structures
    exported in dinput8.lib and are used
    in GetDeviceState calls for joysticks
*/

struct G3DJOYDATA { 
    LONG lX;
    LONG lY;
    LONG lZ;
    LONG lRx;
    LONG lRy;
    LONG lRz;
    LONG rglSlider[2];
    DWORD rgdwPOV[4];
    BYTE rgbButtons[32];
}; 

DIOBJECTDATAFORMAT rgodf[ ] = { 
  { &GUID_XAxis, FIELD_OFFSET(G3DJOYDATA, lX),
    DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_YAxis, FIELD_OFFSET(G3DJOYDATA, lY), 
    DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_ZAxis, FIELD_OFFSET(G3DJOYDATA, lZ), 
    DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_RxAxis, FIELD_OFFSET(G3DJOYDATA, lRx), 
    DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_RyAxis, FIELD_OFFSET(G3DJOYDATA, lRy), 
    DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_RzAxis, FIELD_OFFSET(G3DJOYDATA, lRz), 
    DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Slider, FIELD_OFFSET(G3DJOYDATA, rglSlider[0]), 
    DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Slider, FIELD_OFFSET(G3DJOYDATA, rglSlider[1]), 
    DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_POV, FIELD_OFFSET(G3DJOYDATA, rgdwPOV[0]), 
    DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_POV, FIELD_OFFSET(G3DJOYDATA, rgdwPOV[1]), 
    DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_POV, FIELD_OFFSET(G3DJOYDATA, rgdwPOV[2]), 
    DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_POV, FIELD_OFFSET(G3DJOYDATA, rgdwPOV[3]), 
    DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[0]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[1]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[2]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[3]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[4]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[5]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[6]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[7]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[8]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[9]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[10]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[11]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[12]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[13]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[14]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[15]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[16]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[17]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[18]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[19]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[20]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[21]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[22]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[23]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[24]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[25]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[26]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[27]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[28]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[29]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[30]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
  { &GUID_Button, FIELD_OFFSET(G3DJOYDATA, rgbButtons[31]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE, 0, }, 
}; 
const uint32 numJoyObjects = (sizeof(rgodf) / sizeof(rgodf[0])); 

const DIDATAFORMAT G3DJOYDF = { 
    sizeof(DIDATAFORMAT),       // Size of this structure 
    sizeof(DIOBJECTDATAFORMAT), // Size of object data format 
    DIDF_ABSAXIS,               // Absolute axis coordinates 
    sizeof(G3DJOYDATA),         // Size of device data 
    numJoyObjects,              // Number of objects 
    rgodf,                      // And here they are 
}; 

/*
    DirectInput8 Keyboard structures
*/

struct G3DKEYDATA { 
    BYTE keys[256];
}; 

DIOBJECTDATAFORMAT keyodf[ ] = {
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[0]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 0, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[1]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 256, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[2]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 512, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[3]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 768, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[4]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 1024, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[5]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 1280, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[6]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 1536, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[7]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 1792, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[8]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 2048, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[9]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 2304, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[10]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 2560, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[11]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 2816, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[12]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 3072, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[13]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 3328, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[14]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 3584, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[15]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 3840, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[16]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 4096, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[17]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 4352, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[18]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 4608, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[19]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 4864, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[20]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 5120, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[21]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 5376, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[22]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 5632, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[23]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 5888, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[24]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 6144, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[25]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 6400, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[26]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 6656, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[27]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 6912, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[28]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 7168, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[29]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 7424, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[30]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 7680, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[31]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 7936, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[32]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 8192, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[33]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 8448, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[34]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 8704, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[35]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 8960, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[36]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 9216, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[37]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 9472, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[38]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 9728, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[39]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 9984, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[40]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 10240, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[41]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 10496, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[42]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 10752, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[43]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 11008, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[44]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 11264, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[45]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 11520, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[46]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 11776, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[47]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 12032, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[48]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 12288, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[49]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 12544, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[50]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 12800, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[51]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 13056, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[52]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 13312, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[53]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 13568, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[54]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 13824, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[55]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 14080, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[56]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 14336, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[57]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 14592, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[58]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 14848, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[59]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 15104, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[60]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 15360, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[61]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 15616, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[62]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 15872, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[63]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 16128, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[64]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 16384, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[65]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 16640, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[66]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 16896, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[67]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 17152, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[68]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 17408, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[69]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 17664, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[70]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 17920, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[71]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 18176, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[72]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 18432, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[73]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 18688, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[74]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 18944, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[75]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 19200, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[76]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 19456, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[77]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 19712, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[78]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 19968, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[79]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 20224, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[80]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 20480, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[81]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 20736, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[82]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 20992, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[83]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 21248, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[84]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 21504, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[85]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 21760, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[86]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 22016, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[87]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 22272, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[88]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 22528, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[89]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 22784, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[90]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 23040, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[91]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 23296, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[92]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 23552, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[93]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 23808, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[94]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 24064, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[95]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 24320, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[96]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 24576, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[97]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 24832, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[98]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 25088, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[99]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 25344, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[100]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 25600, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[101]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 25856, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[102]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 26112, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[103]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 26368, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[104]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 26624, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[105]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 26880, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[106]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 27136, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[107]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 27392, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[108]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 27648, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[109]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 27904, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[110]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 28160, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[111]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 28416, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[112]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 28672, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[113]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 28928, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[114]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 29184, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[115]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 29440, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[116]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 29696, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[117]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 29952, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[118]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 30208, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[119]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 30464, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[120]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 30720, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[121]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 30976, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[122]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 31232, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[123]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 31488, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[124]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 31744, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[125]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 32000, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[126]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 32256, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[127]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 32512, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[128]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 32768, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[129]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 33024, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[130]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 33280, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[131]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 33536, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[132]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 33792, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[133]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 34048, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[134]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 34304, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[135]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 34560, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[136]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 34816, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[137]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 35072, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[138]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 35328, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[139]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 35584, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[140]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 35840, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[141]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 36096, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[142]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 36352, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[143]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 36608, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[144]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 36864, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[145]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 37120, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[146]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 37376, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[147]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 37632, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[148]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 37888, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[149]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 38144, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[150]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 38400, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[151]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 38656, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[152]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 38912, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[153]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 39168, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[154]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 39424, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[155]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 39680, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[156]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 39936, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[157]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 40192, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[158]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 40448, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[159]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 40704, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[160]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 40960, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[161]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 41216, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[162]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 41472, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[163]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 41728, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[164]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 41984, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[165]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 42240, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[166]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 42496, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[167]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 42752, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[168]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 43008, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[169]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 43264, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[170]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 43520, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[171]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 43776, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[172]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 44032, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[173]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 44288, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[174]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 44544, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[175]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 44800, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[176]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 45056, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[177]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 45312, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[178]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 45568, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[179]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 45824, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[180]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 46080, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[181]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 46336, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[182]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 46592, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[183]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 46848, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[184]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 47104, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[185]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 47360, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[186]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 47616, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[187]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 47872, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[188]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 48128, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[189]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 48384, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[190]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 48640, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[191]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 48896, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[192]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 49152, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[193]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 49408, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[194]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 49664, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[195]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 49920, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[196]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 50176, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[197]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 50432, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[198]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 50688, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[199]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 50944, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[200]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 51200, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[201]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 51456, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[202]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 51712, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[203]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 51968, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[204]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 52224, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[205]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 52480, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[206]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 52736, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[207]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 52992, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[208]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 53248, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[209]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 53504, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[210]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 53760, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[211]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 54016, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[212]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 54272, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[213]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 54528, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[214]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 54784, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[215]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 55040, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[216]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 55296, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[217]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 55552, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[218]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 55808, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[219]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 56064, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[220]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 56320, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[221]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 56576, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[222]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 56832, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[223]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 57088, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[224]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 57344, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[225]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 57600, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[226]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 57856, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[227]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 58112, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[228]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 58368, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[229]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 58624, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[230]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 58880, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[231]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 59136, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[232]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 59392, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[233]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 59648, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[234]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 59904, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[235]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 60160, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[236]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 60416, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[237]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 60672, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[238]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 60928, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[239]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 61184, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[240]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 61440, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[241]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 61696, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[242]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 61952, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[243]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 62208, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[244]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 62464, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[245]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 62720, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[246]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 62976, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[247]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 63232, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[248]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 63488, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[249]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 63744, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[250]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 64000, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[251]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 64256, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[252]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 64512, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[253]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 64768, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[254]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 65024, 0 },
    { &GUID_Key, FIELD_OFFSET(G3DKEYDATA, keys[255]),
    DIDFT_BUTTON | DIDFT_OPTIONAL | 65280, 0 }
};
    
const uint32 numKeyObjects = (sizeof(keyodf) / sizeof(keyodf[0])); 

const DIDATAFORMAT G3DKEYDF = { 
    sizeof(DIDATAFORMAT),       // Size of this structure 
    sizeof(DIOBJECTDATAFORMAT), // Size of object data format 
    DIDF_ABSAXIS,               // Absolute axis coordinates 
    sizeof(G3DKEYDATA),         // Size of device data 
    numKeyObjects,              // Number of objects 
    keyodf,                     // And here they are 
};

/*
    DirectInput8 Keyboard ascii definitions
*/

const uint32 DIK_ESCAPE          = 0x01;
const uint32 DIK_1               = 0x02;
const uint32 DIK_2               = 0x03;
const uint32 DIK_3               = 0x04;
const uint32 DIK_4               = 0x05;
const uint32 DIK_5               = 0x06;
const uint32 DIK_6               = 0x07;
const uint32 DIK_7               = 0x08;
const uint32 DIK_8               = 0x09;
const uint32 DIK_9               = 0x0A;
const uint32 DIK_0               = 0x0B;
const uint32 DIK_MINUS           = 0x0C;    /* - on main keyboard */
const uint32 DIK_EQUALS          = 0x0D;
const uint32 DIK_BACK            = 0x0E;    /* backspace */
const uint32 DIK_TAB             = 0x0F;
const uint32 DIK_Q               = 0x10;
const uint32 DIK_W               = 0x11;
const uint32 DIK_E               = 0x12;
const uint32 DIK_R               = 0x13;
const uint32 DIK_T               = 0x14;
const uint32 DIK_Y               = 0x15;
const uint32 DIK_U               = 0x16;
const uint32 DIK_I               = 0x17;
const uint32 DIK_O               = 0x18;
const uint32 DIK_P               = 0x19;
const uint32 DIK_LBRACKET        = 0x1A;
const uint32 DIK_RBRACKET        = 0x1B;
const uint32 DIK_RETURN          = 0x1C;    /* Enter on main keyboard */
const uint32 DIK_LCONTROL        = 0x1D;
const uint32 DIK_A               = 0x1E;
const uint32 DIK_S               = 0x1F;
const uint32 DIK_D               = 0x20;
const uint32 DIK_F               = 0x21;
const uint32 DIK_G               = 0x22;
const uint32 DIK_H               = 0x23;
const uint32 DIK_J               = 0x24;
const uint32 DIK_K               = 0x25;
const uint32 DIK_L               = 0x26;
const uint32 DIK_SEMICOLON       = 0x27;
const uint32 DIK_APOSTROPHE      = 0x28;
const uint32 DIK_GRAVE           = 0x29;    /* accent grave */
const uint32 DIK_LSHIFT          = 0x2A;
const uint32 DIK_BACKSLASH       = 0x2B;
const uint32 DIK_Z               = 0x2C;
const uint32 DIK_X               = 0x2D;
const uint32 DIK_C               = 0x2E;
const uint32 DIK_V               = 0x2F;
const uint32 DIK_B               = 0x30;
const uint32 DIK_N               = 0x31;
const uint32 DIK_M               = 0x32;
const uint32 DIK_COMMA           = 0x33;
const uint32 DIK_PERIOD          = 0x34;    /* . on main keyboard */
const uint32 DIK_SLASH           = 0x35;    /* / on main keyboard */
const uint32 DIK_RSHIFT          = 0x36;
const uint32 DIK_MULTIPLY        = 0x37;    /* * on numeric keypad */
const uint32 DIK_LMENU           = 0x38;    /* left Alt */
const uint32 DIK_SPACE           = 0x39;
const uint32 DIK_CAPITAL         = 0x3A;
const uint32 DIK_F1              = 0x3B;
const uint32 DIK_F2              = 0x3C;
const uint32 DIK_F3              = 0x3D;
const uint32 DIK_F4              = 0x3E;
const uint32 DIK_F5              = 0x3F;
const uint32 DIK_F6              = 0x40;
const uint32 DIK_F7              = 0x41;
const uint32 DIK_F8              = 0x42;
const uint32 DIK_F9              = 0x43;
const uint32 DIK_F10             = 0x44;
const uint32 DIK_NUMLOCK         = 0x45;
const uint32 DIK_SCROLL          = 0x46;    /* Scroll Lock */
const uint32 DIK_NUMPAD7         = 0x47;
const uint32 DIK_NUMPAD8         = 0x48;
const uint32 DIK_NUMPAD9         = 0x49;
const uint32 DIK_SUBTRACT        = 0x4A;    /* - on numeric keypad */
const uint32 DIK_NUMPAD4         = 0x4B;
const uint32 DIK_NUMPAD5         = 0x4C;
const uint32 DIK_NUMPAD6         = 0x4D;
const uint32 DIK_ADD             = 0x4E;    /* + on numeric keypad */
const uint32 DIK_NUMPAD1         = 0x4F;
const uint32 DIK_NUMPAD2         = 0x50;
const uint32 DIK_NUMPAD3         = 0x51;
const uint32 DIK_NUMPAD0         = 0x52;
const uint32 DIK_DECIMAL         = 0x53;    /* . on numeric keypad */
const uint32 DIK_OEM_102         = 0x56;    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
const uint32 DIK_F11             = 0x57;
const uint32 DIK_F12             = 0x58;
const uint32 DIK_F13             = 0x64;    /*                     (NEC PC98) */
const uint32 DIK_F14             = 0x65;    /*                     (NEC PC98) */
const uint32 DIK_F15             = 0x66;    /*                     (NEC PC98) */
const uint32 DIK_KANA            = 0x70;    /* (Japanese keyboard)            */
const uint32 DIK_ABNT_C1         = 0x73;    /* /? on Brazilian keyboard */
const uint32 DIK_CONVERT         = 0x79;    /* (Japanese keyboard)            */
const uint32 DIK_NOCONVERT       = 0x7B;    /* (Japanese keyboard)            */
const uint32 DIK_YEN             = 0x7D;    /* (Japanese keyboard)            */
const uint32 DIK_ABNT_C2         = 0x7E;    /* Numpad . on Brazilian keyboard */
const uint32 DIK_NUMPADEQUALS    = 0x8D;    /* = on numeric keypad (NEC PC98) */
const uint32 DIK_PREVTRACK       = 0x90;    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
const uint32 DIK_AT              = 0x91;    /*                     (NEC PC98) */
const uint32 DIK_COLON           = 0x92;    /*                     (NEC PC98) */
const uint32 DIK_UNDERLINE       = 0x93;    /*                     (NEC PC98) */
const uint32 DIK_KANJI           = 0x94;    /* (Japanese keyboard)            */
const uint32 DIK_STOP            = 0x95;    /*                     (NEC PC98) */
const uint32 DIK_AX              = 0x96;    /*                     (Japan AX) */
const uint32 DIK_UNLABELED       = 0x97;    /*                        (J3100) */
const uint32 DIK_NEXTTRACK       = 0x99;    /* Next Track */
const uint32 DIK_NUMPADENTER     = 0x9C;    /* Enter on numeric keypad */
const uint32 DIK_RCONTROL        = 0x9D; 
const uint32 DIK_MUTE            = 0xA0;    /* Mute */
const uint32 DIK_CALCULATOR      = 0xA1;    /* Calculator */
const uint32 DIK_PLAYPAUSE       = 0xA2;    /* Play / Pause */
const uint32 DIK_MEDIASTOP       = 0xA4;    /* Media Stop */
const uint32 DIK_VOLUMEDOWN      = 0xAE;    /* Volume - */
const uint32 DIK_VOLUMEUP        = 0xB0;    /* Volume + */
const uint32 DIK_WEBHOME         = 0xB2;    /* Web home */
const uint32 DIK_NUMPADCOMMA     = 0xB3;    /* , on numeric keypad (NEC PC98) */
const uint32 DIK_DIVIDE          = 0xB5;    /* / on numeric keypad */
const uint32 DIK_SYSRQ           = 0xB7;
const uint32 DIK_RMENU           = 0xB8;    /* right Alt */
const uint32 DIK_PAUSE           = 0xC5;    /* Pause */
const uint32 DIK_HOME            = 0xC7;    /* Home on arrow keypad */
const uint32 DIK_UP              = 0xC8;    /* UpArrow on arrow keypad */
const uint32 DIK_PRIOR           = 0xC9;    /* PgUp on arrow keypad */
const uint32 DIK_LEFT            = 0xCB;    /* LeftArrow on arrow keypad */
const uint32 DIK_RIGHT           = 0xCD;    /* RightArrow on arrow keypad */
const uint32 DIK_END             = 0xCF;    /* End on arrow keypad */
const uint32 DIK_DOWN            = 0xD0;    /* DownArrow on arrow keypad */
const uint32 DIK_NEXT            = 0xD1;    /* PgDn on arrow keypad */
const uint32 DIK_INSERT          = 0xD2;    /* Insert on arrow keypad */
const uint32 DIK_DELETE          = 0xD3;    /* Delete on arrow keypad */
const uint32 DIK_LWIN            = 0xDB;    /* Left Windows key */
const uint32 DIK_RWIN            = 0xDC;    /* Right Windows key */
const uint32 DIK_APPS            = 0xDD;    /* AppMenu key */
const uint32 DIK_POWER           = 0xDE;    /* System Power */
const uint32 DIK_SLEEP           = 0xDF;    /* System Sleep */
const uint32 DIK_WAKE            = 0xE3;    /* System Wake */
const uint32 DIK_WEBSEARCH       = 0xE5;    /* Web Search */
const uint32 DIK_WEBFAVORITES    = 0xE6;    /* Web Favorites */
const uint32 DIK_WEBREFRESH      = 0xE7;    /* Web Refresh */
const uint32 DIK_WEBSTOP         = 0xE8;    /* Web Stop */
const uint32 DIK_WEBFORWARD      = 0xE9;    /* Web Forward */
const uint32 DIK_WEBBACK         = 0xEA;    /* Web Back */
const uint32 DIK_MYCOMPUTER      = 0xEB;    /* My Computer */
const uint32 DIK_MAIL            = 0xEC;    /* Mail */
const uint32 DIK_MEDIASELECT     = 0xED;    /* Media Select */

// Define missing Virtual Keys
const uint32 VK_SEMICOLON        = 0xBA; // ;
const uint32 VK_EQUALS	         = 0xBB; // =
const uint32 VK_COMMA	         = 0xBC; // ,
const uint32 VK_MINUS	         = 0xBD; // -
const uint32 VK_PERIOD	         = 0xBE; // .
const uint32 VK_SLASH	         = 0xBF; // /
const uint32 VK_GRAVE	         = 0xC0; // ??
const uint32 VK_LBRACKET	     = 0xDB; // [
const uint32 VK_BACKSLASH	     = 0xDC; // '\'
const uint32 VK_RBRACKET	     = 0xDD; // ]
const uint32 VK_APOSTROPHE	     = 0xDE; // ??
const uint32 VK_BACKTICK	     = 0xDF; // ??


namespace _internal{


// DirectInput8 simulation helper classes

class _DirectInput {
private:

    typedef struct {
        IDirectInputDevice8A*           device;
        std::string                     name;
        bool                            valid;
        unsigned int                    numAxes;
        unsigned int                    numButtons;
        Array<uint32>                   axisOffsets;

    } JoystickInfo;

    IDirectInput8A*                     _directInput;

    Array< JoystickInfo >               _joysticks;

    HWND                                _window;

    // Handle the DirectInput8 joystick enumeration
    static BOOL CALLBACK enumJoysticksCallback(LPCDIDEVICEINSTANCEA lpddi,
                                               LPVOID pvRef) {
    
        JoystickInfo tmpInfo;

        if (((_DirectInput*)pvRef)->_directInput->CreateDevice(lpddi->guidInstance, &tmpInfo.device, NULL) != S_OK) {
            return true;
        }

        if (tmpInfo.device->SetCooperativeLevel(((_DirectInput*)pvRef)->_window, 
                                                (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))
                                                != S_OK) {
            tmpInfo.device->Release();
            return true;
        }

        if (tmpInfo.device->SetDataFormat(&G3DJOYDF) != S_OK) {
            tmpInfo.device->Release();
            return true;
        }

        DIDEVCAPS joystickCaps;
        joystickCaps.dwSize = sizeof(DIDEVCAPS);

        tmpInfo.device->GetCapabilities(&joystickCaps);
        tmpInfo.numButtons = joystickCaps.dwButtons;

        tmpInfo.name = lpddi->tszProductName;

        for (int i = 0; i < 8; ++i) {
            DIDEVICEOBJECTINSTANCE object;
            object.dwSize = sizeof(DIDEVICEOBJECTINSTANCE);
            if (tmpInfo.device->GetObjectInfo(&object, (i * sizeof(LONG)), DIPH_BYOFFSET) == S_OK) {
                tmpInfo.axisOffsets.append(i);
            }
        }

        tmpInfo.numAxes = tmpInfo.axisOffsets.length();

        ((_DirectInput*)pvRef)->_joysticks.append(tmpInfo);

        return true;
    }

public:

    _DirectInput(HWND window) {

        _window = window;

        // Detect DirectInput8 only and create the joystick interfaces
        HMODULE di8Module = ::LoadLibrary("dinput8.dll");
        if (di8Module == NULL) {
            return;
        }

        // DirectInput8Create function pointer
        HRESULT (WINAPI* DirectInput8Create)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);
        DirectInput8Create = (HRESULT (WINAPI*)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN))::GetProcAddress(di8Module, "DirectInput8Create");
        
        if (DirectInput8Create == NULL) {
            ::FreeLibrary(di8Module);
            return;
        }

        if (DirectInput8Create( ::GetModuleHandle(NULL), 
                                DIRECTINPUT_VERSION, 
                                IID_IDirectInput8A, 
                                reinterpret_cast< void** >(&_directInput), 
                                NULL) != S_OK) {
            ::FreeLibrary(di8Module);
            return;
        }
    

        // Setup joystick devices
        _directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, 
                                  enumJoysticksCallback, 
                                  this, 
                                  DIEDFL_ATTACHEDONLY);

        ::FreeLibrary(di8Module);
    }

    static bool libraryExists() {
        HMODULE handle = ::LoadLibrary("dinput8.dll");
        if (handle == NULL) {
            return false;
        } else {
            ::FreeLibrary(handle);
            return true;
        }
    }

    bool getJoystickState(unsigned int joystick, Array<float>& axis, Array<bool>& button) {

        debugAssert( (uint32)_joysticks.length() > joystick );
        debugAssert( _joysticks[joystick].device != NULL );

        G3DJOYDATA data;
        memset(&data, 0, sizeof(G3DJOYDATA));
        
        _joysticks[joystick].device->Acquire();
        _joysticks[joystick].device->Poll();

        if (_joysticks[joystick].device->GetDeviceState(sizeof(G3DJOYDATA), &data) == S_OK) {

            button.resize(_joysticks[joystick].numButtons, false);
            for (uint32 b = 0; (b < _joysticks[joystick].numButtons) && (b < 32); ++b) {
                button[b] = (data.rgbButtons[b] & 128) ? true : false;
            }            

            axis.resize(_joysticks[joystick].numAxes,false);
            for (uint32 a = 0; a < _joysticks[joystick].numAxes; ++a) {
                axis[a] = (float)((double)(((LONG*)&data)[_joysticks[joystick].axisOffsets[a]] - 32768) / 32768.0); 
            }

            return true;
        } else {
            return false;
        }
    }

    void getJoystickInfo(unsigned int joystick, unsigned int& numButtons, unsigned int& numAxes) {

        debugAssert( (uint32)_joysticks.length() > joystick );

        numButtons = _joysticks[joystick].numButtons;
        numAxes = _joysticks[joystick].numAxes;
    }


    unsigned int getNumJoysticks() {
        return _joysticks.length();
    }

    std::string getJoystickName(unsigned int joystick) {

        debugAssert( (uint32)_joysticks.length() > joystick );

        return _joysticks[joystick].name;
    }

    bool joystickExists(unsigned int joystick) {
        
        if ((uint32)_joysticks.length() > joystick) {
            return true;
        }
        return false;
    }

    void clearJoysticks() {
        //Release any joystick interfaces
        for (int i = 0; i < _joysticks.length(); ++i) {
                _joysticks[i].device->Release();
                _joysticks[i].device = NULL;
        }
        _joysticks.clear();
        _joysticks.resize(0, true);
    }

    const Array< JoystickInfo >& getJoystickArray() {
        return _joysticks;
    }
};

} // namespace _internal
} // namespace G3D

#endif //DIRECTINPUT8_H
