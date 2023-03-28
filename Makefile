clean:
	-rm output/main

all: clean
	clang++ -o main.exe src/main.cpp -std=c++17 -L"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x64" -lUser32

run: all
	main.exe

