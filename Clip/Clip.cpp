#include "windows.h"
#include "stdio.h"
#include "string.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	size_t cch = wcslen(pCmdLine);
	HGLOBAL hdst = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, (cch + 1) * sizeof(wchar_t));
	PWSTR dst = (PWSTR)GlobalLock(hdst);
	memcpy(dst, pCmdLine, cch * sizeof(wchar_t));
	dst[cch] = 0;
	GlobalUnlock(hdst);

	if (!OpenClipboard(NULL))
		return GetLastError();

	EmptyClipboard();
	if (!SetClipboardData(CF_UNICODETEXT, hdst))
		return GetLastError();
	CloseClipboard();

	return 0;
}