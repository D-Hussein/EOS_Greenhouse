/*
 * pwm.c
 *
 *  Created on: Nov 7, 2020
 *      Author: diyar, daniela, jwan
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
	// accessing the gpio directory
	strcat(path,"/sys/class/gpio/gpio");
	strcat(path,gpio);
	fd = fopen( path, "r");

	if (fd >= 0) {
		return 0;
	} else { // setting the export file for write
		FILE *f = fopen("/sys/class/gpio/export", "w");
		fclose(f);
		return 1;
	}
}

// Configuring_pwm
int configure_pwm(char pin[], char pwmchip[]) {
	char com[50] = ""; // Building command string
	strcat(com,"config-pin P9_");
	strcat(com,pin);
	strcat(com," pwm");
	int status = system(com); //Writing to system
	char path[100] = ""; //Building the path to PWM chip
	strcat(path,"/sys/class/pwm/pwmchip");
	strcat(path,pwmchip);
	strcat(path,"/export");
	FILE *exportfile = fopen(path, "w"); //Writing to the export file
	if (exportfile == NULL) { //Exeption handling
		printf("Export file not found!\n");
		return -1;
		exit(1);
	}
	//exporting the pwmchip
	fprintf(exportfile, "1");
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
	}// setting up the period file
	fprintf(periodfile, "10000000");
	fclose(periodfile);
	return 1;

}

//Enabling PWM
int enable_pwm(long duty_cycle, char pwmchip[]) {
	char path[100] =""; //Building the duty cycle path string
	strcat(path,"/sys/class/pwm/pwmchip");
	strcat(path,pwmchip);
	strcat(path,"/pwm-1:1/duty_cycle");
	FILE *dcf = fopen(path, "w"); //writing to the duty cycle file
	if (dcf == NULL) { //exception handling
		printf("Cannot open duty_cycle file!\n");
		return -1;
		exit(1);
	}
	fprintf(dcf, "%d", duty_cycle); // passing the duty cycle value
	fclose(dcf);

	char enablepath[100] =""; //accessing the eneble file
	strcat(enablepath,"/sys/class/pwm/pwmchip");
	strcat(enablepath,pwmchip);
	strcat(enablepath,"/pwm-1:1/enable");

	FILE *enable_file = fopen(enablepath, "w");
	if (enable_file == NULL) {
		printf("Enable file cannot be open!\n");
		return -1;
		exit(1);
	}
	fprintf(enable_file, "1"); //enabling
	fclose(enable_file);
	return 1;
}

// method for using the driver
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
