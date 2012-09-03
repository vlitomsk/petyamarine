LIBS=-lSDL -lSDL_image -lSDL_gfx

all: clean
	g++ -c ./Tape.cpp -o ./Tape.o -O3
	g++ -c ./main.cpp -o ./main.o -O3
	g++ -c ./GameObject.cpp -o ./GameObject.o -O3
	g++ -c ./geometry.cpp -o ./geometry.o -O3

	g++ -o ./main ./*.o $(LIBS) 

run: all
	./main

clean:
	rm ./*.o -f
	rm ./main -f
