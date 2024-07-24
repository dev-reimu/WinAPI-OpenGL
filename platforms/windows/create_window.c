// https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    // Register the window class

    DWORD dwLastError = ERROR_SUCCESS;
    
    const wchar_t WINDOW_CLASS_NAME[]  = L"Reimu Animate";

    const WNDCLASSW wc = {
        .lpfnWndProc   = WindowProc, 
        .hInstance     = hInstance, 
        .lpszClassName = WINDOW_CLASS_NAME, 
        .cbWndExtra    = sizeof(HDC) + sizeof(HGLRC)
    };

    ATOM atom = RegisterClassW(&wc);

    if (atom == INVALID_ATOM)
    {
        dwLastError = GetLastError();
        return -1;
    }

    // Create the window

    HWND hWnd = CreateWindowExW(
        0, 
        WINDOW_CLASS_NAME,          // Window class
        WINDOW_CLASS_NAME,          // Window title

        // Window style
        CS_OWNDC | WS_TILEDWINDOW | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 

        // Size and positions
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 

        NULL,           // Parent window
        NULL,           // Menu
        hInstance,      // Instance handle
        NULL            // Additional window data
    );

    if (hWnd == NULL)
    {
        dwLastError = GetLastError();
        return -1;
    }

    ShowWindow(hWnd, SW_MAXIMIZE);

    // Run the message loop

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                // All painting occurs here, between BeginPaint and EndPaint.

                FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

                EndPaint(hwnd, &ps);
            }
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
