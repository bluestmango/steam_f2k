CXX = g++
CXXFLAGS = -Wall -o2
LIBS = -lcurl

SOURCES := $(wildcard source/*cpp)
OBJECTS := $(SOURCES:.cpp=.o)


steamf2k.exe: $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)
	
%.o: %.cpp
	$(CXX) $< -c $@

.PHONY: clean
clean:
	rm -f steamf2k.exe
	rm -f $(OBJECTS)