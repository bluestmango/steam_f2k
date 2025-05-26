CXX = g++
CXXFLAGS = -Wall -o2
LIBS = -lcurl

SOURCES := $(wildcard source/*.cpp)
OBJECTS := $(patsubst source/%.cpp,build/%.o,$(SOURCES))


steamf2k.exe: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)
	
build/%.o: source/%.cpp
	-mkdir build
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -f steamf2k.exe
	rm -rf build
	rm -f $(wildcard *.o)
#just to clean up any rogue objects

showobj:
	echo $(OBJECTS)