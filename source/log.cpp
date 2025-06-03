/*ok heres the plan:
- if no list file, create one [x]
- check each appID against the list [x]
- flip bools when ids match [x]
- clear list (Addendum: this requires reopening with truncation) [x]
- copy in each ID [x]
- done [x]
*/
#include "log.hpp"
#include "game.hpp"
#include <fstream>
#include <vector>
#include <string>
using std::fstream;
using std::vector;
using std::string;

void updateLog(vector<game>& gamesList) {
	
	fstream IDlog;
	
	IDlog.open("IDlog.txt", std::ios::in);
	if (IDlog.is_open()) {

		string line;
		while (getline(IDlog, line)) {
			for (unsigned short i=0; i<gamesList.size(); i++) {
				if (gamesList[i].appID == line) {
					gamesList[i].isNew = 0;
				}
			}
		}
		IDlog.close();
		IDlog.clear();
	}
		
	IDlog.open("IDlog.txt", std::ios::out | std::ios::trunc);
	for (auto i : gamesList) {
		IDlog << i.appID << "\n";
	}
	IDlog.close();
}

void cleanupGameList(vector<game>& gameList) {
	
	for (unsigned short i=0; i<gameList.size(); i++) {
		if (!gameList[i].isNew) {
			gameList.erase(gameList.begin() + i);
			i--;
		}
	}
}