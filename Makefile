CC = /usr/bin/g++

SRCS = ./src/main.cpp \
	   ./src/linear.cpp \
	   ./src/display.cpp

OBS  = ./src/main.o \
	   ./src/linear.o \
	   ./src/display.o

INC = ./src/structs.h \
	  ./src/log.h

TARGET = mandel


CFLAGS = -std=c++11 -I$(INC) -pedantic -Wall -pedantic-errors \
		 -Wunused-command-line-argument -Wimplicit-function-declaration \
		 -Wdeprecated

CPPFLAGS = -lSDL2main -lSDL2

LIBS = #-lX11 #-DUSE_SYSCTL_HW_MEMSIZE

$(TARGET): $(OBJS)
	$(CC) -g -o $(TARGET) $(SRCS) $(LIBS) $(CFLAGS) $(CPPFLAGS) $(OBJS) 
%.o: %.c
	$(CC) -g -c $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LIBS)


.PHONY: clean
clean:
	@rm -rf $(OBJS) xmand.o $(TARGET) *.dSYM
