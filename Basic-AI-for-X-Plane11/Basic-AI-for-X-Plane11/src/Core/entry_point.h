#include <includes.h>

namespace Init
{
	void Log(spdlog::level::level_enum level)
	{
		spdlog::set_pattern("%^[%l]%$ %v");

		prinfo("Log initialized");

		spdlog::set_level(level);
	}


}

