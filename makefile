default:
	g++ main.cpp
	./a.out

test:
	g++ test.cpp
	./a.out

release:
	g++ main.cpp -O3 -o prism
	./prism

conv:
	g++ converter.cpp
	./a.out