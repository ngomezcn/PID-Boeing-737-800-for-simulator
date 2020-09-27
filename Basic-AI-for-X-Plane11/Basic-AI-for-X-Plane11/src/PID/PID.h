#include "pid_build.h"

namespace PID
{
	namespace CLASS
	{
		void PID::print()
		{
			prinfo("Printing vector: {0}", vec_name);			
			
			prinfo("Kp: {0}", arr[ENUM::Kp]);	
			prinfo("Kd: {0}", arr[ENUM::Kd]);
			prinfo("Ki: {0}", arr[ENUM::Ki]);
			prinfo("Target: {0}", arr[ENUM::Target]);						
			prinfo("Sensor: {0}", *input);
		}

		void PID::print(ENUM::Enum Kselect)
		{
			switch (static_cast<int>(Kselect))
			{
			case ENUM::Kp: prinfo("Kp: {0}", arr[ENUM::Kp]); break;

			case ENUM::Kd: prinfo("Kp: {0}", arr[ENUM::Kd]); break;
			case ENUM::Ki: prinfo("Kp: {0}", arr[ENUM::Ki]); break;
			case ENUM::Target: prinfo("Kp: {0}", arr[ENUM::Target]); break;
			case ENUM::Sensor: prinfo("Sensor: {0}", *input); break;

			default:
				print();
				break;
			}
		}
	}
}

