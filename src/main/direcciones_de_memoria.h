#include "datarefs.h"
#include "var_globales.h"

#include <array> 
#include <tchar.h>
#include <string>
#include <sstream>
#include <iomanip> 
#include <math.h>
#include <float.h>
#include <tchar.h>
#include <windows.h>
#include <psapi.h>
#include <vector>
#include <iostream>

#define TH32CS_SNAPALL (TH32CS_SNAPHEAPLIST | TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD | TH32CS_SNAPMODULE)

void Get_pID_Handle() {

	hGameWindow = FindWindow(NULL, L"X-System");
	GetWindowThreadProcessId(hGameWindow, &pID);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

}
// Obtiene la direccion de X-System.

DWORD_PTR GetProcessBaseAddress(DWORD processID)
{
	DWORD_PTR   baseAddress = 0;
	HANDLE      processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	HMODULE* moduleArray;
	LPBYTE      moduleArrayBytes;
	DWORD       bytesRequired;

	if (processHandle)
	{
		if (EnumProcessModules(processHandle, NULL, 0, &bytesRequired))
		{
			if (bytesRequired)
			{
				moduleArrayBytes = (LPBYTE)LocalAlloc(LPTR, bytesRequired);

				if (moduleArrayBytes)
				{
					unsigned int moduleCount;

					moduleCount = bytesRequired / sizeof(HMODULE);
					moduleArray = (HMODULE*)moduleArrayBytes;

					if (EnumProcessModules(processHandle, moduleArray, bytesRequired, &bytesRequired))
					{
						baseAddress = (DWORD_PTR)moduleArray[0];
					}

					LocalFree(moduleArrayBytes);
				}
			}
		}

		CloseHandle(processHandle);
	}

	return baseAddress;
}

// Convierte un array de strings a un vector de enteros.
vector<int> ArrayStringToVectorInt(string array[], int tamaño) {

	vector<int> int_vec;

	int_vec.clear();

	for (int i = 0; i < tamaño; i++) {

		int_vec.push_back(stoi(array[i], 0, 16));
	}

	return int_vec;
}
DWORD_PTR BuscarDireccion(vector<int> vec, int tamaño) {
	DWORD_PTR address;
	DWORD_PTR addres_1;
	DWORD_PTR addres_2;
	DWORD_PTR clientBase = GetProcessBaseAddress(pID);

	if (tamaño == 1) {
		address = clientBase + vec[0];
		return address;
	}
	else if (tamaño > 1) {
		ReadProcessMemory(pHandle, (LPCVOID)(clientBase + vec[0]), &addres_1, sizeof(addres_1), NULL);

		for (int i = 1; i < vec.size() - 1; i++) {
			ReadProcessMemory(pHandle, (LPCVOID)(addres_1 + vec[i]), &addres_2, sizeof(addres_2), NULL);
			addres_1 = 0;
			addres_1 = addres_2;
			address = addres_2 + vec[i + 1];
		}
		return address;
	}

}

// Retorna la dirección dinamica final que almacena el valor.
DWORD_PTR DireccionFinal(string array[], int tamaño) {
	DWORD_PTR FinalAddress;

	FinalAddress = BuscarDireccion(ArrayStringToVectorInt(array, tamaño), tamaño);
	return FinalAddress;
}

// Retornan el valor que guarda la dirección dinamica.
float GetFloatValue(DWORD_PTR final_addres) {
	float f;
	DWORD_PTR currentValue;
	ReadProcessMemory(pHandle, (LPCVOID)(final_addres), &currentValue, 4, NULL);

	f = *((float*)&currentValue);
	return f;
}
double GetDoubleValue(DWORD_PTR final_addres) {
	double d;
	DWORD_PTR currentValue;

	ReadProcessMemory(pHandle, (LPCVOID)(final_addres), &currentValue, 8, NULL);
	d = *((double*)&currentValue);
	return d;
}
int GetIntValue(DWORD_PTR final_addres) {
	int i;
	DWORD_PTR currentValue;

	ReadProcessMemory(pHandle, (LPCVOID)(final_addres), &currentValue, 4, NULL);
	i = *((int*)&currentValue);
	return i;
}

