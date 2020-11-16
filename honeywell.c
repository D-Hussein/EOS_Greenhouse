/*
 * honeywell.c
 *
 *  Created on: Nov 12, 2020
 *      Author: diyar
 */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

//int fd; /* File descriptor*/
//const char *fileName = "/dev/i2c-2"; /* Name of the port we will be using. On Raspberry 2 this is i2c-1, on an older Raspberry Pi 1 this might be i2c-0.*/

int address = 0x27; // Address of Honeywell sensor
unsigned char buf[4]; /* Buffer for data read/written on the i2c bus */

int file; // file descriptor
char filename[40];

void sensors_init(void) {

	sprintf(filename, "/dev/i2c-2"); //Name of the i2c port
	if ((file = open(filename, O_RDWR)) < 0) {
		printf("Failed to open the bus.");
		// ERROR HANDLING
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, address) < 0) {
		printf("Failed to acquire bus access and/or talk to slave.\n");
		// ERROR HANDLING
		exit(1);
	}

}
void wright_hw() { //write to sensor
	const char *buffer;
	char buf[10] = { 0 };
	//unsigned char reg = 0x10; // Device register to access
	//buf[0] = reg;
	buf[0] = 0b11110000;

	if (write(file, buf, 1) != 1) {
		// ERROR HANDLING: i2c transaction failed
		printf("Failed to write to the i2c bus.\n");
		buffer = strerror(errno);
		printf(buffer);
		printf("\n\n");
	}
}

int sensor_read(char th[]) {

	sensors_init();
	/* Open port (r/w) */
	if ((file = open(filename, O_RDWR)) < 0) {
		printf("Failed to open i2c port\n");
		exit(1);
	}

	/* Set port options and slave devie address */
	if (ioctl(file, I2C_SLAVE, address) < 0) {
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}

	wright_hw();

	//* Wait for 100ms for measurement to complete.
	usleep(100000);

	/* read back data */
	if (read(file, buf, 4) < 0) {
		printf("Unable to read from slave\n");
		exit(1);
	} else {
		/* Humidity is located in first two bytes */
		int reading_hum = (buf[0] << 8) + buf[1];
		double humidity = reading_hum / 16382.0 * 100.0;


		/* Temperature is located in next two bytes, padded by two trailing bits */
		int reading_temp = (buf[2] << 6) + (buf[3] >> 2);
		double temperature = reading_temp / 16382.0 * 165.0 - 40;
		if(strcmp(th,"temp")==0){
			printf("%.1f C\n", temperature);

		}else if(strcmp(th,"hum")==0){
			printf("%.1f %\n", humidity);
		}


	}

	return 0;
}
