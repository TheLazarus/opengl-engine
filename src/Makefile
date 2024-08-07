CC = g++
OBJECTS = main.o glad.o Shader.o
LIBS = -lglfw3 -lgdi32


game: ${OBJECTS}
	${CC} -g ${OBJECTS} -o app -L../lib ${LIBS}
	del ${OBJECTS}

Shader.o: classes/Shader.cpp
	${CC} -g -c -I../include classes/Shader.cpp

main.o: main.cpp
	${CC} -g -c -I../include main.cpp

glad.o: glad.c
	${CC} -g -c -I../include glad.c
