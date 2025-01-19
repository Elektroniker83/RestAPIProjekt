//
// Created by muell on 12.01.2025.
//

// Header-Datei für die GoogleMapsAPI-Klasse, die die Interaktion mit der Google Maps API kapselt.
// Diese Klasse bietet Funktionen zum Abrufen und Verarbeiten von Geodaten über die API.

// Verhindert Mehrfacheinbindung dieser Header-Datei.
#ifndef CURLPROJEKT_GOOGLEMAPSAPI_H
#define CURLPROJEKT_GOOGLEMAPSAPI_H

#include <string>
#include "json.hpp" // Nlohmann JSON-Bibliothek zur einfachen Verarbeitung von JSON-Daten.

using json = nlohmann::json; // Definiert einen Alias für die JSON-Klasse, um den Code lesbarer zu machen.

// Definition der GoogleMapsAPI-Klasse.
class GoogleMapsAPI {
public:
    // Konstruktor: Initialisiert die Klasse mit dem bereitgestellten API-Schlüssel.
    GoogleMapsAPI(const std::string& apiKey);

    // Ruft Geodaten für eine bestimmte Adresse ab und gibt die Option, Koordinaten anzuzeigen.
    void getLocationData(const std::string& address, bool showCoordinates);

    // Gibt die erhaltenen Google Maps-Daten aus, optional mit Koordinaten.
    void printGoogleMapsData(const json& data, bool showCoordinates);

private:
    std::string apiKey; // Der API-Schlüssel für die Authentifizierung bei der Google Maps API.

    // Hilfsfunktion: Sendet eine Anfrage an die API und gibt die Antwort als String zurück.
    std::string queryAPI(const std::string& url);

    // Hilfsfunktion: Extrahiert die Postleitzahl aus den JSON-Adressenkomponenten.
    std::string getPostalCode(const nlohmann::json& address_components);
};

#endif // CURLPROJEKT_GOOGLEMAPSAPI_H
