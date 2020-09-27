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

		}
	}
}

