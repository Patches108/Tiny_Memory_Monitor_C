#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>

#define DIV 1024
#define SPACING 7

int main() {

    // 1. get memory details every second.
    // 2. output to foramtted table.

    int exitLoop = 1;
    char cKey;

    printf("*********************\n");
    printf("TINY MEMORY MONITOR\n");
    printf("Press ESC to exit.\n");
    printf("*********************\n\n");
    Sleep(2000);    // <-- give user time to read the above.

    do {

        system("cls"); // clear screen.

        // 1. get memory details.
        MEMORYSTATUSEX mem;
        mem.dwLength = sizeof (mem);
        GlobalMemoryStatusEx (&mem);

        // get memory details and display them.
        DWORD memLoad = mem.dwMemoryLoad;
        DWORDLONG ttlPhys = mem.ullTotalPhys;
        DWORDLONG avlPhys = mem.ullAvailPhys;

        printf("**********************************************\n");
        _tprintf (TEXT("There is %*ld percent of memory in use.\n"), SPACING, memLoad);
        _tprintf (TEXT("There is %*llu GBs of total physical memory.\n"), SPACING, ttlPhys/DIV/DIV);
        _tprintf (TEXT("There is %*llu GBs of available memory.\n"), SPACING, avlPhys/DIV/DIV);
        printf("**********************************************\n");

        
        // check if ESC key pressed.
        if(kbhit()){
            cKey = getch();
            if(cKey == 27) {      // code 27 should be ESC key. yes, it is.
                printf("ESC pressed. Exiting...\n");
                exitLoop = 0;
            }
        }

        Sleep(1000);    // wait 1 second.

    } while(exitLoop != 0);

    return EXIT_SUCCESS;
}