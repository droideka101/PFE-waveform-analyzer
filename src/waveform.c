//
// Created by ben on 02/04/2026.
//
#include "waveform.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double computePhaseRMS(WaveformSample *waveData, float *phaseFirstPtr) {
    double root, mean, squareSum;
    squareSum = 0;

    char *bytePtr = (char*)phaseFirstPtr;
    size_t stride = sizeof(WaveformSample);

    for (int i = 0; i < 1000; i++) {
        float val = *(float*)bytePtr;
        // printf("val = %f\n", val);      //console log for debugging
        squareSum += val * val;
        bytePtr += stride;
    }

    mean = squareSum / MAX_ROWS;

    root = sqrt(mean);

    return root;
}

double calculatePeakToPeak(WaveformSample *waveData, float *phaseFirstPtr) {
    double min, max, PTP = 0;

    char *bytePtr = (char*)phaseFirstPtr;
    size_t stride = sizeof(WaveformSample);

    for (int i = 0; i < 1000; i++) {
        float val = *(float*)bytePtr;

        if (val < min) min = val;
        if (val > max) max = val;

        bytePtr += stride;
    }
    PTP = max - min;
    return PTP;
}

AnalysisOutputData* AnalysePQ(WaveformSample *waveData) {

    AnalysisOutputData *outputData = malloc(1 * sizeof(AnalysisOutputData));
    if (!outputData) {
        perror("malloc failed");
        exit(1);
    }

    // debug for printing out whole table
    // for (WaveformSample *ptr = &waveData[0]; ptr < &waveData[MAX_ROWS]; ptr++) {
    //     int rowNum = ptr - &waveData[0];
    //
    //     printf("%d, %f, %f, %f, %f, %f, %f, %f, %f\n",
    //         rowNum,
    //         ptr->timestamp,
    //         ptr->phase_A_voltage,
    //         ptr->phase_B_voltage,
    //         ptr->phase_C_voltage,
    //         ptr->line_current,
    //         ptr->frequency,
    //         ptr->power_factor,
    //         ptr->thd_percent);
    //
    // }

    WaveformSample *ptr = waveData;

    double RMSA = computePhaseRMS(waveData, &ptr->phase_A_voltage);
    outputData->RMS_phase_A = RMSA;

    double RMSB = computePhaseRMS(waveData, &ptr->phase_B_voltage);
    outputData->RMS_phase_B = RMSB;

    double RMSC = computePhaseRMS(waveData, &ptr->phase_C_voltage);
    outputData->RMS_phase_C = RMSC;

    double PTPA = calculatePeakToPeak(waveData, &ptr->phase_A_voltage);
    outputData->PTP_phase_A = PTPA;

    double PTPB = calculatePeakToPeak(waveData, &ptr->phase_B_voltage);
    outputData->PTP_phase_B = PTPB;

    double PTPC = calculatePeakToPeak(waveData, &ptr->phase_C_voltage);
    outputData->PTP_phase_C = PTPC;


    return outputData;
}


