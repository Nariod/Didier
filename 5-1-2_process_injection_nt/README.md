# ProcessInjectionNt

## Internals
Win32 API used:
* CreateToolhelp32Snapshot
* CloseHandle
* NtCreateSection
* NtMapViewOfSection
* NtOpenProcess
* NtUnmapViewOfSection
* NtClose
* NtCreateThreadEx


## How to use
Cross-compile from Linux: 
- `git clone https://github.com/Nariod/Tartocitron.git`
- `cd 5-1-2_process_injection`
- change the shellcode in "main.c"
- `x86_64-w64-mingw32-gcc main.c -o main.exe`


## Overview
WIP