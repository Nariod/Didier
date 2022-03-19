# SimpleInjector

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
- `x86_64-w64-mingw32-gcc main.c -o main.exe`


## Overview
Last test on 19/03/2022.
Works, but is detected by Windows Defender as "Trojan:Script/Sabsik.TE.A!ml". Binary final size is ~90Ko.