CXX = g++
CXXFLAGS = -Wall -o2 -I include/
LIBS = -lcurl

SOURCES := $(wildcard source/*.cpp)
OBJECTS := $(patsubst source/%.cpp,build/%.o,$(SOURCES))

#debug block only, remove in prod
all: steamf2k
	@echo Reminder to silence make commands in prod

steamf2k: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)
	
build/%.o: source/%.cpp
	-mkdir build
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f steamf2k.exe steamf2k
	rm -f steam_source.txt
	rm -rf build
	rm -f $(wildcard *.o)
#just to clean up any rogue objects

debug: $(OBJECTS)
	$(CXX) $(CXXFLAGS) build/main.o build/parse.o -o parsetest.exe
#remove this too