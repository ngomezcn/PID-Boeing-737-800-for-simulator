#pragma once
#include "includes.h"
void Clear()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	#include "caraalsol.h"
#endif
}

using namespace std;

int main() {

	Init::Log(spdlog::level::info);

	double hola = 2.3;

	while (true)
	{
		PID::FUNCTIONS::alloc_variables();	

		cout << string(100, '\n');
		
		PID::OBJ::altitude.print(PID::ENUM::Sensor);
		//PID::OBJ::engines.print();
		//PID::OBJ::pitch.print();
		//PID::OBJ::roll.print();
		//PID::OBJ::yaw.print();
		Sleep(600);
	}
}

