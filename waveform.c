#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"

rmsResult compute_rms(WaveformSample *sample,int n) {
    double sum_sqA = 0.0;
    double sum_sqB = 0.0;
    double sum_sqC = 0.0;

    for (int i =0; i < n; i++) {
        sum_sqA += sample[i].phase_A_voltage * sample[i].phase_A_voltage;
        sum_sqB += sample[i].phase_B_voltage * sample[i].phase_B_voltage;
        sum_sqC += sample[i].phase_C_voltage * sample[i].phase_C_voltage;
    }
    rmsResult result;
    result.rmsA = sqrt(sum_sqA/n);
    result.rmsB = sqrt(sum_sqB/n);
    result.rmsC = sqrt(sum_sqC/n);
    return result;
}
void rmsPhaseQ(rmsResult result) {
    char choice;
    printf("Which RMS phase would you like('A','B','C')\n");
    scanf(" %c",&choice);
    switch (choice) {
        case 'A':
        printf("RMS of Phase A = %f\n",result.rmsA);
        break;
        case'B':
        printf("RMS of Phase B = %f\n",result.rmsB);
        break;
        case'C':
        printf("RMS of Phase C = %f\n",result.rmsC);
        break;
        default:
            printf("Invalid phase\n");
    }
}
    peakToPeak compute_peakToPeak(WaveformSample *sample,int n) {
        double PhaseAV =0.0;
        double vmaxPA = 0.0;
        double vminPA = 0.0;

        double PhaseBV =0.0;
        double vmaxPB = 0.0;
        double vminPB = 0.0;

        double PhaseCV =0.0;
        double vmaxPC = 0.0;
        double vminPC = 0.0;

    for (int i =0; i < n; i++) {
        PhaseAV = sample[i].phase_A_voltage;
        PhaseBV = sample[i].phase_B_voltage;
        PhaseCV = sample[i].phase_C_voltage;

        if (PhaseAV > vmaxPA) vmaxPA = PhaseAV;
        if (PhaseAV < vminPA) vminPA = PhaseAV;

        if (PhaseBV > vmaxPB) vmaxPB = PhaseBV;
        if (PhaseBV < vminPB) vminPB = PhaseBV;

        if (PhaseCV > vmaxPC) vmaxPC = PhaseCV;
        if (PhaseCV < vminPC) vminPC = PhaseCV;
    }
    peakToPeak result;
    result.peakToPeakA = vmaxPA - vminPA;
    result.peakToPeakB = vmaxPB - vminPB;
    result.peakToPeakC = vmaxPC - vminPC;

    return result;
}

void pToPPhaseQ(peakToPeak result) {
    char choice;
    printf("Which peak to peak phase would you like('A','B','C')\n");
    scanf(" %c",&choice);
    switch (choice) {
        case 'A':
            printf("Peak to peak of Phase A = %f\n",result.peakToPeakA);
            break;
        case'B':
            printf("Peak to peak of Phase B = %f\n",result.peakToPeakB);
            break;
        case'C':
            printf("Peak to peak of Phase C = %f\n",result.peakToPeakC);
            break;
        default:
            printf("Invalid phase\n");
    }
}
DCoffset compute_DCoffset(WaveformSample *sample,int n) {
    double DCoffsetA = 0.0;
    double voltageASum = 0.0;

    double DCoffsetB = 0.0;
    double voltageBSum = 0.0;

    double DCoffsetC = 0.0;
    double voltageCSum = 0.0;


    for (int i =0; i < n; i++) {
        voltageASum = voltageASum + sample[i].phase_A_voltage;

        voltageBSum = voltageBSum + sample[i].phase_B_voltage;

        voltageCSum = voltageCSum + sample[i].phase_C_voltage;
    }
    DCoffset result;
    result.DCoffsetA = (voltageASum / n);
    result.DCoffsetB = (voltageBSum / n);
    result.DCoffsetC = (voltageCSum / n);
        return result;


}
void DCoffsetQ(DCoffset result) {
    char choice;
    printf("Which RMS phase would you like('A','B','C')\n");
    scanf(" %c",&choice);
    switch (choice) {
        case 'A':
            printf("DC offset of Phase A = %f\n",result.DCoffsetA);
            break;
        case'B':
            printf("DC offset of Phase B = %f\n",result.DCoffsetB);
            break;
        case'C':
            printf("DC offset of Phase C = %f\n",result.DCoffsetC);
            break;
        default:
            printf("Invalid phase\n");
    }
}

double count_clipped(WaveformSample *sample, int n) {
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
void check_compliance(double rmsA,double rmsB ,double rmsC) {
    if (rmsA >= 207.0 && rmsA <= 253.0)
        printf("Phase A rms is compliant\n");
    else
        printf("Phase A rms is not compliant\n");
    if (rmsB >= 207.0 && rmsB <= 253.0)
        printf("Phase B rms is compliant\n");
    else
        printf("Phase B rms is not compliant\n");
    if (rmsC >= 207.0 && rmsC <= 253.0)
        printf("Phase C rms is compliant\n");
    else
        printf("Phase C rms is not compliant\n");
}