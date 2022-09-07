build:
	mkdir build
	gcc ./src/*.c -o build/game.out

clean:
	rm -r build

play:
	./build/game.out

debug:
	gdb ./build/game.out
	
valgrind-debug:
	valgrind ./build/game.out
