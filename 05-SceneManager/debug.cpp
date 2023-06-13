#include <Windows.h>
#include "debug.h"
#include "AssetIDs.h"

HWND _hwnd = NULL;

void DebugOut(const wchar_t* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[MAX_SCENE_LINE_MORE];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

void DebugOutTitle(const wchar_t* fmt, ...)
{
	wchar_t s[MAX_SCENE_LINE];
	VA_PRINTS(s);
	SetWindowText(_hwnd, s);
}

void SetDebugWindow(HWND hwnd)
{
	_hwnd = hwnd;
}