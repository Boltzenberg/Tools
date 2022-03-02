#include "windows.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Usage:  clip \"Text to put on the clipboard\"\n");
		return -1;
	}

	size_t len = strlen(argv[1]);
	HGLOBAL hdst = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, len + 1);
	char* dst = (char*)GlobalLock(hdst);
	memcpy(dst, argv[1], len);
	dst[len] = 0;
	GlobalUnlock(hdst);

	if (!OpenClipboard(NULL))
		return GetLastError();

	EmptyClipboard();
	if (!SetClipboardData(CF_TEXT, hdst))
		return GetLastError();
	CloseClipboard();

	printf("Done!\n");
	return 0;
}