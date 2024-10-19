#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int argc = 0;
	LPWSTR* lpShit;
	int crap = 0;
	wchar_t message[256];
	int i = 1;

	lpShit = CommandLineToArgvW(GetCommandLine(), &argc);
	if (argc < 2)
	{
		MessageBox(NULL, L"Drag and drop font file(s) onto .exe.", L"Usage", MB_OK | MB_ICONINFORMATION);
		return -1;
	}
	
	for (i = 1; i < argc; ++i)
	{
		if (AddFontResource(lpShit[i]) == 0)
		{
			MessageBox(NULL, lpShit[i], L"Failed to load font", MB_OK | MB_ICONERROR);
			goto removecrap;
			return i;
		}
		/* SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0); */
		++crap;
	}
	/* SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0); */
	wsprintfW(message, L"%d fonts loaded successfully.", crap);
	MessageBox(NULL, L"Close this box to unload fonts.", message, MB_OK | MB_ICONINFORMATION);
removecrap:
	/* SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0); */
	for (i = 1; i < argc; ++i)
	{
		RemoveFontResource(lpShit[i]);
		/* SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0); */
	}
	/* SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0); */

	return 0;
}

void WinMainCRTStartup()
{
	ExitProcess(WinMain(GetModuleHandle(NULL), NULL, NULL, 0));
}