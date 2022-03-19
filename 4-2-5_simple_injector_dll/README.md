# SimpleInjectorDLL

## Internals
Win32 API used:
* GetCurrentProcessId
* VirtualAlloc 
* CreateThread
* WaitForSingleObject


## How to use
Cross-compile from Linux: 
- `git clone https://github.com/Nariod/Chocolatine.git`
- `cd 4-2-4_simple_injector`
- change the shellcode in "main.c"
- `x86_64-w64-mingw32-gcc -shared main.c -o main.exe`
On target machine:
- `rundll32.exe main.dll, omelette`


## Overview
Last test on 19/03/2022.
Works, not detected by Windows Defender. Binary final size is ~80Ko.