#pragma once
#include "includes.h"


#define trace(...)     spdlog::trace(__VA_ARGS__)
#define debug(...)     spdlog::debug(__VA_ARGS__)
#define info(...)      spdlog::info(__VA_ARGS__)
#define warn(...)      spdlog::warn(__VA_ARGS__)
#define error(...)     spdlog::error(__VA_ARGS__)
#define criticial(...) spdlog::critical(__VA_ARGS__)

namespace Core
{
	class Application
	{
	public:
		void Log();
	};

	void Application::Log()
	{
		info("Hola");
	}
}
