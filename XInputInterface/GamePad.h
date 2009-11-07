#ifndef _XINPUT_INTERFACE_GAMEPAD_H
#define _XINPUT_INTERFACE_GAMEPAD_H

#include "Common.h"

#include <windows.h>
#include <XInput.h>

extern "C"
{

    XI_EXPORT DWORD XInputGamePadGetState(DWORD dwUserIndex, XINPUT_STATE *pState);
    XI_EXPORT void XInputGamePadSetState(DWORD dwUserIndex, float leftMotor, float rightMotor);

}

#endif