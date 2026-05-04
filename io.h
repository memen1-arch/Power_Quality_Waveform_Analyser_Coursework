//
// Created by nilem on 27/04/2026.
//
#ifndef POWERQUALITYWAVEFORMANALYSER_IO_H
#define POWERQUALITYWAVEFORMANALYSER_IO_H
int lineCountReader(void);

WaveformSample* WaveformArray(int count);

int PQLR(void);
int print_results(rmsResult rms, peakToPeak pToP, DCoffset offset, clipCountP clip);
#endif //POWERQUALITYWAVEFORMANALYSER_IO_H