CC = g++
OBJECTS = main.o glad.o Shader.o VBO.o VAO.o EBO.o Texture.o stb_image.o
LIBS = -lglfw3 -lgdi32
LIB_FLAGS = -L../lib
INCLUDE_FLAGS = -I../include


game: ${OBJECTS}
	${CC} -g ${OBJECTS} -o app ${LIB_FLAGS} ${LIBS}
	del ${OBJECTS}

Shader.o: Shader.cpp
	${CC} -g -c ${INCLUDE_FLAGS} Shader.cpp

VBO.o: VBO.cpp
	${CC} -g -c ${INCLUDE_FLAGS} VBO.cpp

VAO.o: VAO.cpp
	${CC} -g -c ${INCLUDE_FLAGS} VAO.cpp

EBO.o: EBO.cpp
	${CC} -g -c ${INCLUDE_FLAGS} EBO.cpp

Texture.o: Texture.cpp
	${CC} -g -c ${INCLUDE_FLAGS} Texture.cpp

stb_image.o: stb_image.cpp
	${CC} -g -c ${INCLUDE_FLAGS} stb_image.cpp

main.o: main.cpp
	${CC} -g -c ${INCLUDE_FLAGS} main.cpp

glad.o: glad.c
	${CC} -g -c ${INCLUDE_FLAGS} glad.c
