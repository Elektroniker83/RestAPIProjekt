//
// Created by muell on 12.01.2025.
//

#include "WeatherAPI.h"
#include <curl/curl.h>
#include <iostream>
#include "CurlUtils.h"

using namespace std;

// Konstruktor der WeatherAPI-Klasse. Initialisiert den API-Schlüssel.
WeatherAPI::WeatherAPI(const std::string& apiKey) : apiKey(apiKey) {}

// Methode zum Senden einer Anfrage an die angegebene URL und Rückgabe der Antwort als String.
std::string WeatherAPI::queryAPI(const std::string& url) {
    CURL* curl; // Zeiger auf eine cURL-Instanz.
    CURLcode res; // Enthält den Statuscode des cURL-Vorgangs.
    std::string response_string; // String zur Speicherung der API-Antwort.

    curl = curl_easy_init(); // Initialisiert cURL.
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Legt die URL für die Anfrage fest.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Setzt die Callback-Funktion, die die Antwortdaten verarbeitet.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string); // Übergibt die Referenz auf den Speicher, in dem die Antwort gespeichert wird.
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // SSL deaktivieren
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);  // SSL deaktivieren

        res = curl_easy_perform(curl); // Führt die Anfrage aus.
        if (res != CURLE_OK) {
            // Gibt im Fehlerfall die Fehlermeldung aus.
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl); // Bereinigt und schließt die cURL-Instanz.
    }
    return response_string; // Gibt die Antwort als String zurück.
}

// Methode zur Abfrage von Wetterdaten für eine bestimmte Ortschaft.
void WeatherAPI::getWeatherData(const std::string& city) {
    // Erstellt die URL für die OpenWeatherMap-API-Anfrage mit dem API-Schlüssel.
    std::string query = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&lang=de";
    // Führt die API-Anfrage aus und speichert die Antwort.
    std::string response = queryAPI(query);

    if (response.empty()) {
        // Gibt eine Fehlermeldung aus, wenn die Antwort leer ist.
        std::cerr << "Fehler: Leere Antwort von der API erhalten.\n";
        return;
    }

    try {
        json data = json::parse(response); // Parsen der JSON-Antwort.
        printWeatherData(data); // Gibt die Wetterdaten aus.
    } catch (const json::parse_error& e) {
        // Fehlerbehandlung für ungültiges JSON.
        std::cerr << "JSON-Parsing-Fehler: " << e.what() << '\n';
    }
}

// Methode zur Ausgabe der Wetterdaten im Konsolenfenster.
void WeatherAPI::printWeatherData(const json& data) {
    // Überprüft, ob die relevanten Datenfelder in der Antwort enthalten sind.
    if (data.contains("name") && data.contains("main") && data["main"].contains("temp")) {
        // Konvertiert die Temperatur von Kelvin in Celsius.
        double tempCelsius = data["main"]["temp"].get<double>() - 273.15;
        std::cout << "Wetter in " << data["name"] << ":\n";
        std::cout << "Temperatur: " << tempCelsius << " °C\n";
        // Überprüft, ob eine Wetterbeschreibung verfügbar ist, und gibt sie aus.
        if (data["weather"].size() > 0 && data["weather"][0].contains("description")) {
            std::cout << "Wetterbeschreibung: " << data["weather"][0]["description"] << "\n";
        }
    } else {
        // Gibt eine Fehlermeldung aus, wenn die empfangenen Daten ungültig sind.
        std::cerr << "Ungueltige Wetterdaten empfangen.\n";
    }
}
