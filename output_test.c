/*
* Name : output_test.c
* Copyright : GPL
* Description : This is a test application which is used for testing
* GPIO output functionality of the raspi-gpio Linux device driver
* implemented for Raspberry Pi revision B platform. The test
* application first sets all the GPIO pins on the Raspberry Pi to
* output, then it sets all the GPIO pins to "high"/"low" logic
* level based on the options passed to the program from the command
* line
* Usage example:
* ./output_test 1 // Set all GPIO pins to output, high state
* ./output_test 0 // Set all GPIO pins to output, low state
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#define NUM_GPIO_PINS 26
#define MAX_GPIO_NUMBER 28
#define BUF_SIZE 4
#define PATH_SIZE 20

int main(int argc, char **argv)
{
	int i = 0, index = 0, value;
	int fd[NUM_GPIO_PINS];
	char path[PATH_SIZE];
	char buf[BUF_SIZE];
	if (argc != 2) {
		printf("Option low/high must be used\n");
		exit(EXIT_FAILURE);
	}
	// Open all GPIO pins
	for (i = 0; i < MAX_GPIO_NUMBER; i++) {
		if (i != 0 && i != 1) {
			snprintf(path, sizeof(path), "/dev/raspiGpio%d", i);
			fd[index] = open(path, O_WRONLY);
			if (fd[index] < 0) {
				perror("Error opening GPIO pin");
				exit(EXIT_FAILURE);
			}
			index++;
		}
	}
	// Set direction of GPIO pins to output
	printf("Set GPIO pins to output, logic level :%s\n", argv[1]);
	strncpy(buf, "out", 3);
	buf[3] = '\0';
	for (index = 0; index < NUM_GPIO_PINS; index++) {
		if (write(fd[index], buf, sizeof(buf)) < 0) {
			perror("write, set pin output");
			exit(EXIT_FAILURE);
		}
	}
	// Set logic state of GPIO pins low/high
	value = atoi(argv[1]);
	if (value == 1) {
		strncpy(buf, "1", 1);
		buf[1] = '\0';
	}
	else if (value == 0) {
		strncpy(buf, "0", 1);
		buf[1] = '\0';
	} 
	else {
		printf("Invalid logic value\n");
		exit(EXIT_FAILURE);
	}
	for (index = 0; index < NUM_GPIO_PINS; index++) {
		if (write(fd[index], buf, sizeof(buf)) < 0) {
			perror("write, set GPIO state of GPIO pins");
			exit(EXIT_FAILURE);
		}
	}
	return EXIT_SUCCESS;
}
