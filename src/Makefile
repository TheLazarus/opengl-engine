CC=g++
LIB_DIR = ../lib
INCLUDE_DIR = ../include
LIBS = -lglfw3 -lgdi32

APP_OBJECTS = main.o glad.o shaderUtils.o

.PHONY: all clean

all: app

app: ${APP_OBJECTS}
	$(CC) -g ${APP_OBJECTS} -o app -L${LIB_DIR} ${LIBS}
	del ${APP_OBJECTS}


main.o: main.cpp
	$(CC) -g -c -I${INCLUDE_DIR} main.cpp

shaderUtils.o: shaderUtils.cpp
	$(CC) -g -c -I${INCLUDE_DIR} shaderUtils.cpp

glad.o: glad.c
	$(CC) -g -c -I${INCLUDE_DIR} glad.c

clean:
	del ${APP_OBJECTS} app