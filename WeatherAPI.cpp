#include "weatherAPI.hpp"
#include <vector>
Weather::Weather(std::string unprocessedCityData){
        std::string unprocessedData = request(formatInput(unprocessedCityData));
        weatherData = nlohmann::json::parse(unprocessedData);
    }
std::string Weather::getAddress(){
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

std::string Weather::getValue(int offset, std::string key){
    std::string value(weatherData["days"][offset][key].dump());
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

std::string Weather::getHourlyConditions(int offset, int hour, std::string key){
    std::string value(weatherData["days"][offset]["hours"][hour][key].dump());
    if (value.find('"') != std::string::npos){
        value.erase(0, 1);
        value.erase(value.length() - 1, 2);
    }
    return value;
}



typedef size_t(*curl_write)(char*, size_t, size_t, std::string*);

std::string request(std::string city) {
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
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "simple scraper");
        res_code = curl_easy_perform(curl);
        if (res_code != CURLE_OK) {
            return curl_easy_strerror(res_code);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return result;
}

std::string& formatInput(std::string& inputString) {
    std::transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);
    size_t spacePosition = 0;
    while ((spacePosition = inputString.find(" ")) != std::string::npos) {
        inputString.erase(spacePosition, 1);
        inputString.insert(spacePosition, "%20");
    }
    return inputString;
}

void showForecast(nlohmann::json& OutputData) {

    nlohmann::json OutputDataArray = OutputData["days"];
    std::cout << "Weather in " << OutputData.value("resolvedAddress", "Error getting precise address") << ":" << std::endl << std::endl;
    for (size_t i = 0; i < OutputDataArray.size(); i++)
    {
        std::cout << OutputDataArray[i].value("datetime", "Error getting date information") << ": " << OutputDataArray[i]["tempmax"] << "   " << OutputDataArray[i]["tempmin"] << std::endl;
        std::cout << OutputDataArray[i].value("conditions", "Error getting max temperature information") << std::endl << std::endl;
    }
}


nlohmann::json getWeatherByDay(nlohmann::json& OutputData, int offset) { // offset 0 - today, 1 - tomorrow...
    nlohmann::json weatherByDay = OutputData["days"][offset];
    return weatherByDay;
}

std::string getValue(nlohmann::json& weatherByDay, std::string key) {
    return std::string(weatherByDay.value(key, "Error getting a value"));
}

std::string getAddress(nlohmann::json& OutputData){
    std::string fullAddress(OutputData.value("resolvedAddress", "Error getting precise address"));
    std::string shortAddress = "";
    for (size_t index = 0; fullAddress[index]!= ','; ++index){
        shortAddress += fullAddress[index];
    }
    int lastCommaIndex = fullAddress.length() - 1; // last character
    while (lastCommaIndex != 0 && (fullAddress[lastCommaIndex] != ','))
    {
        --lastCommaIndex;
    }
    shortAddress += fullAddress.substr(lastCommaIndex); // +1 to skip leading space
    return shortAddress;
}

