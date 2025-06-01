#pragma once

#include <string>

struct game {
    std::string title;
    std::string url;
    std::string appID;
	bool isNew = 1;
	
	bool isComplete() {
		return !title.empty() && !url.empty() && !appID.empty();
	}
	
	void reset() {
		
		title.clear();
		url.clear();
		appID.clear();
	}
};