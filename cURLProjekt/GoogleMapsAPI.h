//
// Created by muell on 12.01.2025.
//

#ifndef CURLPROJEKT_GOOGLEMAPSAPI_H
#define CURLPROJEKT_GOOGLEMAPSAPI_H

#include <string>
#include "json.hpp"

using json = nlohmann::json;

class GoogleMapsAPI {
public:
    GoogleMapsAPI(const std::string& apiKey);
    void getLocationData(const std::string& address, bool showCoordinates);
    void printGoogleMapsData(const json& data, bool showCoordinates);

private:
    std::string apiKey;
    std::string queryAPI(const std::string& url);
    std::string getPostalCode(const nlohmann::json& address_components);
};

#endif // CURLPROJEKT_GOOGLEMAPSAPI_H
