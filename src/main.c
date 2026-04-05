#include <stdio.h>
#include <stdlib.h>

#include "waveform.h"
#include "io.h"


void printData(WaveformSample *waveData) {
    int count = 0;
    for (count =0; count < 1000; count++) {

        printf("%f, %f, %f, %f, %f, %f, %f, %f\n", waveData[count].timestamp, waveData[count].phase_A_voltage, waveData[count].phase_B_voltage, waveData[count].phase_C_voltage,
        waveData[count].line_current, waveData[count].frequency, waveData[count].power_factor, waveData[count].thd_percent);

    }
}

int main(void) {
    char filePath[256];
    printf("Waveform Analyzer start menu\n");
    printf("enter the path to waveform file");
    scanf("%255s", filePath);

    WaveformSample *waveData;
    waveData = read_waveform_from_file(filePath);

    printData(waveData);



    free (waveData);

    return 0;
}