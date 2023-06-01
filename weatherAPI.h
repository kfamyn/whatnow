#ifndef WEATHERAPI_H
#define WEATHERAPI_H
#include <string>
#include <nlohmann/json.hpp>

class Weather {
public:
    Weather();
    void update(std::string city);
    std::string getAddress();
    std::string getValue(int day, std::string key);
    std::string getCurrentConditions(std::string key);
    std::string getHourlyConditions(int day, int hour, std::string key);
private:
    nlohmann::json weatherData;
    std::string request(std::string city);
    std::string& formatInput(std::string& inputString);
    std::string dayOfWeek(int year, int month, int day);
};

#endif
