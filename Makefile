CXX = clang++
SDL = -F/Library/Frameworks -framework SDL2 -framework SDL2_image
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -Wall -c -std=c++11 -F/Library/Frameworks/
LDFLAGS = $(SDL)
EXE = game

all: $(EXE)

$(EXE): src/main.o
	$(CXX) $(LDFLAGS) $< -o bin/$@

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $< -o src/$@clean:
	rm src/*.o && rm bin/$(EXE)

clean:
	rm src/*.o && rm bin/$(EXE)

