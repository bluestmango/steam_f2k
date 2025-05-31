#include <vector>
#include <string>

#pragma once

struct game {
    std::string title;
    std::string url;
    std::string appID;
	
	bool isComplete() {
		return !title.empty() && !url.empty() && !appID.empty();
	}
	
	void reset() {
		
		title.clear();
		url.clear();
		appID.clear();
	}
};

std::vector<game> findGames();