// Escriben un valor en la dirección dinamica introducida.
void EscribirInt(DWORD_PTR direccion, int valor) {

	WriteProcessMemory(pHandle, (LPVOID)(direccion), &valor, sizeof(valor), 0);

}
void EscribirFloat(DWORD_PTR direccion, float valor) {

	WriteProcessMemory(pHandle, (LPVOID)(direccion), &valor, sizeof(valor), 0);

}
void EscribirDouble(DWORD_PTR direccion, double valor) {

	WriteProcessMemory(pHandle, (LPVOID)(direccion), &valor, sizeof(valor), 0);

}

// Si se añaden nuevos datarefs hay que añadir las variables necesarias aquí.
void ObtenerDireccionesPrograma() {

	std::string indicated_airspeed[] = { "15E9B98" };

	std::string true_phi[] = { "026622E8", "4B0", "45C" };
	std::string true_psi[] = { "026622E8", "2D0", "494" };
	std::string true_theta[] = { "026622E8", "478", "478" };

	string left_engine[] = { "2DBA518" , "4CC0" , "48" };
	string right_engine[] = { "2DBA518" , "4CC0" , "2C4" };

	// Guardar direccion finales
	yolk_roll_ratio_add = DireccionFinal(yolk_roll_ratio, 5);
	yoke_pitch_ratio_add = DireccionFinal(yoke_pitch_ratio, 3);
	yoke_heading_ratio_add = DireccionFinal(yoke_heading_ratio, 3);

	longitude_add = DireccionFinal(longitude, 1);
	latitude_add = DireccionFinal(latitude, 1);

	true_phi_add = DireccionFinal(true_phi, 3);
	true_psi_add = DireccionFinal(true_psi, 3);
	true_theta_add = DireccionFinal(true_theta, 3);

	local_x_add = DireccionFinal(local_x, 3);
	local_y_add = DireccionFinal(local_y, 3);
	local_z_add = DireccionFinal(local_z, 3);

	flap_request_add = DireccionFinal(flap_request, 8);
	gear_request_add = DireccionFinal(gear_request, 3);

	y_agl_add = DireccionFinal(y_agl, 3);
	elevation_add = DireccionFinal(elevation, 3);
	indicated_airspeed_add = DireccionFinal(indicated_airspeed, 1);
	gforce_normal_add = DireccionFinal(gforce_normal, 3);
	onground_any_add = DireccionFinal(onground_any, 1);
	acf_gear_deploy_add = DireccionFinal(acf_gear_deploy, 1);


	left_engine_add = DireccionFinal(left_engine, 3);
	right_engine_add = DireccionFinal(right_engine, 3);
}

void ActualizarValores() {
	joystick_x = GetFloatValue(yolk_roll_ratio_add);
	joystick_y = GetFloatValue(yoke_pitch_ratio_add);
	joystick_head = GetFloatValue(yoke_heading_ratio_add);

	longitud = GetFloatValue(longitude_add);
	latitud = GetFloatValue(latitude_add);

	roll = GetFloatValue(true_phi_add);
	yaw = GetFloatValue(true_psi_add);
	pitch = GetFloatValue(true_theta_add);

	x = GetDoubleValue(local_x_add);
	y = GetDoubleValue(local_y_add);
	z = GetDoubleValue(local_z_add);

	flaps = GetFloatValue(flap_request_add);
	ruedas = GetIntValue(gear_request_add);

	altitud_AGL = GetFloatValue(y_agl_add);
	altitud_MSL = GetDoubleValue(elevation_add);
	velocidad_del_aire = GetFloatValue(indicated_airspeed_add);
	fuerza_g = GetFloatValue(gforce_normal_add);
	tocando_terreno = GetIntValue(onground_any_add);
	retracion_de_ruedas = GetFloatValue(acf_gear_deploy_add);

	m_derecho = GetFloatValue(right_engine_add);
	m_izquierdo = GetFloatValue(left_engine_add);

	Sleep(0);
}






