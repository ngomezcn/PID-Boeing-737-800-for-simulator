#include "VueloautnomoparalaaeronaveF4PhantomII.h"
#include <QtWidgets/QApplication>
#include <sstream>
#include <iostream>
#include "xplane_direcciones_de_memoria.h"
#include "pid.h"
#include "datarefs.h"

#include<QDebug>
#include <QtCore>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VueloautnomoparalaaeronaveF4PhantomII w;
	//w.show();

	Get_pID_Handle();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Colores de la consola
	ObtenerDireccionesPrograma();
	//ActualizarValores(); // Obtiene los valores por primera vez para calibrar las variables
	//CalibrarAeronave();
	//SetConsoleTextAttribute(hConsole, 5); 
	qInfo() << "C++ Style Info Message";

	float engine_cr;


	Kp_roll = 0.03;
	Kd_roll = 0.2;
	Ki_roll = 0.0000001;
	target_roll = 0;

	Kp_pitch = 0.05;
	Kd_pitch = 0.2;
	Ki_pitch = 0.0000001;
	target_pitch = 0;

	Kp_yaw = 0.07;
	Kd_yaw = 2.7;
	Ki_yaw = 0;
	target_yaw = 290;

	float lat_target = 28.456177;
	float lon_target = -16.291930;
	float gps_erro = 0.005;

	target_engine = 400;
	float flt = 400;
	Kp_engine = 0.1;
	Kd_engine = 2.8;
	Ki_engine = 0.00000000001;

	float yaw_calc5;
	float yaw_calc6;
	float target_yaw_opuesto_a;
	unsigned t0, t1;


	while (true) {

		ActualizarValores();

		target_engine = target_engine + (pitch);
		engine_cr = pid_velocidad();
		t0 = clock();
		EscribirFloat(right_engine_add, engine_cr);
		EscribirFloat(left_engine_add, engine_cr);

		EscribirFloat(yoke_pitch_ratio_add, pid_pitch());
		EscribirFloat(yolk_roll_ratio_add, pid_roll());
		t1 = clock();
		//EscribirFloat(yoke_heading_ratio_add, pid_yaw());
		target_engine = flt;

		if (latitud  < lat_target + gps_erro && latitud > lat_target - gps_erro && longitud  < lon_target + gps_erro && longitud > lon_target - gps_erro) {


		}
		else {


		}

		QCoreApplication::processEvents();


		cout << "Target_airspeed: " << target_engine << "  True_airspeed: " << velocidad_del_aire << "  Limit G force: " << "10.000" << "  G Force:  " << fuerza_g << "  Tiempo eje: " << (double(t1 - t0) / CLOCKS_PER_SEC) << "s" << "             \r";

	}

	return a.exec();

}

