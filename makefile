default: build
	./prism

build:
	g++ -Iinclude -O3 -std=c++11 main.cpp lib/prism_models.cpp lib/prism_linalg.cpp lib/prism_raycast.cpp -o prism

clean:
	rm -rf prism