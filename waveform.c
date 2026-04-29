#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"

double compute_rms(WaveformSample *sample,int n) {
    double sum_sq =0.0;
    for (int i =0; i < n; i++) {
        sum_sq += sample[i].phase_A_voltage * sample[i].phase_A_voltage;
    }
    double rms = sqrt(sum_sq/n);
    printf("RMS = %f\n",rms);
    return rms;
}
