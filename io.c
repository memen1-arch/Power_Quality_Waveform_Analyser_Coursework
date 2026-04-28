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
    WaveformSample *sample = WaveformArray();
    int n= 0;

    char line[256]; //Parsing Header
    fgets(line,sizeof(line),fp);
    while (fgets(line,sizeof(line),fp) != NULL && n < 8) { //read one line from the CSV until there is no more lines or n is > 8
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

            sample[n].timestamp = time;
            sample[n].phase_A_voltage = phase_A_voltage;
            sample[n].phase_B_voltage = phase_B_voltage;
            sample[n].phase_C_voltage = phase_C_voltage;
            sample[n].line_current = line_current;
            sample[n].frequency = frequency;
            sample[n].power_factor = power_factor;
            sample[n].thd_percent = thd_percent;

        printf("time = %.4f,PhaseAVolt = %.4f,PhaseBVolt = %.4f , PhaseCVolt = %.4f,Line current = %.4f,Frequency = %.4f,Power Factor = %.4f,thd percent = %.4f\n",
            time,phase_A_voltage,phase_B_voltage,phase_C_voltage,line_current,frequency,power_factor,thd_percent);

            n++; //adds 1 to the n counter
        }

    fclose(fp);
    return 0;
}
