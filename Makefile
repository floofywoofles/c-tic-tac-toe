build:
	mkdir build
	gcc -g ./src/* -o build/game

clean:
	rm -r build

play:
	./build/game

debug:
	gdb ./build/game
	
valgrind-debug:
	valgrind ./build/game

push:
	git push upstream --force
	git push origin --force