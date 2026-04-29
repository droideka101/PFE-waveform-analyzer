//
// Created by ben on 02/04/2026.
//

#ifndef PROJECT_FILE_IO_H
#define PROJECT_FILE_IO_H

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

WaveformSample* read_waveform_from_file(const char* filePath);

#endif //PROJECT_FILE_IO_H