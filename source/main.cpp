#include "game.hpp"
#include "log.hpp"
#include "parse.hpp"
#include "scraper.hpp"
#include <curl/curl.h>
#include <iostream>
#include <vector>
using std::vector;
using std::cout;

int main() {
	
	curl_global_init(CURL_GLOBAL_ALL);

	if (scrapeToFile() != 0) {
		cout << "Scraper error\n";
	}
	
	vector gamesList = findGames();
	
	if(gamesList.size() == 0) {
		cout << "Game list is empty. No games found\n";
		curl_global_cleanup();
		return -1;
	}
	
	if (!updateLog(gamesList)) {
		cout << "Error saving game list";
		return -1;
	}
	
	/*email up next. it's not written yet lol*/
}
