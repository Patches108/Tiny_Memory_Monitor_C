#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define DIV 1024

int main() {

    printf("Attempting to access system memory now...");
    printf("\n\nPress ESC to exit memory monitor.\n\n");
    Sleep(1500); // <-- give user time to read message.

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);

    char c;

    if(GlobalMemoryStatusEx(&statex) != 0) {

        // update every second.
        do {
            system("cls"); // start with clearing the terminal.

            printf("| -----------------------------------------------------------------|\n");
            printf("| Label              |          MB          |          GB          |\n");
            printf("| -----------------------------------------------------------------|\n");
            printf("| Total Physical Mem |        %lld         |          %lld          |\n", statex.ullTotalPhys/DIV/DIV, statex.ullTotalPhys/DIV/DIV/DIV);
            printf("| Amount in use      |        %lld         |          %lld          |\n", (statex.ullTotalPhys - statex.ullAvailPhys)/DIV/DIV, (statex.ullTotalPhys - statex.ullAvailPhys)/DIV/DIV/DIV);
            printf("| Percent of mem     |                     %ld%%                     |\n", statex.dwMemoryLoad);
            printf("| -----------------------------------------------------------------|\n");

            // check to see if ESC (code 27) was pressed.
            if(kbhit()){
                c = getch();
                if((int)c == 27) {
                    printf("\n\nESC pressed. Exiting memory monitor.\n\n");
                    break; // exit while.
                }
            }

            Sleep(1000); // wait 1 second.

            // try recalibrate?
            GlobalMemoryStatusEx(&statex);

        } while(1);
    } else {
        printf("There was an error accessing system memory. Exiting...");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// WHAT I LEARNED:
// 1. prinf() is not sufficient for this type of formatting. There must be a C output format that allows neater/more controlled formatting.
// 2. Recalibrate doesn't seem to work -- Memory stays the same even if i open large programs in the background.