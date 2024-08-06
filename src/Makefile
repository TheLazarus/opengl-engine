CC = g++
OBJECTS = main.o glad.o
LIBS = -lglfw3 -lgdi32


game: ${OBJECTS}
	${CC} -g ${OBJECTS} -o app -L../lib ${LIBS}
	del ${OBJECTS}


main.o: main.cpp
	${CC} -g -c -I../include main.cpp

glad.o: glad.c
	${CC} -g -c -I../include glad.c