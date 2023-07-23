default:
	g++ main.cpp
	./a.out

test:
	g++ test.cpp -o test
	./test

release:
	g++ main.cpp -O3 -o prism
	./prism

conv:
	g++ converter.cpp
	./a.out