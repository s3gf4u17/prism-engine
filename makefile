ppm-encoder:
	@g++ -Iinclude -O3 kernel.cpp -o kernel
	@./kernel > render.ppm
	@rm -f render