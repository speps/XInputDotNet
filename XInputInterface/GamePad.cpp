#include "GamePad.h"
#include <cstdio>

namespace
{
    typedef DWORD( WINAPI *XInputGetStatePointer )( DWORD dwUserIndex, XINPUT_STATE *pState );
    typedef DWORD( WINAPI *XInputSetStatePointer )( DWORD dwUserIndex, XINPUT_VIBRATION *pVibration );

	class XInputLoader
	{
	public:
		XInputLoader()
			: mLoaded(false), mHandle(0), mGetState(0), mSetState(0)
		{
		}

		~XInputLoader()
		{
		}

		void ensureLoaded()
		{
			if (!mLoaded)
			{
				// Keep hold of error codes from each library we try to load.
				DWORD xinput1_3_ErrorCode = 0;
				DWORD xinput1_4_ErrorCode = 0;
				DWORD xinput9_1_ErrorCode = 0;

				// Try XInput 1.3 first as it has all the features we need.
				mHandle = LoadLibrary("xinput1_3.dll");
				xinput1_3_ErrorCode = GetLastError();

				// Look for XInput 1.4 as a backup (newer machines may not have 1.3 at all).
				if(mHandle == NULL)
				{
					mHandle = LoadLibrary("xinput1_4.dll");
					xinput1_4_ErrorCode = GetLastError();
				}

				// Look for XInput 9.1.0 as a last resort! One of the others should exist but we may as well try to load it.
				if(mHandle == NULL)
				{
					mHandle = LoadLibrary("xinput9_1_0.dll");
					xinput9_1_ErrorCode = GetLastError();
				}

				if (mHandle != NULL)
				{
					mGetState = (XInputGetStatePointer)GetProcAddress(mHandle, (LPCSTR)100); // Ordinal 100 is the same as XInputGetState but supports the Guide button.
					mSetState = (XInputSetStatePointer)GetProcAddress(mHandle, "XInputSetState");
					mLoaded = true;
				}
				else
				{
					printf_s("[XInput.NET] Failed to load xinput1_3.dll, xinput1_4.dll and xinput9_1_0.dll (error codes 0x%08x, 0x%08x, 0x%08x respectively; check that \"DirectX End-User Runtimes (June 2010)\""
						" is installed (http://www.microsoft.com/en-us/download/details.aspx?id=8109)\n", xinput1_3_ErrorCode, xinput1_4_ErrorCode, xinput9_1_ErrorCode);
				}
			}
		}

		XInputGetStatePointer mGetState;
		XInputSetStatePointer mSetState;

	private:
		bool mLoaded;
		HMODULE mHandle;
	};

	XInputLoader gXInputLoader;
}

DWORD XInputGamePadGetState(DWORD dwUserIndex, XINPUT_STATE* pState)
{
	gXInputLoader.ensureLoaded();
	if(gXInputLoader.mGetState != NULL)
	{
		return gXInputLoader.mGetState(dwUserIndex, pState);
	}
	else
	{
		return ERROR_DEVICE_NOT_CONNECTED;
	}
}

void XInputGamePadSetState(DWORD dwUserIndex, float leftMotor, float rightMotor)
{
	gXInputLoader.ensureLoaded();
	if(gXInputLoader.mSetState != NULL)
	{
		leftMotor = leftMotor < 0.0f ? 0.0f : (leftMotor > 1.0f ? 1.0f : leftMotor);
		rightMotor = rightMotor < 0.0f ? 0.0f : (rightMotor > 1.0f ? 1.0f : rightMotor);
		XINPUT_VIBRATION vibration = { (WORD)(leftMotor * 65535), (WORD)(rightMotor * 65535) };
		gXInputLoader.mSetState(dwUserIndex, &vibration);
	}
}
