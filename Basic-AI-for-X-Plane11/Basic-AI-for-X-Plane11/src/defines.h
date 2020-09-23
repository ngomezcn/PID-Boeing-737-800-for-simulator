#pragma once

#define extraComa 1 // Se utiliza para separar los valores de las comas.

#define SIM 0
#define ARDUINO 1

#define prtrace(...)     spdlog::trace(__VA_ARGS__)
#define prdebug(...)     spdlog::debug(__VA_ARGS__)
#define prinfo(...)      spdlog::info(__VA_ARGS__)
#define prwarn(...)      spdlog::warn(__VA_ARGS__)
#define prerror(...)     spdlog::error(__VA_ARGS__)
#define prcriticial(...) spdlog::critical(__VA_ARGS__)