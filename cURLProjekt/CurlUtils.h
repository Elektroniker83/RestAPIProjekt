//
// Created by muell on 12.01.2025.
//

#ifndef CURLPROJEKT_CURLUTILS_H
#define CURLPROJEKT_CURLUTILS_H


#include <string>

// Callback-Funktion für curl, um die Antwort zu sammeln
// Deklaration der Callback-Funktion für curl.
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);


#endif //CURLPROJEKT_CURLUTILS_H
