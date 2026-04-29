//
// Created by ben on 02/04/2026.
//
#include "waveform.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void calculateRMS(double sampleVoltage, PhaseOutputData *Phase, int rowNum) {
    // printf("DEBUG: RowNum: %d  Sample Voltage: %lf\n", rowNum, sampleVoltage);
    Phase->TotalSquared += sampleVoltage * sampleVoltage;

    if (rowNum == MAX_ROWS) {
        Phase->RMS = sqrt(Phase->TotalSquared / MAX_ROWS);
    }
}

void calculatePeakToPeak2(double sampleVoltage, PhaseOutputData *Phase, int rowNum) {
    if (sampleVoltage > Phase->Max) Phase->Max = sampleVoltage;
    if (sampleVoltage < Phase->Min) Phase->Min = sampleVoltage;

    if (rowNum == MAX_ROWS) {
        Phase->PTP = Phase->Max - Phase->Min;
    }
}

WaveformAnalysisData* AnalysePQ(WaveformSample *waveData) {

    WaveformAnalysisData *analysisData = calloc(1 * sizeof(WaveformAnalysisData), MAX_ROWS);
    if (!analysisData) {
        perror("malloc failed");
        exit(1);
    }

    PhaseOutputData *PhaseA = calloc(1 * sizeof(PhaseOutputData), MAX_ROWS);
    if (!PhaseA) {
        perror("malloc failed");
        exit(1);
    }
    PhaseOutputData *PhaseB = calloc(1 * sizeof(PhaseOutputData), MAX_ROWS);
    if (!PhaseB) {
        perror("malloc failed");
        exit(1);
    }
    PhaseOutputData *PhaseC = calloc(1 * sizeof(PhaseOutputData), MAX_ROWS);
    if (!PhaseC) {
        perror("malloc failed");
        exit(1);
    }

    for (WaveformSample *ptr = &waveData[0]; ptr < &waveData[MAX_ROWS]; ptr++) {
        int rowNum = ptr - &waveData[0] + 1;
        calculateRMS(ptr->phase_A_voltage, PhaseA, rowNum);
        calculatePeakToPeak2(ptr->phase_A_voltage, PhaseA, rowNum);

        calculateRMS(ptr->phase_B_voltage, PhaseB, rowNum);
        calculatePeakToPeak2(ptr->phase_B_voltage, PhaseB, rowNum);

        calculateRMS(ptr->phase_C_voltage, PhaseC, rowNum);
        calculatePeakToPeak2(ptr->phase_C_voltage, PhaseC, rowNum);
    }

    analysisData->phase_A = *PhaseA;
    analysisData->phase_B = *PhaseB;
    analysisData->phase_C = *PhaseC;

    free(PhaseA);
    free(PhaseB);
    free(PhaseC);

    return analysisData;
}


