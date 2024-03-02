all:
	g++ -I ./include -L ./lib -o ./bin/main ./src/*.cpp -lmingw32 -lSDL2main -lSDL2

clean:
	-del bin