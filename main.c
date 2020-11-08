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


void heater(){
	//ToDo
	printf("This function is not completed yet...\n");
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

	if(cmnd = "light"){
		printf("setting light intensity...\n");
		char *p;
			long conv = strtol(argv[2], &p, 10);

			printf("starting PWM_LIGHT\n");

			pwm_light("3","21","1",conv);

			printf("PWM_Light excuted\n");
			return 1;
	}else if(cmnd = "servo"){

		return 1;

	}else if(cmnd = "heater"){

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
