#pragma once
#include "includes.h"

namespace PID
{
	enum pid_var
	{
		Kp = 0,
		Kd = 1,
		Ki = 2,
		Target = 3,
		pid_var = 4,
	};

	namespace variables
	{

		double altitude[pid_var];
		double engines[pid_var];
		double roll[pid_var];
		double yaw[pid_var];
		double pitch[pid_var];

	}

	int PID_alloc_variables()
	{
		csv::csv_manager PID(csv::paths::PID);

		prdebug("Variables found in the file {0}:", PID.filename);

		PID.variable_alloc("altitude", "Kp", PID::variables::altitude[PID::Kp]);
		PID.variable_alloc("altitude", "Kd", PID::variables::altitude[PID::Kd]);
		PID.variable_alloc("altitude", "Ki", PID::variables::altitude[PID::Ki]);
		PID.variable_alloc("altitude", "Target", PID::variables::altitude[PID::Target]);

		PID.variable_alloc("engines", "Kp", PID::variables::engines[PID::Kp]);
		PID.variable_alloc("engines", "Kd", PID::variables::engines[PID::Kd]);
		PID.variable_alloc("engines", "Ki", PID::variables::engines[PID::Ki]);
		PID.variable_alloc("engines", "Target", PID::variables::engines[PID::Target]);

		PID.variable_alloc("roll", "Kp", PID::variables::roll[PID::Kp]);
		PID.variable_alloc("roll", "Kd", PID::variables::roll[PID::Kd]);
		PID.variable_alloc("roll", "Ki", PID::variables::roll[PID::Ki]);
		PID.variable_alloc("roll", "Target", PID::variables::roll[PID::Target]);

		PID.variable_alloc("yaw", "Kp", PID::variables::yaw[PID::Kp]);
		PID.variable_alloc("yaw", "Kd", PID::variables::yaw[PID::Kd]);
		PID.variable_alloc("yaw", "Ki", PID::variables::yaw[PID::Ki]);
		PID.variable_alloc("yaw", "Target", PID::variables::yaw[PID::Target]);

		PID.variable_alloc("pitch", "Kp", PID::variables::pitch[PID::Kp]);
		PID.variable_alloc("pitch", "Kd", PID::variables::pitch[PID::Kd]);
		PID.variable_alloc("pitch", "Ki", PID::variables::pitch[PID::Ki]);
		PID.variable_alloc("pitch", "Target", PID::variables::pitch[PID::Target]);

	}
}
