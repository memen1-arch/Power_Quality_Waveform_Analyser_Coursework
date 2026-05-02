//
// Created by nilem on 23/04/2026.
//

#ifndef POWER_QUALITY_ANALYSER_COURSEWORK_WAVEFORM_H
#define POWER_QUALITY_ANALYSER_COURSEWORK_WAVEFORM_H
typedef struct {
    double timestamp,phase_A_voltage,phase_B_voltage,phase_C_voltage,line_current,frequency,power_factor,thd_percent;
}WaveformSample; //Struct that holds all 8 fields for a single row of the CSV

int lineCountReader(void);
WaveformSample* WaveformArray(int count);
int PQLR(void);

typedef struct {
    double rmsA,rmsB,rmsC;
}rmsResult;
rmsResult compute_rms(WaveformSample *sample,int n);
typedef struct {
    double peakToPeakA,peakToPeakB,peakToPeakC;
}peakToPeak;
peakToPeak compute_peakToPeak(WaveformSample *sample,int n);
void pToPPhaseQ(peakToPeak result);

typedef struct {
    int clipA,clipB,clipC;
}clipCountP;
clipCountP count_clipped(WaveformSample *sample, int n);
void clipCountQ(clipCountP result);

void check_compliance(double rmsA,double rmsB,double rmsC);
void rmsPhaseQ(rmsResult result);

typedef struct {
    double DCoffsetA ,DCoffsetB ,DCoffsetC;
}DCoffset;
DCoffset compute_DCoffset(WaveformSample *sample,int n);
void DCoffsetQ(DCoffset result);

#endif //POWER_QUALITY_ANALYSER_COURSEWORK_WAVEFORM_H