.PHONY: all

prog_name = routh

all: build

build:
	g++ -std=c++17 main.cpp -o $(prog_name)

clean:
	rm $(prog_name)
