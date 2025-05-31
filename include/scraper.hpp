#pragma once


#include <cstddef>

size_t write_callback(char *incomingData, size_t size, size_t nmemb, void *outputFile);

int scrapeToFile();