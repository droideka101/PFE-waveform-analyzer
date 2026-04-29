#include <stdio.h>
#include <stdlib.h>

#include "waveform.h"
#include "io.h"


int main(void) {
    char filePath[256] = "C:/Users/ben/Downloads/power_quality_log.csv";    // hardcoded for testing, comment out for user input
    printf("Waveform Analyzer start menu\n");
    printf("enter the path to waveform file\n> \n");
    //scanf("%255s", filePath);


    WaveformSample *waveData = read_waveform_from_file(filePath);


    WaveformAnalysisData *analysisData = AnalysePQ(waveData);

    printf("PhaseA RMS: %lf\nPhaseA PTP: %lf\n", analysisData->phase_A.RMS, analysisData->phase_A.PTP);
    printf("PhaseB RMS: %lf\nPhaseB PTP: %lf\n", analysisData->phase_B.RMS, analysisData->phase_B.PTP);
    printf("PhaseC RMS: %lf\nPhaseC PTP: %lf\n", analysisData->phase_C.RMS, analysisData->phase_C.PTP);


    free (waveData);
    free(analysisData);
    return 0;
}