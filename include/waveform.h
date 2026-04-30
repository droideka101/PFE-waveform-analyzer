//
// Created by ben on 02/04/2026.
//

#ifndef PROJECT_FILE_WAVEFORM_H
#define PROJECT_FILE_WAVEFORM_H

#include "io.h"

#define volLimit 324.9
#define targetRMS 230

WaveformAnalysisData* AnalysePQ(WaveformSample *waveData);

#endif //PROJECT_FILE_WAVEFORM_H