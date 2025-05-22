CXX = g++
CXXFLAGS = -Wall -o2
LIBS = -lcurl

SOURCES := $(wildcard source/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)


steamf2k.exe: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)
	
%.o: %.cpp
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -f steamf2k.exe
	rm -f $(OBJECTS)
	rm -f $(wildcard *.o)
#just to clean up any rogue objects

showobj:
	echo $(OBJECTS)