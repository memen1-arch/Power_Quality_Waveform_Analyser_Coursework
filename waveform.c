#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"

double compute_rms(WaveformSample *sample,int n) {
    double sum_sqA =0.0;
    double sum_sqB = 0.0;
    double sum_sqC = 0.0;

    for (int i =0; i < n; i++) {
        sum_sqA += sample[i].phase_A_voltage * sample[i].phase_A_voltage;
        sum_sqB += sample[i].phase_B_voltage * sample[i].phase_B_voltage;
        sum_sqC += sample[i].phase_C_voltage * sample[i].phase_C_voltage;
    }
    double rmsA = sqrt(sum_sqA/n);
    double rmsB = sqrt(sum_sqB/n);
    double rmsC = sqrt(sum_sqC/n);
    char choice;
    printf("Which RMS phase would you like('A','B','C')\n");
    scanf("%c",&choice);
    switch (choice) {
        case 'A':
        printf("RMS of Phase A = %f",rmsA);
        break;
        case'B':
        printf("RMS of Phase B = %f",rmsB);
        break;
        case'C':
        printf("RMS of Phase C = %f",rmsC);
        break;
    }
    return 0;
}
