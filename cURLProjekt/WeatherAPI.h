//
// Created by muell on 12.01.2025.
//

// Header-Datei für die WeatherAPI-Klasse, die Funktionen zur Abfrage und Verarbeitung von Wetterdaten bereitstellt.

#ifndef CURLPROJEKT_WEATHERAPI_H
#define CURLPROJEKT_WEATHERAPI_H


#include <string>
#include "json.hpp"

using json = nlohmann::json; // Definiert einen Alias für die JSON-Klasse, um den Code lesbarer zu machen.

// Definition der WeatherAPI-Klasse, die die Funktionalität zur Interaktion mit einer Wetter-API bereitstellt.
class WeatherAPI {
public:
    WeatherAPI(const std::string& apiKey);  // Konstruktor: Initialisiert die Klasse mit einem API-Schlüssel.
    void getWeatherData(const std::string& city); // Ruft Wetterdaten für die angegebenen Ortschaft ab.
    void printWeatherData(const json& data); // // Gibt die empfangenen Wetterdaten im Konsolenfenster aus.

private:
    std::string apiKey; // Der API-Schlüssel, der zur Authentifizierung bei der Wetter-API verwendet wird.
    std::string queryAPI(const std::string& url); // Hilfsfunktion: Führt eine HTTP-Anfrage an die angegebene URL aus und gibt die Antwort als String zurück.
};

#endif //CURLPROJEKT_WEATHERAPI_H
