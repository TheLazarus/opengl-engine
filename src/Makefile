MAKEFLAGS += --silent

CC = g++
CFLAGS = -Wall -Wextra -pedantic
LIBS = -lglfw3 -lgdi32
LIB_DIRS = -L../lib
INCLUDE_DIRS = -I../include
APP_NAME = app


# Sources and Objects
CPP_SOURCES = main.cpp ShaderProgram.cpp VBO.cpp VAO.cpp EBO.cpp Texture.cpp PerspectiveMatrix.cpp TranslationMatrix.cpp stb_image.cpp
C_SOURCES = glad.c

CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)
C_OBJECTS = $(C_SOURCES:.c=.o)

all: $(APP_NAME)

$(APP_NAME): $(CPP_OBJECTS) $(C_OBJECTS)
	echo Compiling and Linking App...
	$(CC) $(CFLAGS) $(CPP_OBJECTS) $(C_OBJECTS) -o $(APP_NAME) $(LIB_DIRS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $(INCLUDE_DIRS) $< -o $@
	echo (C++) -- $< compiled successfully!
	
%.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDE_DIRS) $< 
	echo (C) -- $< compiled successfully!
	
clean: 
	del $(APP_NAME) $(CPP_OBJECTS) $(C_OBJECTS)
	echo Cleanup Successful

.PHONY: all clean
