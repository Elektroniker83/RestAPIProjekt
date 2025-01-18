//
// Created by muell on 12.01.2025.
//

#include "MainController.h"
#include <iostream>
#include <string>

using namespace std;

// Hauptlogik der Anwendung.
void MainController::run() {
    int choice;

    std::cout << "###################################################" << endl;
    std::cout << "#_________OpenWeatherMap / Google Maps____________#" << endl;
    std::cout << "###################################################" << endl;
    std::cout << "Willkommen bei der Rest API Abfrage" << endl;
    std::cout << "Wenn Sie OpenWeatherMap moechten, waehlen Sie bitte die 1." << endl;
    std::cout << "Wenn Sie Google Maps moechten, waehlen Sie bitte die 2." << endl;
    std::cin >> choice;

    if (choice == 1) {
        handleWeatherAPI();
    } else if (choice == 2) {
        handleGoogleMapsAPI();
    } else {
        std::cerr << "Ungültige Auswahl!\n";
    }
}

// Wetter-API-Verarbeitung.
void MainController::handleWeatherAPI() {
    std::string apiKey = "ce742369cbc7d4b4bdaea6e38ccf6e9b";
    std::string city;
    std::cout << "Geben Sie die gewuenschte Ortschaft ein: \n";
    std::cin >> city;

    WeatherAPI weather(apiKey);
    weather.getWeatherData(city);
}

// Google Maps API-Verarbeitung.
void MainController::handleGoogleMapsAPI() {
    std::string apiKey = "AIzaSyCXrFb1261AUPwjWPzXUKI5bAol4g1blKU";
    std::string address;
    std::cout << "Geben Sie die gewuenschte Ortschaft ein: \n";
    std::cin.ignore();
    std::getline(std::cin, address);
    std::replace(address.begin(), address.end(), ' ', '+');

    int displayChoice;
    std::cout << "Moechten Sie die Koordinaten oder die Postleitzahl anzeigen lassen?\n1. Koordinaten\n2. Postleitzahl\nGib deine Wahl ein (1/2): \n";
    std::cin >> displayChoice;
    bool showCoordinates = (displayChoice == 1);

    GoogleMapsAPI googleMaps(apiKey);
    googleMaps.getLocationData(address, showCoordinates);
}