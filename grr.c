#include <windows.h>

// Use Common Controls version 6.0 instead of ShellMessageBox to provide modern look with more compatibility.
// https://learn.microsoft.com/en-us/windows/win32/controls/cookbook-overview#using-manifests-or-directives-to-ensure-that-visual-styles-can-be-applied-to-applications
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argc = 0;
    LPWSTR* lpFont;
    int countLoad = 0;
    wchar_t message[256];
    int i = 1;

    lpFont = CommandLineToArgvW(GetCommandLine(), &argc);
    if (argc < 2)
    {
        MessageBox(NULL, L"Drag and drop font file(s) onto .exe.", L"Usage", MB_OK | MB_ICONINFORMATION);
        return -1;
    }

    for (i = 1; i < argc; ++i)
    {
        if (AddFontResource(lpFont[i]) == 0)
        {
            MessageBox(NULL, lpFont[i], L"Failed to load font", MB_OK | MB_ICONERROR);
            goto removefont;
            return i;
        }
        SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
        ++countLoad;
    }
    SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
    wsprintfW(message, L"%d fonts loaded successfully.", countLoad);
    MessageBox(NULL, L"Close this box to unload fonts.", message, MB_OK | MB_ICONINFORMATION);
removefont:
    SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
    for (i = 1; i < argc; ++i)
    {
        RemoveFontResource(lpFont[i]);
        SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
    }
    SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

    return 0;
}

void WinMainCRTStartup()
{
    ExitProcess(WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWDEFAULT));
}
