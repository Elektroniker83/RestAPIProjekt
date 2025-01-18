//
// Created by muell on 12.01.2025.
//

#include "GoogleMapsAPI.h"
#include <curl/curl.h>
#include <iostream>
#include <algorithm>
#include "CurlUtils.h"

using namespace std;

// Konstruktor für die GoogleMapsAPI-Klasse. Initialisiert den API-Schlüssel.
GoogleMapsAPI::GoogleMapsAPI(const std::string& apiKey) : apiKey(apiKey) {}

// Funktion, die eine Anfrage an die Google Maps API stellt.
std::string GoogleMapsAPI::queryAPI(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response_string;

    curl = curl_easy_init();    // Initialisiert curl.
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());   // Setzt die URL.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);   // Setzt die Callback-Funktion.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);    // Speichert die Antwort.
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // Deaktiviert SSL-Überprüfung.
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);  // Deaktiviert Hostname-Überprüfung.

        res = curl_easy_perform(curl);  // Führt die Anfrage aus.
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);    // Bereinigt curl.
    }
    return response_string; // Gibt die API-Antwort zurück
}

// Extrahiert die Postleitzahl aus den Address-Komponenten der API-Antwort.
std::string GoogleMapsAPI::getPostalCode(const nlohmann::json& address_components) {
    for (const auto& component : address_components) {
        for (const auto& type : component["types"]) {
            if (type == "postal_code") {
                return component["long_name"];
            }
        }
    }
    return "";  // Rückgabe leerer String, falls keine Postleitzahl gefunden wird
}

// Hauptmethode, um Geodaten von der API zu erhalten und zu verarbeiten.
void GoogleMapsAPI::getLocationData(const std::string& address, bool showCoordinates) {
    std::string query = "https://maps.googleapis.com/maps/api/geocode/json?address=" + address + "&key=" + apiKey;
    std::string response = queryAPI(query);

    if (response.empty()) {
        std::cerr << "Fehler: Leere Antwort von der API erhalten.\n";
        return;
    }

    try {
        json data = json::parse(response);
        printGoogleMapsData(data, showCoordinates);
    } catch (const json::parse_error& e) {
        std::cerr << "JSON-Parsing-Fehler: " << e.what() << '\n';
    }
}

// Gibt die Geodaten aus, entweder als Koordinaten oder als formatierte Adresse.
void GoogleMapsAPI::printGoogleMapsData(const json& data, bool showCoordinates) {
    if (data.contains("results") && data["results"].size() > 0) {
        std::string formatted_address = data["results"][0]["formatted_address"];
        double lat = data["results"][0]["geometry"]["location"]["lat"];
        double lng = data["results"][0]["geometry"]["location"]["lng"];
        std::string postal_code = getPostalCode(data["results"][0]["address_components"]);

        if (showCoordinates) {
            std::cout << "Koordinaten: Breitengrad: " << lat << ", Laengengrad: " << lng << "\n";
        } else {
            std::cout << "Postleitzahl: " << formatted_address << "\n";
        }
    } else {
        std::cerr << "Keine Ergebnisse gefunden oder ungueltige Antwort.\n";
    }
}
