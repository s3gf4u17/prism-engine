default:
	g++ RenderEngine.c
	./a.out

java:
	@javac RenderEngine.java
	@clear && java RenderEngine