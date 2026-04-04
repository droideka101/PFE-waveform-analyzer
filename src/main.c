#include <stdio.h>
#include "waveform.h"
#include "io.h"


int main(void) {
    char filePath[256];
    printf("Waveform Analyzer start menu\n");
    printf("enter the path to waveform file");
    scanf("%255s", filePath);

    read_waveform_from_file(filePath);

    return 0;
}