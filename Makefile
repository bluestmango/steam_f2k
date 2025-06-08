CXX = g++
CXXFLAGS = -Wall -o2 -I include/
LIBS = -lcurl

SOURCES := $(wildcard source/*.cpp)
OBJECTS := $(patsubst source/%.cpp,build/%.o,$(SOURCES))

ifeq ($(OS),Windows_NT)
	ICON := build/icon.res
endif
#debug block only, remove in prod
all:steamf2k
	@echo Reminder to silence make commands in prod

steamf2k: $(OBJECTS)
	$(CXX) $^ $(ICON) -o $@ $(LIBS)
	
build/%.o: source/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f steamf2k.exe steamf2k
	rm -f $(wildcard build/*.o)

debug: $(OBJECTS)
	$(CXX) $(CXXFLAGS) build/notification.o -o notiftest.exe $(LIBS)
#remove this too
