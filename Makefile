build:
	mkdir build
	gcc -g ./src/* -o build/game

clean:
	rm -r build

play:
	./build/game

debug:
	gdb ./build/game