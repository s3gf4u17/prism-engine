default:
	g++ -std=c++11 main.cpp
	./a.out

test:
	g++ test.cpp -o test
	./test

release:
	@clear
	g++ main.cpp -O3 -o prism
	./prism

conv:
	g++ converter.cpp
	./a.out

use:
	@clear
	./prism

new:
	g++ src/main.c && ./a.out