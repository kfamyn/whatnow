#include "format.hpp"

std::string formatDayOfWeek(int day, int month, int year)
{
    static std::string daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    static int monthIndex[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return daysOfWeek[( year + year / 4 - year / 100 + year / 400 + monthIndex[month - 1] + day) % 7];
}

std::string formatDate(std::string rawDate){
    static std::string months[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    std::string dateFormatted = "";
    dateFormatted += rawDate.substr(8, 2);
    dateFormatted += months[std::stoi(rawDate.substr(5, 2)) - 1];
    return dateFormatted;
}

std::string formatTime(std::string rawTime, int accuracy){
    static std::string ampm[] = {"AM", "PM"};
    std::string timeFormatted = "";
    timeFormatted += (std::stoi(rawTime.substr(0, 2)) % 12 != 0) ? std::to_string(std::stoi(rawTime.substr(0, 2)) % 12) : std::to_string(12);
    if (accuracy == HOURS_AND_MINUTES || accuracy == FULL_ACCURACY){
        timeFormatted += rawTime.substr(2, 3);
    }
    if (accuracy == FULL_ACCURACY){
        timeFormatted += rawTime.substr(5, 3);
    }
    timeFormatted += ampm[std::stoi(rawTime.substr(0, 2)) >= 12];
    return timeFormatted;
}

std::string formatPrecipitationProbability(std::string rawProbability){
    return std::to_string(std::stoi(rawProbability)).append("%");
}

std::string formatTemperature(std::string rawTemperature){
    return std::to_string(std::stoi(rawTemperature));
}

int formatTimeToInt(std::string rawTime){
    return std::stoi(rawTime.substr(0, 2));
}
