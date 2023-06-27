#include "weatherAPI.h"
#include "curl/curl.h"
#include <fstream>
#include <cstddef>
#include <iostream>
#include <stdlib.h>

Weather::Weather(){}

void Weather::update(std::string city)
{
    try {
        weatherData = nlohmann::json::parse(request(formatInput(city)));
    }
    catch (std::exception e){
        weatherData = nlohmann::json::parse(request("Cupertino"));
    }
}

std::string Weather::getAddress(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    std::string fullAddress(weatherData.value("resolvedAddress", "Error getting precise address"));
    std::string shortAddress = "";
    for (size_t index = 0; fullAddress[index]!= ','; ++index){
        shortAddress += fullAddress[index];
    }
    int lastCommaIndex = fullAddress.length() - 1;
    while (lastCommaIndex != 0 && (fullAddress[lastCommaIndex] != ','))
    {
        --lastCommaIndex;
    }
    shortAddress += fullAddress.substr(lastCommaIndex);
    return shortAddress;
}

std::string Weather::getValue(int day, std::string key){
    std::string value(weatherData["days"][day][key].dump());
    if (value.find('"') != std::string::npos){
        value.erase(0, 1);
        value.erase(value.length() - 1, 2);
    }
    return value;
    }

std::string Weather::getCurrentConditions(std::string key){
    std::string value(weatherData["currentConditions"][key].dump());
    if (value.find('"') != std::string::npos){
        value.erase(0, 1);
        value.erase(value.length() - 1, 2);
    }
    return value;
}

std::string Weather::getHourlyConditions(int day, int hour, std::string key){
    std::string value(weatherData["days"][day]["hours"][hour][key].dump());
    if (value.find('"') != std::string::npos){
        value.erase(0, 1);
        value.erase(value.length() - 1, 2);
    }
    return value;
}

typedef size_t(*curl_write)(char*, size_t, size_t, std::string*);

std::string Weather::request(std::string city) {
    CURLcode res_code = CURLE_FAILED_INIT;
    CURL* curl = curl_easy_init();
    std::string result;
    std::string url = "https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/" + city + "?unitGroup=metric&key=LBME92TM9HRUY3VG2TP2D7LKF&iconSet=icons2&contentType=json";
    curl_global_init(CURL_GLOBAL_ALL);
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 0);
        curl_easy_setopt(curl,
            CURLOPT_WRITEFUNCTION,
            static_cast <curl_write> ([](char* contents, size_t size,
                size_t nmemb, std::string* data) -> size_t {
                    size_t new_size = size * nmemb;
                    if (data == NULL) {
                        return 0;
                    }
                    data->append(contents, new_size);
                    return new_size;
                }));
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Weather getter");
        res_code = curl_easy_perform(curl);
        if (res_code != CURLE_OK) {
            return curl_easy_strerror(res_code);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return result;
}

std::string& Weather::formatInput(std::string& inputString) {
    std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
    size_t spacePosition = 0;
    while ((spacePosition = inputString.find(" ")) != std::string::npos) {
        inputString.erase(spacePosition, 1);
        inputString.insert(spacePosition, "%20");
    }
    return inputString;
}

