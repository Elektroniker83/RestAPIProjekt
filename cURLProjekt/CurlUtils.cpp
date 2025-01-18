//
// Created by muell on 12.01.2025.
//

#include "CurlUtils.h"

// Callback-Funktion, um Daten, die von libcurl empfangen werden, in einen String zu schreiben.
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}
