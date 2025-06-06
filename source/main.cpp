#include "game.hpp"
#include "log.hpp"
#include "parse.hpp"
#include "scraper.hpp"
#include "notification.hpp"
#include <curl/curl.h>
#include <iostream>
#include <vector>
using std::vector;
using std::cout;

int main() {
	
	curl_global_init(CURL_GLOBAL_ALL);

	if (scrapeToFile() != 0) {
		cout << "Scraper error\n";
		return 1;
	}
	
	vector gamesList = findGames();
	updateLog(gamesList);
	cleanupGameList(gamesList); //deletes already-logged entries
	
	
	if(gamesList.size() == 0) {
		cout << "No new games found\n"; //try adding the time here. ctime lib?
		curl_global_cleanup();
		return 0;
	} //if we're still going, new titles are guaranteed
	
	//alright lets send the email notifs
	if (!sendEmail(gamesList)) {
		curl_global_cleanup();
		return 2;
	}
	
	curl_global_cleanup();
	return 0;
}
