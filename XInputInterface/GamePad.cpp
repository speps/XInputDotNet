#include "GamePad.h"

DWORD XInputGamePadGetState(DWORD dwUserIndex, XINPUT_STATE *pState)
{
    return XInputGetState(dwUserIndex, pState);
}

void XInputGamePadSetState(DWORD dwUserIndex, float leftMotor, float rightMotor)
{
    XINPUT_VIBRATION vibration = { (int)(leftMotor * 65535), (int)(rightMotor * 65535) };
    XInputSetState(dwUserIndex, &vibration);
}