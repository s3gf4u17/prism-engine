default:
	g++ main.cpp
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