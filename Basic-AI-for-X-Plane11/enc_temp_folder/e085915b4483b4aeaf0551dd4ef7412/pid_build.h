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
			var_name = 5,
		};
	}
	
	namespace CLASS
	{
		class PID {
		public:

			double* arr;

			const char* vec_name;

			PID(double*_arr, const char* _vec_name)
			{
				arr = _arr;
				vec_name = _vec_name;
			}


			void print();
		};
	}

	namespace VECTOR_CONSTANTS  
	{
		double altitude[static_cast<int>(ENUM::vec_size)];
		double engines[static_cast<int>(ENUM::vec_size)];
		double roll[static_cast<int>(ENUM::vec_size)];
		double yaw[static_cast<int>(ENUM::vec_size)];
		double pitch[static_cast<int>(ENUM::vec_size)];
	}

	namespace OBJ
	{
		PID::CLASS::PID altitude(VECTOR_CONSTANTS::altitude, "altitude");
		PID::CLASS::PID engines(VECTOR_CONSTANTS::engines, "engines");
		PID::CLASS::PID roll(VECTOR_CONSTANTS::roll, "roll");
		PID::CLASS::PID yaw(VECTOR_CONSTANTS::yaw, "yaw");
		PID::CLASS::PID pitch(VECTOR_CONSTANTS::pitch, "pitch");
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
