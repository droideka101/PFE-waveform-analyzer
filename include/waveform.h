//
// Created by ben on 02/04/2026.
//

#ifndef PROJECT_FILE_WAVEFORM_H
#define PROJECT_FILE_WAVEFORM_H
#include "io.h"

typedef struct {
    double RMS_phase_A;
    double RMS_phase_B;
    double RMS_phase_C;
    double PTP_phase_A;
    double PTP_phase_B;
    double PTP_phase_C;
    // int DCOffset;
    // int clipping;
    // int toleranceCompliance;
} AnalysisOutputData;

AnalysisOutputData* AnalysePQ(WaveformSample *waveData);

#endif //PROJECT_FILE_WAVEFORM_H