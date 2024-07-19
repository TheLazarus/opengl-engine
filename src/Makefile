game: main.o glad.o
	g++ -g glad.o main.o -o app -L../lib -lglfw3 -lgdi32 -lopengl32
	del glad.o main.o


main.o: main.cpp
	g++ -g -c -I../include main.cpp

glad.o: glad.c
	g++ -g -c -I../include glad.c