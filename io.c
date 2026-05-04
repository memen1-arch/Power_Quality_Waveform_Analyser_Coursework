//For All file I/O: Loading the CSV into your struct array,writing the result file.
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "waveform.h"
int lineCountReader(void) { //read each line add a count when line has been read until CSV has been fully read
    FILE *fp = fopen("power_quality_log.csv","r"); //Reading our CSV file
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    char line[256];
    int count = 0;

    if (fgets(line,sizeof(line),fp) == NULL) {
        fclose(fp);
        return 0;
    }
    while (fgets(line,sizeof(line),fp) != NULL) {
        //printf("%s",line);
        count++;
    }
    fclose(fp);
    return count;
}
WaveformSample* WaveformArray(int count){
     WaveformSample*arr = malloc(count*sizeof(WaveformSample)); //allocate enough memory based on count of lines from line reader
    if (arr == NULL) {
        return NULL;
    }
    return arr;
}


int PQLR(void) {
    int count = lineCountReader();
    if (count == 0) {
        printf("Error reading CSV\n");
        return 1;
    }
    FILE *fp = fopen("power_quality_log.csv","r"); //Reading our CSV file
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    WaveformSample *sample = WaveformArray(count);
    int n= 0;

    char line[256]; //Parsing Header
    fgets(line,sizeof(line),fp);
    while (fgets(line,sizeof(line),fp) != NULL && n < count) { //read one line from the CSV until there is no more lines or n is less than count
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


            n++; //adds 1 to the n counter
        }

    rmsResult rms =compute_rms(sample,n);
    rmsPhaseQ(rms);
    check_compliance(rms.rmsA, rms.rmsB, rms.rmsC);

    peakToPeak pToP =compute_peakToPeak(sample,n);
    pToPPhaseQ(pToP);

    DCoffset offset =compute_DCoffset(sample,n);
    DCoffsetQ(offset);

    clipCountP clip =count_clipped(sample,n);
    clipCountQ(clip);

 print_results(rms,pToP,offset,clip);
    free(sample);
    fclose(fp);
    return 0;
}
int print_results(rmsResult rms, peakToPeak pToP, DCoffset offset, clipCountP clip) {
    FILE *fp = fopen("results.txt","w");
    if (fp == NULL) {
        printf("Error opening file\n");
    }
    fprintf(fp,"Power Quality Analysis Results\n");
    fprintf(fp,"RMS Results\n");
    fprintf(fp,"RMS Phase A:%.4f\n",rms.rmsA);
    fprintf(fp,"RMS Phase B:%.4f\n",rms.rmsB);
    fprintf(fp,"RMS Phase C:%.4f\n",rms.rmsC);

    fprintf(fp,"Peak to peak\n");
    fprintf(fp,"Peak to peak of Phase A:%.4f\n",pToP.peakToPeakA);
    fprintf(fp,"Peak to peak of Phase B:%.4f\n",pToP.peakToPeakB);
    fprintf(fp,"Peak to peak of Phase C:%.4f\n",pToP.peakToPeakC);

    fprintf(fp,"DC offset\n");
    fprintf(fp,"DC offset of Phase A:%.4f\n",offset.DCoffsetA);
    fprintf(fp,"DC offset of Phase B:%.4f\n",offset.DCoffsetB);
    fprintf(fp,"DC offset of Phase C:%.4f\n",offset.DCoffsetC);

    fprintf(fp,"Clipping Count\n");
    fprintf(fp,"Clip count of Phase A:%d\n",clip.clipA);
    fprintf(fp,"Clip count of Phase B:%d\n",clip.clipB);
    fprintf(fp,"Clip count of Phase C:%d\n",clip.clipC);

    fclose(fp);
}
