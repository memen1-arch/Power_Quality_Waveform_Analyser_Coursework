//For All file I/O: Loading the CSV into your struct array,writing the result file.
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "waveform.h"
WaveformSample* WaveformArray(void){
     WaveformSample*arr = malloc(8*sizeof(WaveformSample));
    if (arr == NULL) {
        return NULL;
    }
    return arr;
}

int PQLR(void) {
    FILE *fp = fopen("power_quality_log.csv","r"); //Reading our CSV file
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    char line[256]; //Parsing Header
    fgets(line,sizeof(line),fp);
    while (fgets(line,sizeof(line),fp) != NULL) {
        char *token;
        token = strtok(line,",");
        double time = atof(token);

        token = strtok(NULL,",");
        double phase_A_voltage = atof(token);

        token = strtok(NULL,",");
        double phase_B_voltage = atof(token);

        token = strtok(NULL,",");
        double phase_C_voltage = atof(token);

        token = strtok(NULL,",");
        double line_current = atof(token);

        token = strtok(NULL,",");
        double frequency = atof(token);

        token = strtok(NULL,",");
        double power_factor = atof(token);

        token = strtok(NULL,",");
        double thd_percent = atof(token);

        printf("time = %.1f,PhaseAVolt = %.1f,PhaseBVolt = %.1f , PhaseCVolt = %.1f,Line current = %.1f,Frequency = %.1f,Power Factor = %.1f,thd percent = %.1f\n",
            time,phase_A_voltage,phase_B_voltage,phase_C_voltage,line_current,frequency,power_factor,thd_percent);
    }
    fclose(fp);
    return 0;
}
