#ifndef FORMAT_HPP
#define FORMAT_HPP
#include <iostream>
#include <stdlib.h>

enum timeAccuracy{ HOURS = 1, HOURS_AND_MINUTES = 2, FULL_ACCURACY = 3};

std::string formatDayOfWeek(int day, int month, int year);

std::string formatDate(std::string rawDate);

std::string formatTime(std::string rawTime, int accuracy = HOURS);

std::string formatPrecipitationProbability(std::string rawProbability);

std::string formatTemperature(std::string rawTemperature);

int formatTimeToInt(std::string rawTime);

int secondsSinceMidnight(std::string rawTime);

#endif // FORMAT_HPP
