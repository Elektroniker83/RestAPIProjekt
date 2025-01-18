//
// Created by muell on 12.01.2025.
//

#ifndef CURLPROJEKT_WEATHERAPI_H
#define CURLPROJEKT_WEATHERAPI_H


#include <string>
#include "json.hpp"

using json = nlohmann::json;

class WeatherAPI {
public:
    WeatherAPI(const std::string& apiKey);
    void getWeatherData(const std::string& city);
    void printWeatherData(const json& data);

private:
    std::string apiKey;
    std::string queryAPI(const std::string& url);
};

#endif //CURLPROJEKT_WEATHERAPI_H
