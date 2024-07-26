mkdir ..\executables\windows
cls
gcc ..\source\windows\open_gl.c ..\source\windows\create_window.c -o ..\executables\windows\windows.exe -municode -lgdi32 -lopengl32
..\executables\windows\windows.exe
