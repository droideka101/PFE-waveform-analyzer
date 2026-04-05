//
// Created by ben on 02/04/2026.
//

#ifndef PROJECT_FILE_IO_H
#define PROJECT_FILE_IO_H

typedef struct {
    float timestamp;
    float phase_A_voltage;
    float phase_B_voltage;
    float phase_C_voltage;
    float line_current;
    float frequency;
    float power_factor;
    float thd_percent;
} WaveformSample;

WaveformSample* read_waveform_from_file(const char* filePath);

#endif //PROJECT_FILE_IO_H