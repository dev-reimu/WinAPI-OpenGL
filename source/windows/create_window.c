// https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <GL/gl.h>
#include "open_gl.h"

#pragma comment (lib, "opengl32.lib")



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOWTEXT));
            EndPaint(hwnd, &ps);
            return 0;
        }

        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	WNDCLASSW wc        = {0};
	wc.lpfnWndProc      = WindowProc;
    wc.style            = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wc.hInstance        = hInstance;
	wc.hbrBackground    = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName    = L"Reimu_Animate_Window";

    ATOM atom = RegisterClassW(&wc);
    if (atom == INVALID_ATOM)
        return 1;

    HWND window = CreateWindowExW(0, wc.lpszClassName, L"Reimu Animate", 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
        NULL, NULL, hInstance, NULL);
    if (window == NULL)
        return 1;
    ShowWindow(window, SW_MAXIMIZE);

    HDC dc = GetDC(window);
  
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;
    int format = ChoosePixelFormat(dc, &pfd);
    SetPixelFormat(dc, format, &pfd);
    
    HGLRC glrc = wglCreateContext(dc);
    wglMakeCurrent(dc, glrc);

    MSG msg = {0};

    while (TRUE) {

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
            if (msg.message == WM_QUIT)
                return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        opengl_init(dc);
    }

    return 0;
}
