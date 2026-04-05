//
// Created by ben on 02/04/2026.
//
#include "io.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 1000

WaveformSample* read_waveform_from_file(const char* filePath) {

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }


    WaveformSample *waveData = malloc(MAX_ROWS * sizeof(WaveformSample));
    if (!waveData) {
        perror("malloc failed");
        exit(1);
    }

    char line[256];

    fgets(line, sizeof(line), file); //skip headers

    size_t count = 0;

    while (fgets(line, sizeof(line), file) != NULL && count < MAX_ROWS) {
        char *token;

        token = strtok(line, ",");
        waveData[count].timestamp = atof(token);

        token = strtok(NULL, ",");
        waveData[count].phase_A_voltage = atof(token);

        token = strtok(NULL, ",");
        waveData[count].phase_B_voltage = atof(token);

        token = strtok(NULL, ",");
        waveData[count].phase_C_voltage = atof(token);

        token = strtok(NULL, ",");
        waveData[count].line_current = atof(token);

        token = strtok(NULL, ",");
        waveData[count].frequency = atof(token);

        token = strtok(NULL, ",");
        waveData[count].power_factor = atof(token);

        token = strtok(NULL, ",");
        waveData[count].thd_percent = atof(token);


        count++;
    }


    fclose(file);
    return waveData;
}
