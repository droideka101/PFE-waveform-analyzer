//
// Created by ben on 02/04/2026.
//
#include "waveform.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void calculateRMS(double sampleVoltage, PhaseOutputData *Phase, int rowNum) {
    /// adds all the voltage samples to TotalSquared after being squared
    /// once the all added, applies the mean and square root to get the RMS value

    // printf("DEBUG: RowNum: %d  Sample Voltage: %lf\n", rowNum, sampleVoltage);
    Phase->total_squared += sampleVoltage * sampleVoltage;

    if (rowNum == MAX_ROWS) {
        Phase->RMS = sqrt(Phase->total_squared / MAX_ROWS);
    }
}

void calculatePeakToPeak(double sampleVoltage, PhaseOutputData *Phase, int rowNum) {
    /// checks if each sample voltage is higher or lower than the current max/min
    /// once all values checked, subtracts lowest from highest, giving the peak to peak (amplitude)

    if (sampleVoltage > Phase->max) Phase->max = sampleVoltage;
    if (sampleVoltage < Phase->min) Phase->min = sampleVoltage;

    if (rowNum == MAX_ROWS) {
        Phase->PTP = Phase->max - Phase->min;
    }
}


void calculateDCOffset(double sampleVoltage, PhaseOutputData *Phase, int rowNum) {
    Phase->total += sampleVoltage;
    if (rowNum == MAX_ROWS) {
        Phase->DC_offset = Phase->total / MAX_ROWS;
    }
}

WaveformAnalysisData* AnalysePQ(WaveformSample *waveData) {

    WaveformAnalysisData *analysisData = calloc(1 * sizeof(WaveformAnalysisData), MAX_ROWS);
    if (!analysisData) {
        perror("calloc failed");
        exit(1);
    }

    PhaseOutputData *PhaseA = calloc(1 * sizeof(PhaseOutputData), MAX_ROWS);
    if (!PhaseA) {
        perror("calloc failed");
        exit(1);
    }
    PhaseOutputData *PhaseB = calloc(1 * sizeof(PhaseOutputData), MAX_ROWS);
    if (!PhaseB) {
        perror("calloc failed");
        exit(1);
    }
    PhaseOutputData *PhaseC = calloc(1 * sizeof(PhaseOutputData), MAX_ROWS);
    if (!PhaseC) {
        perror("calloc failed");
        exit(1);
    }

    for (WaveformSample *ptr = &waveData[0]; ptr < &waveData[MAX_ROWS]; ptr++) {
        int rowNum = ptr - &waveData[0] + 1;
        calculateRMS(ptr->phase_A_voltage, PhaseA, rowNum);
        calculatePeakToPeak(ptr->phase_A_voltage, PhaseA, rowNum);
        calculateDCOffset(ptr->phase_A_voltage, PhaseA, rowNum);

        calculateRMS(ptr->phase_B_voltage, PhaseB, rowNum);
        calculatePeakToPeak(ptr->phase_B_voltage, PhaseB, rowNum);
        calculateDCOffset(ptr->phase_B_voltage, PhaseB, rowNum);

        calculateRMS(ptr->phase_C_voltage, PhaseC, rowNum);
        calculatePeakToPeak(ptr->phase_C_voltage, PhaseC, rowNum);
        calculateDCOffset(ptr->phase_C_voltage, PhaseC, rowNum);
    }

    analysisData->phase_A = *PhaseA;
    analysisData->phase_B = *PhaseB;
    analysisData->phase_C = *PhaseC;

    free(PhaseA);
    free(PhaseB);
    free(PhaseC);

    return analysisData;
}


