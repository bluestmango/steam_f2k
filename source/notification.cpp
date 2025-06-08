#include "game.hpp"
#include "notification.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <cstring> //only required on linux somehow
#include <curl/curl.h>

std::string emailContent;

const char* composeEmail(std::vector<game>& gamesList) {
	
	emailContent = //yes, this works fine
	"To: epiccryingmangos@gmail.com\r\n"
	"From: steamfree2keep@gmail.com\r\n" //optionally add cc line after this line
	"Subject: New Game(s)\r\n"
	"\r\n"; // empty line to divide headers from body
	
	//how tf do i insert them? thats future me's problem //oops guess im future me now
	if (gamesList.size() == 1) {
		emailContent += '\"' + gamesList[0].title + "\" ";
		emailContent += "is free on Steam: ";
		emailContent += gamesList[0].url + "\r\n";
	}
	else {
		emailContent += "The following games are free on Steam ";
		emailContent += "(https://store.steampowered.com/search/?maxprice=free&supportedlang=english&specials=1&ndl=1):\r\n\r\n";
		for (auto i : gamesList) {
			emailContent += i.title + "\r\n";
			emailContent += i.url + "\r\n";
			emailContent += "\r\n\r\n";
		}
	}
	return emailContent.c_str();
}


struct upload_status {
	
	size_t bytes_read = 0;
	const char *payload_text;
};

static size_t read_callback(char *inputBuffer, size_t size, size_t nmemb, void *voidPtr) {
	upload_status *uploadHelper = (upload_status *)voidPtr;
	const char *data;
	size_t spaceLeft = size * nmemb;
	
	if (size == 0 || nmemb == 0 || spaceLeft < 1) {
		return 0;
	}

	data = &uploadHelper->payload_text[uploadHelper->bytes_read];
	if (data) {
		size_t len = strlen(data);
		if (spaceLeft < len) {
			len = spaceLeft;
		}
		memcpy(inputBuffer, data, len);
		uploadHelper->bytes_read += len;
		return len;
	}
	
	return 0;
}

//need to check each curlopt setting b4 setting string, some might need the buffer until finished
bool sendEmail(std::vector<game>& gamesList) {
	bool wasSuccessful = 1;
	
	upload_status uploadHelper;
	uploadHelper.bytes_read = 0;
	uploadHelper.payload_text = composeEmail(gamesList);
	
	CURL *emailHandle = curl_easy_init();
	
	curl_easy_setopt(emailHandle, CURLOPT_URL, "smtp://smtp.gmail.com:587"); //set smtp server, port 587
	
	curl_easy_setopt(emailHandle, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);//require ssl for all communication
	
	curl_easy_setopt(emailHandle, CURLOPT_USERNAME, "steamfree2keep@gmail.com");
	curl_easy_setopt(emailHandle, CURLOPT_PASSWORD, "password redacted"); //obviously hardcoding this is not optimal. this will be fixed at some point in the future
	
	curl_easy_setopt(emailHandle, CURLOPT_MAIL_FROM, "<steamfree2keep@gmail.com>");
	struct curl_slist *recipients = NULL;
	recipients = curl_slist_append(recipients, "epiccryingmangos@gmail.com");//i wanna put a mailing list in here
	curl_easy_setopt(emailHandle, CURLOPT_MAIL_RCPT, recipients); 				 //stored in a config file like "notif_list.txt"
	
	curl_easy_setopt(emailHandle, CURLOPT_READFUNCTION, read_callback);
	curl_easy_setopt(emailHandle, CURLOPT_READDATA, &uploadHelper);
	curl_easy_setopt(emailHandle, CURLOPT_UPLOAD, 1);
	
	CURLcode res = curl_easy_perform(emailHandle);
	if (res != CURLE_OK) {
		std::cout << "Email not sent: curl_easy_perform() failed.\n";
		std::cout << curl_easy_strerror(res) << "\n";
		wasSuccessful = 0;
	}
	
	curl_slist_free_all(recipients);
	curl_easy_cleanup(emailHandle);
	
	return wasSuccessful;
}
