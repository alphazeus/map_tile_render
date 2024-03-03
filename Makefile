all:
	g++ -I ./include -L ./lib -o main ./src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

clean:
	-del bin