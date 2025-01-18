//
// Created by muell on 12.01.2025.
//

#ifndef CURLPROJEKT_MAINCONTROLLER_H
#define CURLPROJEKT_MAINCONTROLLER_H

#include <string>
#include "WeatherAPI.h"
#include "GoogleMapsAPI.h"

class MainController {
public:
    void run();
private:
    void handleWeatherAPI();
    void handleGoogleMapsAPI();
};

#endif // CURLPROJEKT_MAINCONTROLLER_H
