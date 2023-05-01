#ifndef FORMAT_HPP
#define FORMAT_HPP
#include <iostream>
#include <stdlib.h>

std::string formatDayOfWeek(int day, int month, int year);

std::string formatDate(std::string rawDate);

std::string formatTime(std::string rawTime);

std::string formatPrecipitationProbability(std::string rawProbability);

std::string formatTemperature(std::string rawTemperature);

int formatTimeToInt(std::string rawTime);

#endif // FORMAT_HPP
