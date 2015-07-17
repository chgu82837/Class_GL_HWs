# This makefile is for OSX
# You need to install `glfw3` and `glew`. I install them by `Homebrew` with the following command:
# brew install glfw3
# brew install glew

ProjName = GL_HW1_4101056017

# OBJS specifies which files to compile as part of the project
OBJS = $(ProjName)/$(ProjName).cpp

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = -framework OpenGL -framework GLUT -lglfw3

# -lglew not working
# LINKER_FLAGS = -framework OpenGL -framework GLUT -lglfw3 -lglew

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = OSX_Build/$(ProjName)

OBJ_FOLDER = OSX_Build

#This is the target that compiles our executable
all : $(OBJS)
	mkdir -p $(OBJ_FOLDER)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
