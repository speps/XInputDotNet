#include "GamePad.h"

namespace
{
	typedef DWORD (*XInputGetStatePointer)(DWORD dwUserIndex, XINPUT_STATE* pState);
	typedef DWORD (*XInputSetStatePointer)(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);

	class XInputLoader
	{
	public:
		XInputLoader()
			: mHandle(0), mGetState(0), mSetState(0)
		{
			mHandle = LoadLibrary("xinput1_3.dll");

			// Ordinal 100 is the same as XInputGetState but supports the Guide button.
			mGetState = (XInputGetStatePointer)GetProcAddress(mHandle, (LPCSTR)100);

			mSetState = (XInputSetStatePointer)GetProcAddress(mHandle, "XInputSetState");
		}

		~XInputLoader()
		{
			FreeLibrary(mHandle);
		}

		XInputGetStatePointer mGetState;
		XInputSetStatePointer mSetState;

	private:
		HMODULE mHandle;
	};

	XInputLoader gXInputLoader;
}

DWORD XInputGamePadGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
	return gXInputLoader.mGetState(dwUserIndex, pState);
}

void XInputGamePadSetState(DWORD dwUserIndex, float leftMotor, float rightMotor)
{
	XINPUT_VIBRATION vibration = { (int)(leftMotor * 65535), (int)(rightMotor * 65535) };
	gXInputLoader.mSetState(dwUserIndex, &vibration);
}