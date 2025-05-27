#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <cstdlib> //for size_t


//im brand new to libcurl, lots of comments incoming
int main() { //once im done testing, this will need to not be main 
	
	curl_global_init(CURL_GLOBAL_ALL);
	//so i guess type CURL is a thing now
	CURL *steamHandle = curl_easy_init();

	if (!steamHandle) {
		
		std::cout << "Failed to create CURL handle\n";
		return -1;
	}
	
	curl_easy_setopt(steamHandle, CURLOPT_URL, "https://store.steampowered.com/search/?maxprice=free&supportedlang=english&specials=1&ndl=1");
	//need a setopt call to set data output
	char errorBuffer[CURL_ERROR_SIZE];
	curl_easy_setopt(&steamHandle, CURLOPT_ERRORBUFFER, &errorBuffer);


	if (curl_easy_perform(steamHandle) != CURLE_OK) {
		std::cout << curl_easy_strerror << "\n" 
		std::cout << errorBuffer << "\n";
		return -1;
	}
	
	//deletes handle, we won't be needing it anymore
	curl_easy_cleanup(steamHandle);
	
	return 0;
	
}


// define function to handle incoming data here
size_t write_callback(char *incomingData, size_t size, size_t nmemb, void *userdata) {

	fstream outputFile("steam_source.txt", ios::out | ios::app | ios::binary);
	if (!outputFile) {
		return -1;
	}

	if (outputFile << *incomingData) {
		return size * nmemb;
	}
	else {
		return -1;
	}
}



/* in scraped html file:
	- "<!-- List Items -->" commment marks list start
	- "<a href" marks useful data
	- "<!-- End List Items -->" commment marks list end 
*/