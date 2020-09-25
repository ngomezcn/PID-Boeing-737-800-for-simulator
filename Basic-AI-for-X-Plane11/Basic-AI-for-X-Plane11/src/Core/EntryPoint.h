#pragma once
#include "includes.h"

namespace Init
{
	void Log()
	{
		spdlog::set_pattern("%^[%l]%$ %v");

		prinfo("Log initialized");

		spdlog::set_level(spdlog::level::info);
	}
}

