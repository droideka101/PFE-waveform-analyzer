//
// Created by ben on 02/04/2026.
//

#ifndef PROJECT_FILE_IO_H
#define PROJECT_FILE_IO_H

#include <stdbool.h>

#define MAX_ROWS 1000

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} WaveformSample;

typedef struct {
    double max;
    double min;
    double PTP;
    double total_squared;
    double RMS;
    double total;
    double DC_offset;
    double clipping_timestamps[MAX_ROWS];
    bool tolerance_compliance;
} PhaseOutputData;

typedef struct {
    PhaseOutputData phase_A;
    PhaseOutputData phase_B;
    PhaseOutputData phase_C;
} WaveformAnalysisData;

WaveformSample* read_waveform_from_file(const char* filePath);

void output_data_to_file(WaveformAnalysisData *analysisData);

#endif //PROJECT_FILE_IO_H