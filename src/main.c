#include <stdio.h>
#include <stdlib.h>

#include "waveform.h"
#include "io.h"


int main(void) {
    char filePath[256];
    printf("Waveform Analyzer start menu\n");
    printf("enter the path to waveform file\n> ");
    scanf("%255s", filePath);

    WaveformSample *waveData = read_waveform_from_file(filePath);

    AnalysisOutputData *outputData = AnalysePQ(waveData);

    printf("RMS Phase A: %lf\n", outputData->RMS_phase_A);
    printf("RMS Phase B: %lf\n", outputData->RMS_phase_B);
    printf("RMS Phase C: %lf\n", outputData->RMS_phase_C);
    printf("PTP Phase A: %lf\n", outputData->PTP_phase_A);
    printf("PTP Phase B: %lf\n", outputData->PTP_phase_B);
    printf("PTP Phase C: %lf\n", outputData->PTP_phase_C);

    free (waveData);
    return 0;
}