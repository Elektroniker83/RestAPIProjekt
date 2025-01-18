# Anleitung zur Installation, Kompilierung und Nutzung

## 1. Installation von Abhängigkeiten
Für das Projekt werden folgende Bibliotheken benötigt:

- **cURL**: Für HTTP-Anfragen an die APIs.  
- **nlohmann/json**: Für das Parsen der JSON-Antworten der APIs.

### a. Installation von cURL:
- **Für Windows**: Du kannst cURL über den Windows-Paketmanager `winget` installieren:
  ```bash
  winget install curl
  ```
- Alternativ kannst du cURL von [curl.se](https://curl.se) herunterladen und installieren.

### b. Installation von nlohmann/json:
- Du kannst die JSON-Bibliothek über CMake von GitHub einbinden:
  ```bash
  git clone https://github.com/nlohmann/json.git
  ```
- Stelle sicher, dass du die `json.hpp`-Datei in deinem Projekt verwendest.

---

## 2. Projekt einrichten
- Lade oder erstelle die Quelldateien in einem Verzeichnis.
- Erstelle eine CMake-Konfigurationsdatei (`CMakeLists.txt`), um das Projekt zu kompilieren.

### Beispiel für die `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.10)
project(cURLProjekt)

set(CMAKE_CXX_STANDARD 14)

# cURL und JSON-Header einbinden
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(path/to/json)

add_executable(cURLProjekt main.cpp WeatherAPI.cpp GoogleMapsAPI.cpp CurlUtils.cpp MainController.cpp)

target_link_libraries(cURLProjekt ${CURL_LIBRARIES})
```

---

## 3. Kompilierung des Projekts
- Öffne das Projekt in deiner IDE (z. B. CLion) oder benutze die Kommandozeile, um das Projekt zu kompilieren:
  
  - **In CLion**: Drücke `Shift + F9` (Build).
  - **Mit CMake in der Kommandozeile:**
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

---

## 4. API-Schlüssel
- Du musst für beide APIs (OpenWeatherMap und Google Maps) API-Schlüssel erhalten:
  - **OpenWeatherMap API**: Registriere dich auf [openweathermap.org](https://openweathermap.org) und hole dir einen API-Schlüssel.
  - **Google Maps API**: Registriere dich auf [console.cloud.google.com](https://console.cloud.google.com) und erhalte einen API-Schlüssel.

Ersetze im Code die Platzhalter für die API-Schlüssel:
```cpp
apiKey = "dein_api_schluessel_fuer_openweathermap";  // OpenWeatherMap
apiKey = "dein_api_schluessel_fuer_google_maps";      // Google Maps
```

---

## 5. Nutzung des Programms
- Nach der Kompilierung kannst du das Programm ausführen.
- Es fragt den Benutzer, welche API er verwenden möchte (1 für OpenWeatherMap oder 2 für Google Maps).
- Je nach Auswahl wird entweder das Wetter für eine Stadt oder die Koordinaten bzw. die Adresse einer eingegebenen Adresse angezeigt.

### Beispiel:
#### OpenWeatherMap:
```bash
###################################################
#_________OpenWeatherMap / Google Maps____________#
###################################################
Willkommen bei der Rest API Abfrage
Wenn Sie OpenWeatherMap moechten, waehlen Sie bitte die 1.
Wenn Sie Google Maps moechten, waehlen Sie bitte die 2.
1
Geben Sie die gewuenschte Ortschaft ein:
Neuhausen
Wetter in "Neuhausen":
Temperatur: 5.4 ┬░C
Wetterbeschreibung: "Bedeckt"

Process finished with exit code 0
```

#### Google Maps:
```bash
###################################################
#_________OpenWeatherMap / Google Maps____________#
###################################################
Willkommen bei der Rest API Abfrage
Wenn Sie OpenWeatherMap moechten, waehlen Sie bitte die 1.
Wenn Sie Google Maps moechten, waehlen Sie bitte die 2.
2
Geben Sie die gewuenschte Ortschaft ein:
Hettlingen
Moechten Sie die Koordinaten oder die Postleitzahl anzeigen lassen?
1. Koordinaten
2. Postleitzahl
Gib deine Wahl ein (1/2):
1
Koordinaten: Breitengrad: 47.547, Laengengrad: 8.70879
```

---

## 6. Fehlerbehebung
- Falls du beim Kompilieren oder Ausführen Fehler bekommst, stelle sicher, dass alle Bibliotheken korrekt eingebunden sind und dass du die richtigen API-Schlüssel verwendest.
- Überprüfe die Ausgabe auf mögliche Fehler bei der API-Abfrage, z. B. ungültige Anfragen oder fehlende API-Schlüssel.
