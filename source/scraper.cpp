#include "scraper.hpp"
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <cstdlib> //for size_t


//im brand new to libcurl, lots of comments incoming
int scrapeToFile() {
	
	//open output file
	std::fstream outputFile("steam_source.txt", std::ios::out | std::ios::trunc);
	if (!outputFile) {
		std::cout << "Failed to create output file\n";
		return -1;
	}
	
	CURL *steamHandle = curl_easy_init();

	if (!steamHandle) {	
		std::cout << "Failed to create CURL handle\n";
		return -1;
	}
	
	curl_easy_setopt(steamHandle, CURLOPT_URL, "https://store.steampowered.com/search/?maxprice=free&supportedlang=english&specials=1&ndl=1");
	curl_easy_setopt(steamHandle, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(steamHandle, CURLOPT_WRITEDATA, &outputFile);
	char errorBuffer[CURL_ERROR_SIZE];
	curl_easy_setopt(&steamHandle, CURLOPT_ERRORBUFFER, errorBuffer);


	CURLcode res = curl_easy_perform(steamHandle);
	if (res != CURLE_OK) {
		std::cout << curl_easy_strerror(res) << "\n";
		std::cout << errorBuffer << "\n";
		return -1;
	}
	
	//deletes handle, we won't be needing it anymore
	curl_easy_cleanup(steamHandle);
	outputFile.close();
	
	return 0;
	
}


size_t write_callback(char *incomingData, size_t size, size_t nmemb, void *voidPtr) {

	std::fstream* outputFilePtr = static_cast<std::fstream*>(voidPtr);
	
	if (outputFilePtr->write(incomingData, size * nmemb)) {
		return size * nmemb;
	}
	return -1;	
}
