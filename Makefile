clean:
	-rm main

all: clean
	g++ -o main.exe src/main.cpp

run: all
	main.exe

