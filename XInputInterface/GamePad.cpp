#include "GamePad.h"
#include <cstdio>

namespace
{
	typedef DWORD (*XInputGetStatePointer)(DWORD dwUserIndex, XINPUT_STATE* pState);
	typedef DWORD (*XInputSetStatePointer)(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration);

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
				mHandle = LoadLibrary("xinput1_3.dll");
				if (mHandle != NULL)
				{
					mGetState = (XInputGetStatePointer)GetProcAddress(mHandle, (LPCSTR)100); // Ordinal 100 is the same as XInputGetState but supports the Guide button.
					mSetState = (XInputSetStatePointer)GetProcAddress(mHandle, "XInputSetState");
					mLoaded = true;
				}
				else
				{
					printf_s("[XInput.NET] Failed to loaded xinput1_3.dll (error code 0x%08x, check that DirectX End-User Runtimes"
						" is installed (http://www.microsoft.com/en-us/download/details.aspx?id=8109)\n", GetLastError());
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
	return gXInputLoader.mGetState(dwUserIndex, pState);
}

void XInputGamePadSetState(DWORD dwUserIndex, float leftMotor, float rightMotor)
{
	gXInputLoader.ensureLoaded();
	XINPUT_VIBRATION vibration = { (int)(leftMotor * 65535), (int)(rightMotor * 65535) };
	gXInputLoader.mSetState(dwUserIndex, &vibration);
}