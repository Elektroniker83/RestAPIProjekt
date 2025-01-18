//
// Created by muell on 12.01.2025.
//

#include "WeatherAPI.h"
#include <curl/curl.h>
#include <iostream>
#include "CurlUtils.h"

using namespace std;


WeatherAPI::WeatherAPI(const std::string& apiKey) : apiKey(apiKey) {}

std::string WeatherAPI::queryAPI(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response_string;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // SSL deaktivieren
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);  // SSL deaktivieren

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return response_string;
}

void WeatherAPI::getWeatherData(const std::string& city) {
    std::string query = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&lang=de";
    std::string response = queryAPI(query);

    if (response.empty()) {
        std::cerr << "Fehler: Leere Antwort von der API erhalten.\n";
        return;
    }

    try {
        json data = json::parse(response);
        printWeatherData(data);
    } catch (const json::parse_error& e) {
        std::cerr << "JSON-Parsing-Fehler: " << e.what() << '\n';
    }
}

void WeatherAPI::printWeatherData(const json& data) {
    if (data.contains("name") && data.contains("main") && data["main"].contains("temp")) {
        double tempCelsius = data["main"]["temp"].get<double>() - 273.15;
        std::cout << "Wetter in " << data["name"] << ":\n";
        std::cout << "Temperatur: " << tempCelsius << " °C\n";
        if (data["weather"].size() > 0 && data["weather"][0].contains("description")) {
            std::cout << "Wetterbeschreibung: " << data["weather"][0]["description"] << "\n";
        }
    } else {
        std::cerr << "Ungueltige Wetterdaten empfangen.\n";
    }
}
