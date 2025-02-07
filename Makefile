FLAGS=-Wall -Werror -lm -g

7color : o/GameState.o
	gcc $(FLAGS) o/GameState.o -o 7color

o/GameState.o: head/GameState.h src/GameState.c
	gcc $(FLAGS) -c src/GameState.c -o o/GameState.o
