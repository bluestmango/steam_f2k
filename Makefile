scraper.exe: scraper.o
	@g++ scraper.o -o scraper.exe
	
scraper.o: scraper.cpp
	@g++ -c scraper.cpp
	
clean:
	rm -f scraper.exe
	rm -f scraper.o