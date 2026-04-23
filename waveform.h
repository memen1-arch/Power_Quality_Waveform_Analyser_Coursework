//
// Created by nilem on 23/04/2026.
//

#ifndef POWER_QUALITY_ANALYSER_COURSEWORK_WAVEFORM_H
#define POWER_QUALITY_ANALYSER_COURSEWORK_WAVEFORM_H

typedef struct {
    double timestamp,phase_A_voltage,phase_B_voltage,phase_C_voltage,line_current,frequency,power_factor,thd_percent;
}WaveformSample; //Struct that holds all 8 fields for a single row of the CSV

WaveformSample* WaveformArray(void);
int PQLR(void);
#endif //POWER_QUALITY_ANALYSER_COURSEWORK_WAVEFORM_H