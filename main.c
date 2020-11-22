/*
 * main.c
 *
 *  Created on: Nov 7, 2020
 *      Author: diyar, daniela, jwan
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "pwm.h"
#include "honey.h"

char heaterpin[] = "49"; //pin 9_23

void heater(char turn[]) {
	export_pwm(heaterpin); //using an already existing method for exporting the heater pin

	//Setting direction to output

	char com[50] = "";
	strcat(com, "/sys/class/gpio/gpio"); // Building the command string
	strcat(com, heaterpin);
	strcat(com, "/direction");
	//int status = system(com);
	FILE *directionFile = fopen(com, "w");

	if (directionFile == NULL) { //Exception handler
		printf("Direction file not found!\n");
		return;
		exit(1);
	}

	fprintf(directionFile, "out");
	fprintf(directionFile, "Out"); //Setting the pin to output
	//Access the value file
	char path[100] = "";
	strcat(path, "/sys/class/gpio/gpio");
	strcat(path, heaterpin);
	strcat(path, "/value");
	FILE *valueFile = fopen(path, "w");
	if (valueFile == NULL) {
		printf("Value file not found!\n");
		return;
		exit(1);
	}

	if (strcmp(turn, "on") == 0) {
		printf("Turning heater on!\n");

		fprintf(valueFile, "1"); //Turning the heater on
		fclose(valueFile);

	} else if (strcmp(turn, "off") == 0) {
		printf("Turning heater off!\n");

		fprintf(valueFile, "0"); //Turning the heater off
		fclose(valueFile);
	} else {
		printf("please type on or off as the second argument for the heater\n");
		return;
		exit(1);
	}

}

void measureLight() { //Light sensor
	system("cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw");
}

void pwm_light(char gpio[], char pin[], char pwmchip[], long intensity) {

	if (intensity >= 0 && intensity <= 100) { // Making sure the intensity is in percentage
		printf("processing...\n");
		long duty_cycle = intensity * 100000; // Duty cycle Long variable
		printf("sending to pwm...\n");
		pwm(gpio, pin, pwmchip, duty_cycle);	// Using the PWM driver
		printf("Brightness is %d\n ", intensity);
	} else {	// Exception handler
		printf("Please provide correct intensity percentage value \n");
	}

}

int main(int argc, char *argv[]) {
	if (argc != 3) {	// Number of arguments must be 3 in all cases
		printf("Two parameters are required to be passed. \n");
		return 0;
	}
	char *cmnd = argv[1]; // Command from user

	if (strcmp(cmnd, "light") == 0) { // PWM_Light function
		printf("setting light intensity...\n");
		char *p;
		long conv = strtol(argv[2], &p, 10); // Converting the second argument to Long

		printf("starting PWM_LIGHT\n");

		pwm_light("3", "21", "1", conv); // Passing the GPIO,Pin_Number,pinchip,and intensity value

		printf("PWM_Light excuted\n");
		return 0;
	} else if (strcmp(cmnd, "heater") == 0) { // Heater function

		printf("Turning heater\n");
		heater(argv[2]);
		return 0;
	} else if (strcmp(cmnd, "lightMeasure") == 0) { //Light sensor

		measureLight(argv[2]); // Second argument is just a random string here which does not affect anything
		return 0;
	} else if (strcmp(cmnd, "t_h") == 0) { // Honeywell sensor

		sensor_read(argv[2]); // secon argument specifies temperature or humidity
		return 0;
	} else {
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
