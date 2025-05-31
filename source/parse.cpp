#include "parse.hpp"
#include <string>
#include <vector>
#include <fstream>
using std::vector;
using std::string;
using std::fstream;

//outputFile from scraper.cpp is now steam_source

vector<unsigned short> markQuotes(string line, char start ='\"', char end = '\"');

vector<game> findGames() {

    string line;
    bool isListFound = 0;
    fstream steam_source("steam_source.txt");

    while (getline(steam_source, line)) {

        if (line != "<!-- List Items -->") {
            continue;
        }
        isListFound = 1;
        break;
    }
    
    if (!isListFound) {
        return {};
    }
    vector<game> gameList = {};
	game newgame;
	
    while (getline(steam_source, line)) {

        if (line.find("a href=") != string::npos) {
            vector<unsigned short> indexes = markQuotes(line);
            newgame.url = line.substr(indexes[0]+1, indexes[1]-indexes[0]-1);
        }
        else if (line.find("data-ds-appid") != string::npos) {
            vector<unsigned short> indexes = markQuotes(line);
            newgame.appID = line.substr(indexes[0]+1, indexes[1]-indexes[0]-1);
        }
		else if (line.find("<span class=\"title\"") != string::npos) {
            vector<unsigned short> indexes = markQuotes(line, '>', '<');
            newgame.title = line.substr(indexes[0]+1, indexes[1]-indexes[0]-1);
        }
		else if (line.find("<!-- End List Items -->") != string::npos) {
			break;
		}
		
		if (newgame.isComplete()) {
			gameList.push_back(newgame);
			newgame.reset();
		}
		
    }

	return gameList;
}


vector<unsigned short> markQuotes(string line, char start, char end) {

    for (unsigned short x=0; x<line.size()-1;x++) {
        if (line[x] == start) {

            for (unsigned short y=x+1;y<line.size();y++) {
                if (line[y] == end) {
                    return {x,y};
                }
            }
            return {0,0};
        }
    }
    return {0,0};
} 