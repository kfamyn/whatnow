#ifndef WEATHERAPIH
#define WEATHERAPIH
#include <cstddef>
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include "curl/curl.h"
#include <string>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

class Weather {
public:
    Weather(std::string unprocessedCityData);
    std::string getAddress();
    std::string getValue(int offset, std::string key);
    std::string getCurrentConditions(std::string key);
    std::string getHourlyConditions(int offset, int hour, std::string key);
private:
    nlohmann::json weatherData;
};

std::string request(std::string city);

std::string& formatInput(std::string& inputString);

void showForecast(nlohmann::json& OutputData);

nlohmann::json getWeatherByDay(nlohmann::json& OutputData, int offset);

std::string getValue(nlohmann::json& weatherByDay, std::string key);

std::string getAddress(nlohmann::json& OutputData);

std::string dayOfWeek(int year, int month, int day);

#endif
