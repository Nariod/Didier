# ProcessInjection

## Internals
Win32 API used:
* CreateToolhelp32Snapshot
* CloseHandle
* OpenProcess 
* VirtualAllocEx
* WriteProcessMemory
* CreateRemoteThread


## How to use
Cross-compile from Linux: 
- `git clone https://github.com/Nariod/Tartocitron.git`
- `cd 5-1-2_process_injection`
- change the shellcode in "main.c"
- `x86_64-w64-mingw32-gcc main.c -o main.exe`


## Overview
Works, not flagged by Windows Defender (last test on 19/02/22). Binary final size is ~90Ko.