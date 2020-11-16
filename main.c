/*
 * main.c
 *
 *  Created on: Nov 7, 2020
 *      Author: diyar
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "pwm.h"
//#include "I2CDevice.h"
#include "honey.h"


char heaterpin[] = "49"; //pin 9_23

void heater(char turn[]){
	export_pwm(heaterpin);

	//Setting direction to output


	char com[50] = "";
			strcat(com,"/sys/class/gpio/gpio");
			strcat(com,heaterpin);
			strcat(com,"/direction");
			//int status = system(com);
			FILE *directionFile = fopen(com , "w");

			if (directionFile == NULL) {
				printf("Direction file not found!\n");
				return;
				exit(1);
			}

				fprintf(directionFile, "1");

	//Access the value file
	char path[100] = "";
			strcat(path,"/sys/class/gpio/gpio");
			strcat(path,heaterpin);
			strcat(path,"/value");
	FILE *valueFile = fopen(path, "w");
			if (valueFile == NULL) {
				printf("Value file not found!\n");
				return;
				exit(1);
			}

			if(strcmp(turn,"on")==0){
				printf("Turning heater on!\n");

				fprintf(valueFile, "1");
				fclose(valueFile);
			}else if(strcmp(turn,"off")==0){
				printf("Turning heater off!\n");

				fprintf(valueFile, "0");
				fclose(valueFile);
			}else{
				printf("please type on or off as the second argument for the heater\n");
				return;
				exit(1);
			}

}
void pwm_servo(char gpio[], char pin[],char pwmchip[],long percentage){
	//ToDo
	printf("This function is not completed yet...\n");
}


void pwm_light(char gpio[], char pin[],char pwmchip[],long intensity) {

	if (intensity >= 0 && intensity <= 100) {
		printf("processing...\n");
		long duty_cycle = intensity * 100000;
		printf("sending to pwm...\n");
		pwm(gpio,pin,pwmchip,duty_cycle);
		printf("Brightness is %d\n ", intensity);
	} else {
		printf("Please provide correct intensity percentage value \n");
	}

}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf(
				"Two parameters are required to be passed. \n");
		return -1;
	}



	char *cmnd = argv[1];

	if(strcmp(cmnd,"light")==0){
		printf("setting light intensity...\n");
		char *p;
			long conv = strtol(argv[2], &p, 10);

			printf("starting PWM_LIGHT\n");

			pwm_light("3","21","1",conv);

			printf("PWM_Light excuted\n");
			return 1;
	}else if(strcmp(cmnd,"servo")==0){

		return 1;

	}else if(strcmp(cmnd,"heater")==0){

		printf("Turning heater\n");
		heater(argv[2]);
		return 1;
	}else if(strcmp(cmnd,"t_h")==0){

		// ToDo: still need to pass 3ed parameter as a place holder
		sensor_read(argv[2]);
		return 1;
	}
	else{
		printf("Your command is not recognized\n");
		printf(argv[0]);
		printf("\n");
		printf(argv[1]);
		printf("\n");
		printf(argv[2]);
		printf("\n");
		printf(cmnd);
		printf("\n");

		return 0;
	}

}
