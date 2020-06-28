#pragma once
#include "datarefs.h"
#include <Windows.h>
#define NULL 0

// Se utilizan para encontrar la direccion del modulo
HANDLE pHandle;
DWORD pID;
HWND hGameWindow;

// ===============================
// Guardan los valores de los datarefs
// ===============================
extern float joystick_x = NULL;
extern float joystick_y = NULL;
extern float joystick_head = NULL;

extern float longitud = NULL;
extern float latitud = NULL;

extern float roll = NULL;
extern float yaw = NULL;
extern float pitch = NULL;

extern double x = NULL;
extern double y = NULL;
extern double z = NULL;

extern float flaps = NULL;
extern int ruedas = NULL;

extern float altitud_AGL = NULL;
extern float altitud_MSL = NULL;
extern float velocidad_del_aire = NULL;
extern float fuerza_g = NULL;
extern int tocando_terreno = NULL;
extern float retracion_de_ruedas = NULL;

extern float m_izquierdo = NULL;
extern float m_derecho = NULL;

// ===============================
// Guardan la direccion final de los datarefs.
// ===============================
extern DWORD_PTR yolk_roll_ratio_add = NULL;
extern DWORD_PTR yoke_pitch_ratio_add = NULL;
extern DWORD_PTR yoke_heading_ratio_add = NULL;

extern DWORD_PTR longitude_add = NULL;
extern DWORD_PTR latitude_add = NULL;

extern DWORD_PTR true_phi_add = NULL;
extern DWORD_PTR true_psi_add = NULL;
extern DWORD_PTR true_theta_add = NULL;

extern DWORD_PTR local_x_add = NULL;
extern DWORD_PTR local_y_add = NULL;
extern DWORD_PTR local_z_add = NULL;

extern DWORD_PTR flap_request_add = NULL;
extern DWORD_PTR gear_request_add = NULL;

extern DWORD_PTR y_agl_add = NULL;
extern DWORD_PTR elevation_add = NULL;
extern DWORD_PTR indicated_airspeed_add = NULL;
extern DWORD_PTR gforce_normal_add = NULL;
extern DWORD_PTR onground_any_add = NULL;
extern DWORD_PTR acf_gear_deploy_add = NULL;

extern DWORD_PTR right_engine_add = NULL;
extern DWORD_PTR left_engine_add = NULL;

// 1-azulMarino 2-verde 3-azulClaro 4-rojo 5-lila 6-amarillo 7-blanco 8-gris 9-AzulMenosClaro 
// 10-VerdeClaro 11-AzulCielo 12-Naranja 13-LilaOscuro 14-AmarilloClarito 15-Blanco



/*if (altitud_AGL < 1000) {

	SetConsoleTextAttribute(hConsole, 5);
	std::cout << "[INFO] ";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " Alcanzar los 3000ft: ";
	SetConsoleTextAttribute(hConsole, 6);
	std::cout << setprecision(2) << " [" << (altitud_AGL * 100) / 3000 << "%]         \r ";
}
else {

	SetConsoleTextAttribute(hConsole, 5);
	std::cout << "[INFO] ";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " Alcanzar los 35ft: ";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << setprecision(2) << " [Completado]          \r";
}*/