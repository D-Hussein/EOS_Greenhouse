/*
 * pwm.c
 *
 *  Created on: Nov 7, 2020
 *      Author: diyar
 */



#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "pwm.h"

// Exporting PWM
int export_pwm(char gpio[]) {
	int fd;
	char path[50] ="";
	strcat(path,"/sys/class/gpio/gpio");
	strcat(path,gpio);
	fd = fopen( path, "r");

	if (fd >= 0) {
		return 0;
	} else {
		FILE *f = fopen("/sys/class/gpio/export", "w");
		fclose(f);
		return 1;
	}
}

// Configuring_pwm
int configure_pwm(char pin[], char pwmchip[]) {
	char com[50] = "";
	strcat(com,"config-pin P9_");
	strcat(com,pin);
	strcat(com," pwm");
	int status = system(com);
	char path[100] = "";
	strcat(path,"/sys/class/pwm/pwmchip");
	strcat(path,pwmchip);
	strcat(path,"/export");
	FILE *exportfile = fopen(path, "w");
	if (exportfile == NULL) {
		printf("Export file not found!\n");
		return -1;
		exit(1);
	}
	fprintf(exportfile, "3");
	fclose(exportfile);

	char periodpath[100] ="";
	strcat(periodpath,"/sys/class/pwm/pwmchip");
	strcat(periodpath,pwmchip);
	strcat(periodpath,"/pwm-1:1/period");

	FILE *periodfile = fopen(periodpath, "w");
	if (periodfile == NULL) {
		printf("Period file not found!\n");
		return -1;
		exit(1);
	}
	fprintf(periodfile, "10000000");
	fclose(periodfile);
	return 1;

}

//Enabling PWM
int enable_pwm(long duty_cycle, char pwmchip[]) {
	char path[100] ="";
	strcat(path,"/sys/class/pwm/pwmchip");
	strcat(path,pwmchip);
	strcat(path,"/pwm-1:1/duty_cycle");
	FILE *dcf = fopen(path, "w");
	if (dcf == NULL) {
		printf("Cannot open duty_cycle file!\n");
		return -1;
		exit(1);
	}
	fprintf(dcf, "%d", duty_cycle);
	fclose(dcf);

	char enablepath[100] ="";
	strcat(enablepath,"/sys/class/pwm/pwmchip");
	strcat(enablepath,pwmchip);
	strcat(enablepath,"/pwm-1:1/enable");

	FILE *enable_file = fopen(enablepath, "w");
	if (enable_file == NULL) {
		printf("Enable file cannot be open!\n");
		return -1;
		exit(1);
	}
	fprintf(enable_file, "1");
	fclose(enable_file);
	return 1;
}

int pwm(char gpio[],char pin[], char pwmchip[],long duty_cycle) {
	printf("pwm program started...\n");
		export_pwm(gpio);
		printf("exporting done...\n");
		configure_pwm(pin,pwmchip);
		printf("configutration done...\n");
		enable_pwm(duty_cycle,pwmchip);
		printf("pwm program done.\n");
		return 1;
}
