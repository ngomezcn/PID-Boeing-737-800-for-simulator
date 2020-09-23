#pragma once
#include "includes.h"



namespace Core
{
	class Application
	{
	public:
		void Log();
	};

	void Application::Log()
	{
		prinfo("Hola");
	}
}
