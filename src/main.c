#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "waveform.h"
#include "io.h"


void printData(WaveformAnalysisData *analysisData) {
    printf("\nPhase A:\n   RMS: %lf\n   Peak to peak: %lf\n   DC offset: %lf\n", analysisData->phase_A.RMS, analysisData->phase_A.PTP, analysisData->phase_A.DC_offset);
    printf("   Clipping detected at the following timestamps:\n");
    for (int i = 0; i < sizeof(analysisData->phase_A.clipping_timestamps) / sizeof(analysisData->phase_A.clipping_timestamps[0]); i++) {
        if (analysisData->phase_A.clipping_timestamps[i] != 0) {
            printf("%lf ", analysisData->phase_A.clipping_timestamps[i]);
        }
    }
    if (analysisData->phase_A.tolerance_compliance) {
        printf("\n   Tolerance compliance: True\n");
    } else {
        printf("\n   Tolerance compliance: False\n");
    }

    printf("\n\nPhase B:\n   RMS: %lf\n   Peak to peak: %lf\n   DC offset: %lf\n", analysisData->phase_B.RMS, analysisData->phase_B.PTP, analysisData->phase_B.DC_offset);
    printf("   Clipping detected at the following timestamps:\n");
    for (int i = 0; i < sizeof(analysisData->phase_B.clipping_timestamps) / sizeof(analysisData->phase_B.clipping_timestamps[0]); i++) {
        if (analysisData->phase_B.clipping_timestamps[i] != 0) {
            printf("%lf ", analysisData->phase_B.clipping_timestamps[i]);
        }
    }
    if (analysisData->phase_B.tolerance_compliance) {
        printf("\n   Tolerance compliance: True\n");
    } else {
        printf("\n   Tolerance compliance: False\n");
    }

    printf("\n\nPhase C:\n   RMS: %lf\n   Peak to peak: %lf\n   DC offset: %lf\n", analysisData->phase_C.RMS, analysisData->phase_C.PTP, analysisData->phase_C.DC_offset);
    printf("   Clipping detected at the following timestamps:\n");
    for (int i = 0; i < sizeof(analysisData->phase_C.clipping_timestamps) / sizeof(analysisData->phase_C.clipping_timestamps[0]); i++) {
        if (analysisData->phase_C.clipping_timestamps[i] != 0) {
            printf("%lf ", analysisData->phase_C.clipping_timestamps[i]);
        }
    }
    if (analysisData->phase_C.tolerance_compliance) {
        printf("\n   Tolerance compliance: True\n");
    } else {
        printf("\n   Tolerance compliance: False\n");
    }
}

int main(int argc, char *argv[]) {



    WaveformSample *waveData = read_waveform_from_file(argv[1]);   // calls function from io.c to, returns all data in a struct


    WaveformAnalysisData *analysisData = AnalysePQ(waveData);   // calls function from waveform.c, returns all required data to output

    //printData(analysisData);   // prints the data to the console in a readable format

    output_data_to_file(analysisData);

    printf("\nData analysis complete\n");

    printf("\nData output to file complete\n");

    // frees up memory of left over structs, then exits program
    free (waveData);
    free(analysisData);
    return 0;
}

