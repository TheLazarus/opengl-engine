CC = g++
OBJECTS = main.o glad.o Shader.o VBO.o VAO.o EBO.o
LIBS = -lglfw3 -lgdi32


game: ${OBJECTS}
	${CC} -g ${OBJECTS} -o app -L../lib ${LIBS}
	del ${OBJECTS}

Shader.o: Shader.cpp
	${CC} -g -c -I../include Shader.cpp

VBO.o: VBO.cpp
	${CC} -g -c -I../include VBO.cpp

VAO.o: VAO.cpp
	${CC} -g -c -I../include VAO.cpp

EBO.o: EBO.cpp
	${CC} -g -c -I../include EBO.cpp

main.o: main.cpp
	${CC} -g -c -I../include main.cpp

glad.o: glad.c
	${CC} -g -c -I../include glad.c
