#pragma once
#include <Windows.h>
#include <iostream>    
#include <array> 
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <array> 
#include <iomanip> 
#include <math.h>
#include <float.h>
#include "var_globales.h"

// Roll
float Kp_roll;
float Kd_roll;
float Ki_roll;
float target_roll;
float error_roll;
float last_error_roll;
float integral_roll;
float derivate_roll;
float result_roll;

// Pitch
float Kp_pitch;
float Kd_pitch;
float Ki_pitch;
float target_pitch;
float error_pitch;
float last_error_pitch;
float integral_pitch;
float derivate_pitch;
float result_pitch;

// Yaw
float Kp_yaw;
float Kd_yaw;
float Ki_yaw;
float target_yaw;
float error_yaw;
float last_error_yaw;
float integral_yaw;
float derivate_yaw;
float result_yaw;
float target_yaw_opuesto;

float yaw_calc1;
float yaw_calc2;

// Velocidad
float Kp_engine;
float Kd_engine;
float Ki_engine;
float target_engine;
float error_engine;
float last_error_engine;
float integral_engine;
float derivate_engine;
float result_engine;


void obtener_error_yaw() {

	yaw_calc1 = fabsf((yaw - target_yaw));
	yaw_calc2 = fabsf(fabsf(((yaw - target_yaw))) - 360);

	if (yaw_calc1 < yaw_calc2) {
		error_yaw = yaw_calc1;
	}
	else if (yaw_calc1 > yaw_calc2) {
		error_yaw = yaw_calc2;
	}

	if (target_yaw > 180) {

		target_yaw_opuesto = fabsf(180 - target_yaw);

		if (yaw > target_yaw_opuesto && yaw < target_yaw) {

			error_yaw *= -1;
		}
	}
	else if (target_yaw <= 180) {

		target_yaw_opuesto = fabsf(180 + target_yaw);

		if (yaw < target_yaw_opuesto && yaw > target_yaw) {

			error_yaw *= -1;
		}
	}

	if (target_yaw > 0 && target_yaw > 180) {
		error_yaw = error_yaw * -1;

	}
	else {
		error_yaw = error_yaw * 1;
	}

}

float pid_roll() {
	error_roll = target_roll - roll;
	integral_roll = error_roll + integral_roll;
	derivate_roll = error_roll - last_error_roll;
	result_roll = (error_roll * Kp_roll) + (integral_roll * Ki_roll) + (derivate_roll * Kd_roll);
	last_error_roll = error_roll;

	if (result_roll > 1) {
		result_roll = 1;
	}
	if (result_roll < -1) {
		result_roll = -1;
	}

	return result_roll;

}

float pid_pitch() {

	error_pitch = target_pitch - pitch;
	integral_pitch = error_pitch + integral_pitch;
	derivate_pitch = error_pitch - last_error_pitch;
	result_pitch = (error_pitch * Kp_pitch) + (integral_pitch * Ki_pitch) + (derivate_pitch * Kd_pitch);
	last_error_pitch = error_pitch;

	return result_pitch;
}

float pid_velocidad() {

	error_engine = target_engine - velocidad_del_aire;
	integral_engine = error_engine + integral_engine;
	derivate_engine = error_engine - last_error_engine;
	result_engine = (error_engine * Kp_engine) + (integral_engine * Ki_engine) + (derivate_engine * Kd_engine);

	last_error_engine = error_engine;

	if (result_engine > 1) {
		result_engine = 1;
	}
	if (result_engine < -0) {
		result_engine = 0;
	}


	return result_engine;
}

float pid_yaw() {

	obtener_error_yaw();

	integral_yaw = error_yaw + integral_yaw;
	derivate_yaw = error_yaw - last_error_yaw;
	result_yaw = (error_yaw * Kp_yaw) + (integral_yaw * Ki_yaw) + (derivate_yaw * Kd_yaw);

	if (result_yaw > 0.2 || result_yaw < -0.2) {
		target_roll = error_yaw;

		if (target_roll > 55) {
			target_roll = 45;
		}
		if (target_roll < -45) {
			target_roll = -45;
		}

	}
	else {
		target_roll = 0;
	}

	if (result_yaw > 0.25) {
		result_yaw = 0.25;

	}if (result_yaw < -0.25) {
		result_yaw = -0.25;
	}

	last_error_yaw = error_yaw;

	return result_yaw;
}

