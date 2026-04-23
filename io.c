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
        double voltage = atof(token);

        token = strtok(NULL,",");
        double current = atof(token);

        token = strtok(NULL,",");
        double power = atof(token);

        printf("time = %.1f,voltage = %.1f,current = %.1f , power = %.1f\n",
            time,voltage,current,power);
    }
    fclose(fp);
    return 0;
}
