#pragma once
#include "includes.h"

namespace PID
{
	namespace FUNCTIONS
	{
		void alloc_variables();
	}
	namespace ENUM
	{
		enum Enum
		{
			Kp = 0,
			Kd = 1,
			Ki = 2,
			Target = 3,
			vec_size = 4,
			Sensor = 6,
		};
	}
	
	namespace CLASS
	{
		class PID {
		public:

			double* arr;
			const char* vec_name;



			// variables para el sistema Proporcional Integral Derivativo
			double *input = nullptr;
			double error;
			double last_error;
			double integral;
			double derivate;
			double result;
			double sumatori;

			PID(double*_arr, const char* _vec_name, double& _input)
			{
				arr = _arr;
				vec_name = _vec_name;
				input = &_input;
			}			

			void print();

			void print(ENUM::Enum Kselect);

		};
	}

	namespace VECTOR_CONSTANTS  
	{
		double altitude[static_cast<int>(ENUM::vec_size)] = {-1};
		double engines[static_cast<int>(ENUM::vec_size)] = { -1 };;
		double roll[static_cast<int>(ENUM::vec_size)] = { -1 };;
		double yaw[static_cast<int>(ENUM::vec_size)] = { -1 };;
		double pitch[static_cast<int>(ENUM::vec_size)] = { -1 };;
	}

	namespace OBJ
	{
		// PID constructor obj(&array, vec_name, &input)
		PID::CLASS::PID altitude(VECTOR_CONSTANTS::altitude, "altitude", ENVIR::Inputs::altitude_AGL);
		PID::CLASS::PID engines(VECTOR_CONSTANTS::engines, "engines", ENVIR::Inputs::airspeed);
		PID::CLASS::PID roll(VECTOR_CONSTANTS::roll, "roll", ENVIR::Inputs::roll);
		PID::CLASS::PID yaw(VECTOR_CONSTANTS::yaw, "yaw", ENVIR::Inputs::yaw);
		PID::CLASS::PID pitch(VECTOR_CONSTANTS::pitch, "pitch", ENVIR::Inputs::pitch);
	};

	void FUNCTIONS::alloc_variables()
	{
		// TODO: Make a clean func instead of copypaste all code.
		csv::csv_manager PID(csv::paths::PID);

		prdebug("constants found in the file {0}:", PID.filename);

		PID.variable_alloc("altitude", "Kp", VECTOR_CONSTANTS::altitude[ENUM::Kp]);
		PID.variable_alloc("altitude", "Kd", VECTOR_CONSTANTS::altitude[ENUM::Kd]);
		PID.variable_alloc("altitude", "Ki", VECTOR_CONSTANTS::altitude[ENUM::Ki]);
		PID.variable_alloc("altitude", "Target", VECTOR_CONSTANTS::altitude[ENUM::Target]);

		/*const char* a[4] = {"Kp", "Kd", "Ki", "Target"};

		for (int i = 0; i < 4; i++)
		{
			PID.variable_alloc("altitude", a[i], VECTOR_CONSTANTS::altitude[i]);
		}*/

		PID.variable_alloc("engines", "Kp", VECTOR_CONSTANTS::engines[ENUM::Kp]);
		PID.variable_alloc("engines", "Kd", VECTOR_CONSTANTS::engines[ENUM::Kd]);
		PID.variable_alloc("engines", "Ki", VECTOR_CONSTANTS::engines[ENUM::Ki]);
		PID.variable_alloc("engines", "Target", VECTOR_CONSTANTS::engines[ENUM::Target]);

		PID.variable_alloc("roll", "Kp", VECTOR_CONSTANTS::roll[ENUM::Kp]);
		PID.variable_alloc("roll", "Kd", VECTOR_CONSTANTS::roll[ENUM::Kd]);
		PID.variable_alloc("roll", "Ki", VECTOR_CONSTANTS::roll[ENUM::Ki]);
		PID.variable_alloc("roll", "Target", VECTOR_CONSTANTS::roll[ENUM::Target]);

		PID.variable_alloc("yaw", "Kp", VECTOR_CONSTANTS::yaw[ENUM::Kp]);
		PID.variable_alloc("yaw", "Kd", VECTOR_CONSTANTS::yaw[ENUM::Kd]);
		PID.variable_alloc("yaw", "Ki", VECTOR_CONSTANTS::yaw[ENUM::Ki]);
		PID.variable_alloc("yaw", "Target", VECTOR_CONSTANTS::yaw[ENUM::Target]);

		PID.variable_alloc("pitch", "Kp", VECTOR_CONSTANTS::pitch[ENUM::Kp]);
		PID.variable_alloc("pitch", "Kd", VECTOR_CONSTANTS::pitch[ENUM::Kd]);
		PID.variable_alloc("pitch", "Ki", VECTOR_CONSTANTS::pitch[ENUM::Ki]);
		PID.variable_alloc("pitch", "Target", VECTOR_CONSTANTS::pitch[ENUM::Target]);
	}
}
