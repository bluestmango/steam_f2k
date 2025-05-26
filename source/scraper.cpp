#include <curl/curl.h>
#include <iostream>
#include <cstdlib> //for size_t

using namespace std;

//im brand new to libcurl, lots of comments incoming
int main() { //once im done testing, this will need to not be main 
	
	curl_global_init(CURL_GLOBAL_ALL);
	//so i guess type CURL is a thing now
	CURL *steamHandle = curl_easy_init();

	if (!steamHandle) {
		
		cout << "Failed to create CURL handle\n";
		return -1;
	}
	
	curl_easy_setopt(steamHandle, CURLOPT_URL, "https://store.steampowered.com/search/?maxprice=free&supportedlang=english&specials=1&ndl=1");
	//need a setopt call to set data output
	char errorBuffer[CURL_ERROR_SIZE];
	curl_easy_setopt(&steamHandle, CURLOPT_ERRORBUFFER, &errorBuffer);

	CURLcode returnCode = curl_easy_perform(steamHandle);
	if (returnCode != CURLE_OK) {
		std::cout << curl_easy_strerror << "\n";
		std::cout << errorBuffer << "\n";
		return -1;
	}
	
	//deletes handle, we won't be needing it anymore
	curl_easy_cleanup(steamHandle);
	
	return 0;
	
	
}


// define function to handle incoming data here




/* in scraped html file:
	- "<!-- List Items -->" commment marks list start
	- "<a href" marks useful data
	- "<!-- End List Items -->" commment marks list end 
*/