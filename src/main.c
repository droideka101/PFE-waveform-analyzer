#include <stdio.h>
#include <stdlib.h>

#include "waveform.h"
#include "io.h"


int main(void) {
    //First section handles start menu and taking file name input in command line

    char filePath[256] = "C:/Users/ben/Downloads/power_quality_log.csv";    // hardcoded for testing, comment out for user input
    printf("Waveform Analyzer start menu\n");
    printf("enter the path to waveform file\n> \n");
    //scanf("%255s", filePath);


    WaveformSample *waveData = read_waveform_from_file(filePath);   // calls function from io.c to, returns all data in a struct


    WaveformAnalysisData *analysisData = AnalysePQ(waveData);   // calls function from waveform.c, returns all required data to output



    printf("\nPhase A:\n   RMS: %lf\n   Peak to peak: %lf\n   DC offset: %lf\n", analysisData->phase_A.RMS, analysisData->phase_A.PTP, analysisData->phase_A.DC_offset);
    printf("   Clipping detected at the following timestamps:\n");
    for (int i = 0; i < sizeof(analysisData->phase_A.clipping_timestamps) / sizeof(analysisData->phase_A.clipping_timestamps[0]); i++) {
        if (analysisData->phase_A.clipping_timestamps[i] != 0) {
            printf("%lf ", analysisData->phase_A.clipping_timestamps[i]);
        }
    }

    printf("\n\nPhase B:\n   RMS: %lf\n   Peak to peak: %lf\n   DC offset: %lf\n", analysisData->phase_B.RMS, analysisData->phase_B.PTP, analysisData->phase_B.DC_offset);
    printf("   Clipping detected at the following timestamps:\n");
    for (int i = 0; i < sizeof(analysisData->phase_B.clipping_timestamps) / sizeof(analysisData->phase_B.clipping_timestamps[0]); i++) {
        if (analysisData->phase_B.clipping_timestamps[i] != 0) {
            printf("%lf ", analysisData->phase_B.clipping_timestamps[i]);
        }
    }

    printf("\n\nPhase C:\n   RMS: %lf\n   Peak to peak: %lf\n   DC offset: %lf\n", analysisData->phase_C.RMS, analysisData->phase_C.PTP, analysisData->phase_C.DC_offset);
    printf("   Clipping detected at the following timestamps:\n");
    for (int i = 0; i < sizeof(analysisData->phase_C.clipping_timestamps) / sizeof(analysisData->phase_C.clipping_timestamps[0]); i++) {
        if (analysisData->phase_C.clipping_timestamps[i] != 0) {
            printf("%lf ", analysisData->phase_C.clipping_timestamps[i]);
        }
    }


    // frees up memory of left over structs, then exits program
    free (waveData);
    free(analysisData);
    return 0;
}