// https://youtu.be/HVrGLCkrwCs?list=PLcnkUACTPcVSEYLYjd_tDp8wjJrwxltiy
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
// https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    
    int nExitCode = 0;
    DWORD dwLastError = ERROR_SUCCESS;

    const wchar_t WINDOW_CLASS_NAME[]  = L"Reimu Animate";

    const WNDCLASSEXW windowClass = {
        .cbSize = sizeof(WNDCLASSEXW),
        .style = CS_OWNDC | WS_TILEDWINDOW | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, 
        .lpfnWndProc = &WindowProc, 
        .cbClsExtra = 0, 
        .cbWndExtra = 0, 
        .hInstance = hInstance, 
        .hIcon = NULL, 
        .hCursor = NULL, 
        .hbrBackground = NULL, 
        .lpszMenuName = NULL, 
        .lpszClassName = WINDOW_CLASS_NAME, 
        .hIconSm = NULL
    };

    ATOM atom = RegisterClassExW(&windowClass);

    if (atom == INVALID_ATOM)
    {
        dwLastError = GetLastError();
        return dwLastError;
    }

    // Create the window.

    HWND hwnd = CreateWindowExW(
        WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW, 
        WINDOW_CLASS_NAME, 
        WINDOW_CLASS_NAME, 
        WS_OVERLAPPEDWINDOW,  

        // Size and positions
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 

        NULL,           // Parent window
        NULL,           // Menu
        hInstance,      // Instance handle
        NULL            // Additional application data
    );

    if (hwnd == NULL)
    {
        dwLastError = GetLastError();
        return dwLastError;
    }

    // Choose Pixel Format

    // PIXELFORMATDESCRIPTOR pfd = {
    //     sizeof(PIXELFORMATDESCRIPTOR),
    //     1,
    //     // Flags
    //     PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 
    //     PFD_TYPE_RGBA,        // The framebuffer type: RGBA or palette.
    //     32,                   // Colordepth of the framebuffer.
    //     0, 0, 0, 0, 0, 0,
    //     0,
    //     0,
    //     0,
    //     0, 0, 0, 0,
    //     24,                   // Number of bits for the depthbuffer
    //     8,                    // Number of bits for the stencilbuffer
    //     0,                    // Number of Aux buffers in the framebuffer.
    //     PFD_MAIN_PLANE,
    //     0,
    //     0, 0, 0
    // };

    // int pixelFormatNumber = ChoosePixelFormat(hwnd, &pfd);
    // SetPixelFormat(, pixelFormatNumber, &pfd);

    // Finalize window creation

    ShowWindow(hwnd, SW_MAXIMIZE);

    // Run the message loop

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);

        if (msg.message == WM_QUIT)
            nExitCode = msg.wParam;
    }

    DestroyWindow(hwnd);
    hwnd = NULL;
    UnregisterClassW(MAKEINTATOM(atom), hInstance);
    atom = INVALID_ATOM;

    return nExitCode;
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

    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
