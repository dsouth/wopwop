CC = clang
SDL = -Llib/ -lSDL2 -lSDL2_image -lSDL2_ttf
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall -c -Iinclude
LDFLAGS = $(SDL)
EXE = game

all: $(EXE)

$(EXE): src/main.o src/texture.o
	$(CC) $(LDFLAGS) src/main.o src/texture.o -o bin/$@

main.o: src/main.c
	$(CC) $(CFLAGS) $< -o src/$@

texture.o: src/texture.c
	$(CC) $(CFLAGS) $< -o src/$@

clean:
	rm src/*.o && rm bin/$(EXE)

