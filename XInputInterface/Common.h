#ifndef _XINPUT_INTERFACE_COMMON_H
#define _XINPUT_INTERFACE_COMMON_H

#ifdef XI_EXPORTS
    #define XI_EXPORT __declspec(dllexport)
#else
    #define XI_EXPORT __declspec(dllimport)
#endif

#endif