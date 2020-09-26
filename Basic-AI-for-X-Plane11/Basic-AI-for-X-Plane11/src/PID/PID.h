#include "pid_build.h"

namespace PID
{
	class _PID {       
	public:            
				
		double(&state)[4];

		_PID(double(&arr)[4]): state(arr)
		{
		
		}

		void print()
		{
			
			for (int x = 0; x < 4; x++)
				std::cout << state[x + 0 * 4] << " ";
			
		}
	};

	void PID()
	{
		PID_alloc_variables();

		PID::_PID altitude(PID::variables::altitude);
		PID::_PID engines(PID::variables::engines);
		PID::_PID roll(PID::variables::roll);
		PID::_PID yaw(PID::variables::yaw);
		PID::_PID pitch(PID::variables::pitch);		

		altitude.print();		
	}	

	void hola()
	{
		PID::altitude.print();

	}
}

