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
        printf("RMS of Phase A = %f\n",rmsA);
        break;
        case'B':
        printf("RMS of Phase B = %f\n",rmsB);
        break;
        case'C':
        printf("RMS of Phase C = %f\n",rmsC);
        break;
    }
    return 0;
}

    double compute_peakToPeakA(WaveformSample *sample,int n) {
        double PhaseAV =0.0;
        double vmaxPA = 0.0;
        double vminPA = 0.0;

    for (int i =0; i < n; i++) {
        PhaseAV = sample[i].phase_A_voltage;

        if (PhaseAV > vmaxPA) vmaxPA = PhaseAV;
        if (PhaseAV < vminPA) vminPA = PhaseAV;
    }
    return vmaxPA-vminPA;
}
double compute_peakToPeakB(WaveformSample *sample,int n) {
    double PhaseBV =0.0;
    double vmaxPB = 0.0;
    double vminPB = 0.0;

    for (int i =0; i < n; i++) {
        PhaseBV = sample[i].phase_B_voltage;

        if (PhaseBV > vmaxPB) vmaxPB = PhaseBV;
        if (PhaseBV < vminPB) vminPB = PhaseBV;
    }
    return vmaxPB-vminPB;
}
double compute_peakToPeakC(WaveformSample *sample,int n) {
    double PhaseCV =0.0;
    double vmaxPC = 0.0;
    double vminPC = 0.0;

    for (int i =0; i < n; i++) {
        PhaseCV = sample[i].phase_C_voltage;

        if (PhaseCV > vmaxPC) vmaxPC = PhaseCV;
        if (PhaseCV < vminPC) vminPC = PhaseCV;
    }
    return vmaxPC-vminPC;
}
double compute_peakToPeak(WaveformSample *sample,int n,int phase) {
    char choice;
    printf("Which Peak to peak voltage phase would you like('A','B','C')\n");
    scanf(" %c",&choice);
    switch (choice) {
        case 'A': {
            double tempPtoP = compute_peakToPeakA(sample,n);
            printf("Peak to peak of phase A=%f\n",tempPtoP);
            return tempPtoP;
        }
        case 'B': {
            double tempPtoP = compute_peakToPeakB(sample,n);
            printf("Peak to peak of phase B=%f\n",tempPtoP);
            return tempPtoP;
        }
        case 'C': {
            double tempPtoP = compute_peakToPeakC(sample,n);
            printf("Peak to peak of phase C=%f\n",tempPtoP);
            return tempPtoP;
        }
            default:
                printf("Invalid phase\n");
            return 0.0;
    }
}
double compute_DCoffsetA(WaveformSample *sample,int n) {
    double DCoffsetA = 0.0;
    double voltageASum = 0.0;
    for (int i =0; i < n; i++) {
        voltageASum = voltageASum + sample[i].phase_A_voltage;
        DCoffsetA = (voltageASum / n);
    }
    return DCoffsetA;
}
double compute_DCoffsetB(WaveformSample *sample,int n) {
    double DCoffsetB = 0.0;
    double voltageBSum = 0.0;
    for (int i =0; i < n; i++) {
        voltageBSum = voltageBSum + sample[i].phase_B_voltage;
        DCoffsetB = (voltageBSum / n);
    }
    return DCoffsetB;
}
double compute_DCoffsetC(WaveformSample *sample,int n) {
    double DCoffsetC = 0.0;
    double voltageCSum = 0.0;
    for (int i =0; i < n; i++) {
        voltageCSum = voltageCSum + sample[i].phase_C_voltage;
        DCoffsetC = (voltageCSum / n);
    }
    return DCoffsetC;
}
double compute_DCoffset(WaveformSample *sample,int n,int phase) {
    char choice;
    printf("Which DC offset voltage phase would you like('A','B','C')\n");
    scanf(" %c",&choice);
    switch (choice) {
        case 'A': {
            double tempOS = compute_DCoffsetA(sample,n);
            printf("DC offset of phase A=%f\n",tempOS);
            return tempOS;
        }
        case 'B': {
            double tempOS = compute_DCoffsetB(sample,n);
            printf("DC offset of phase B=%f\n",tempOS);
            return tempOS;
        }
        case 'C': {
            double tempOS = compute_DCoffsetC(sample,n);
            printf("DC offset of phase C=%f\n",tempOS);
            return tempOS;
        }
        default:
            printf("Invalid phase\n");
            return 0.0;
    }
}

double detectClipping(WaveformSample *sample, int n) {
    int clipA = 0;
    int clipB = 0;
    int clipC = 0;

    for (int i =0; i < n; i++) {
        if (sample[i].phase_A_voltage >= 324.9 || sample[i].phase_A_voltage <= -324.9) {
            clipA++;
        }
        if (sample[i].phase_B_voltage >= 324.9 || sample[i].phase_B_voltage <= -324.9) {
            clipB++;
        }
        if (sample[i].phase_C_voltage >= 324.9 || sample[i].phase_C_voltage <= -324.9) {
            clipC++;
        }
    }
        char choice;
        printf("Which voltage phase would you like to see the clipping count for('A','B','C')\n");
        scanf(" %c",&choice);
        switch (choice) {
            case 'A': {
                printf("Clipping count for phase A = %d\n",clipA);
                return clipA;
            }
            case 'B': {
                printf("Clipping count for phase B = %d\n",clipB);
                return clipB;
            }
            case 'C': {
                printf("Clipping count for phase C = %d\n",clipC);
                return clipC;
            }
            default:
                printf("Invalid phase\n");
                return 0.0;
        }
    }
