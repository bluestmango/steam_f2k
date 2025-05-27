CXX = g++
CXXFLAGS = -Wall -o2 -I include/
LIBS = -lcurl

SOURCES := $(wildcard source/*.cpp)
OBJECTS := $(patsubst source/%.cpp,build/%.o,$(SOURCES))

#debug block only, remove in prod
all: steamf2k.exe
	@echo Reminder to silence make commands in prod

steamf2k.exe: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)
	
build/%.o: source/%.cpp
	-mkdir build
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f steamf2k.exe
	rm -rf build
	rm -f $(wildcard *.o)
#just to clean up any rogue objects

showobj:
	echo $(OBJECTS)
#also remove that in prod