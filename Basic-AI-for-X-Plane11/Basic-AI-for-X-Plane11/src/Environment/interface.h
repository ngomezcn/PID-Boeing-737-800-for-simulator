#pragma once

namespace ENVIR
{
	namespace Inputs
	{
		double roll = NULL;         // Rotación en vista alzada
		double yaw = NULL;          // Rotación  en vista de planta
		double pitch = NULL;         // Rotación en vista de perfil.

		double altitude_AGL = NULL; // Altitud sobre el terreno.
		double altitude_MSL = NULL; // Altitud sobre el nivel del mar.

		double latitude = NULL;     // Cordenadas latitud 
		double longitude = NULL;    // Cordenadas longitud 

		double airspeed = NULL;     // Velocidad realativa al aire
		double true_speed = NULL;   // Velocidad real del avión

		double g_force = NULL;      // Fuerza G que esta experimentando 
		double flap_pos = NULL;     // Posición de los flaps

		bool landing_gear = NULL;   // Estado del tren de aterrizaje
		bool touch_terrain = NULL;  // Detecta si el avión esta tocando el terreno

		double R_engine = NULL;     // Acelerador del motor izquierdo
		double L_engine = NULL;     // Acelerador del motor izquierdo		
	}

	namespace Output
	{

	}
}