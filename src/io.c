//
// Created by ben on 02/04/2026.
//
#include "io.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


WaveformSample* read_waveform_from_file(const char* filePath) {

    // opens file, throws error if any problems occur with reading the data
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // allocates memory for the data, returns error if malloc fails
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

void output_data_to_file(WaveformAnalysisData *analysisData) {

    FILE *file = fopen("results.txt", "w");

    fprintf(file, "Phase A Analysis:\n");
    fprintf(file, "   RMS: %lf\n", analysisData->phase_A.RMS);
    fprintf(file, "   Peak to Peak: %lf\n", analysisData->phase_A.PTP);
    fprintf(file, "   DC Offset: %lf\n", analysisData->phase_A.DC_offset);
    fprintf(file, "   Clipping detected at the following timestamps:\n");

    for (int i = 0; i < sizeof(analysisData->phase_A.clipping_timestamps) / sizeof(analysisData->phase_A.clipping_timestamps[0]); i++) {
        if (analysisData->phase_A.clipping_timestamps[i] != 0) {
            fprintf(file, "   %lf ", analysisData->phase_A.clipping_timestamps[i]);
        }
    }

    fprintf(file, "\n   Tolerance compliance: %s\n", analysisData->phase_A.tolerance_compliance ? "True" : "False");

    fprintf(file, "\n\nPhase B Analysis:\n");
    fprintf(file, "   RMS: %lf\n", analysisData->phase_B.RMS);
    fprintf(file, "   Peak to Peak: %lf\n", analysisData->phase_B.PTP);
    fprintf(file, "   DC Offset: %lf\n", analysisData->phase_B.DC_offset);
    fprintf(file, "   Clipping detected at the following timestamps:\n");

    for (int i = 0; i < sizeof(analysisData->phase_B.clipping_timestamps) / sizeof(analysisData->phase_B.clipping_timestamps[0]); i++) {
        if (analysisData->phase_B.clipping_timestamps[i] != 0) {
            fprintf(file, "   %lf ", analysisData->phase_B.clipping_timestamps[i]);
        }
    }

    fprintf(file, "\n   Tolerance compliance: %s\n", analysisData->phase_B.tolerance_compliance ? "True" : "False");

    fprintf(file, "\n\nPhase C Analysis:\n");
    fprintf(file, "   RMS: %lf\n", analysisData->phase_C.RMS);
    fprintf(file, "   Peak to Peak: %lf\n", analysisData->phase_C.PTP);
    fprintf(file, "   DC Offset: %lf\n", analysisData->phase_C.DC_offset);
    fprintf(file, "   Clipping detected at the following timestamps:\n");

    for (int i = 0; i < sizeof(analysisData->phase_C.clipping_timestamps) / sizeof(analysisData->phase_C.clipping_timestamps[0]); i++) {
        if (analysisData->phase_C.clipping_timestamps[i] != 0) {
            fprintf(file, "   %lf ", analysisData->phase_C.clipping_timestamps[i]);
        }
    }

    fprintf(file, "\n   Tolerance compliance: %s\n", analysisData->phase_C.tolerance_compliance ? "True" : "False");

    fclose(file);
}