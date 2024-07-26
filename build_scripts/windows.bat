mkdir ..\executables\windows
cls
gcc ..\source\windows\create_window.c ..\source\windows\open_gl.c -o ..\executables\windows\windows.exe -municode -lgdi32 -lopengl32
..\executables\windows\windows.exe
