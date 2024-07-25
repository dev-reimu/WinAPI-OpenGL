// https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <GL/GL.h>

#pragma comment (lib, "opengl32.lib")



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    MSG msg          = {0};
	WNDCLASSW wc      = {0}; 
	wc.lpfnWndProc   = WindowProc;
	wc.hInstance     = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = L"Reimu Animate";
	wc.style = CS_OWNDC;

    ATOM atom = RegisterClassW(&wc);
    if (atom == INVALID_ATOM)
        return 1;

    HWND hwnd = CreateWindowExW(0, wc.lpszClassName, L"Reimu Animate", 
        CS_OWNDC | WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
        NULL, NULL, hInstance, NULL);
    if (hwnd == NULL)
        return 1;
    ShowWindow(hwnd, SW_MAXIMIZE);
    
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
        
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOWTEXT));
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_CREATE: {
                PIXELFORMATDESCRIPTOR pfd = {
                    sizeof(PIXELFORMATDESCRIPTOR),
                    1,
                    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
                    PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
                    32,                   // Colordepth of the framebuffer.
                    0, 0, 0, 0, 0, 0,
                    0,
                    0,
                    0,
                    0, 0, 0, 0,
                    24,                   // Number of bits for the depthbuffer
                    8,                    // Number of bits for the stencilbuffer
                    0,                    // Number of Aux buffers in the framebuffer.
                    PFD_MAIN_PLANE,
                    0,
                    0, 0, 0
                };

                HDC ourWindowHandleToDeviceContext = GetDC(hwnd);
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
