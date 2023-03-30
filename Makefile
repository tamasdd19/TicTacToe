clean:
	-rm main

all: clean
	g++ -o main.exe src/main.cpp src/TicTacToe.cpp

run: all
	main.exe

