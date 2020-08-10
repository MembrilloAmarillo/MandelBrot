CC = /usr/bin/g++

OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRC = 	$(SRC_DIR)main.cpp \
		$(SRC_DIR)linear.cpp \
	   	$(SRC_DIR)display.cpp

OBJ  = $(OBJ_DIR)main.o \
	   $(OBJ_DIR)linear.o \
	   $(OBJ_DIR)display.o

INC = $(SRC_DIR)structs.h \
	  $(SRC_DIR)log.h \
	  $(SRC_DIR)display.h \
	  $(SRC_DIR)log.h
			
TARGET = mandel

WARNINGS = 	-pedantic -Wall -pedantic-errors \
		 	-Wunused-command-line-argument -Wimplicit-function-declaration \
		 	-Wdeprecated 

CFLAGS = -I$(INC) -02 $(WARNINGS) -g

CPPFLAGS = -lSDL2main -lSDL2

#LIBS = -lX11 -DUSE_SYSCTL_HW_MEMSIZE

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) -c -MD $(CFLAGS) $(CPPFLAGS) $< -o $@

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(OBJ) 

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) xmand.o $(TARGET) *.dSYM

# NO TOCAR ESTAS LINEAS PORFA PLIS #

$(OBJ_DIR)main.o    : main.cpp linear.cpp display.cpp display.h
$(OBJ_DIR)linear.o  : linear.cpp display.cpp display.h
$(OBJ_DIR)display.o : display.cpp linear.cpp display.h log.h
