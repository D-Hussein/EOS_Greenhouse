/*
 * pwm.h
 *
 *  Created on: Nov 7, 2020
 *      Author: diyar
 */



#ifndef PWM_HEADER

#define PWM_HEADER


int pwm(char gpio[],char pin[], char pwmchip[],long duty_cycle);
int export_pwm(char gpio[]);
int configure_pwm(char pin[],char pwmchip[]);
int enable_pwm(long duty_cycle,char pwmchip[]);

#endif

