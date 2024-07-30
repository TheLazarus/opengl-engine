app: main.o glad.o shaderUtils.o
	g++ -g glad.o main.o shaderUtils.o -o app -L../lib -lglfw3 -lgdi32
	del glad.o main.o shaderUtils.o


main.o: main.cpp
	g++ -g -c -I../include main.cpp

shaderUtils.o: shaderUtils.cpp
	g++ -g -c -I../include shaderUtils.cpp

glad.o: glad.c
	g++ -g -c -I../include glad.c