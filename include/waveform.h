//
// Created by ben on 02/04/2026.
//

#ifndef PROJECT_FILE_WAVEFORM_H
#define PROJECT_FILE_WAVEFORM_H
#include "io.h"

typedef struct {
    double max;
    double min;
    double PTP;
    double total_squared;
    double RMS;
    double total;
    double DC_offset;

} PhaseOutputData;

typedef struct {
    PhaseOutputData phase_A;
    PhaseOutputData phase_B;
    PhaseOutputData phase_C;
} WaveformAnalysisData;

WaveformAnalysisData* AnalysePQ(WaveformSample *waveData);

#endif //PROJECT_FILE_WAVEFORM_H