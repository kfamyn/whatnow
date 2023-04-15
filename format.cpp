#include "format.hpp"

std::string formatDayOfWeek(int year, int month, int day)
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

std::string formatTime(std::string rawTime){
    static std::string ampm[] = {"AM", "PM"};
    std::string TimeFormatted = "";

    TimeFormatted += (std::stoi(rawTime.substr(0, 2)) % 12 != 0) ? std::to_string(std::stoi(rawTime.substr(0, 2)) % 12) : std::to_string(12);
    TimeFormatted += ampm[std::stoi(rawTime.substr(0, 2)) >= 12];
    return TimeFormatted;
}

std::string formatPrecipitationProbability(std::string rawProbability){
    std::string probabilityFormatted = "";
    probabilityFormatted += std::to_string(std::stoi(rawProbability));
    probabilityFormatted += "%";
    return probabilityFormatted;
}

std::string formatTemperature(std::string rawTemperature){
    return std::to_string(std::stoi(rawTemperature));
}

int formatTimeToInt(std::string rawTime){
    return std::stoi(rawTime.substr(0, 2));
}
