CC = /usr/bin/gcc

SRCS = ./src/display.c \
	   ./src/mandel.c \
	   ./src/complex.c \
	   ./src/linear.c 

OBS  = ./src/display.o \
	   ./src/mandel.o \
	   ./src/complex.o \
	   ./src/linear.o

INC = ./src/structs.h

TARGET = mandel


CFLAGS = -I$(INC) -pedantic -Wall -pedantic-errors \
		 -Wunused-command-line-argument -Wimplicit-function-declaration 

CPPFLAGS = -I/opt/X11/include -L/usr/X11R6/lib

LIBS = -lX11 #-DUSE_SYSCTL_HW_MEMSIZE

$(TARGET): $(OBJS)
	$(CC) -g -o $(TARGET) $(SRCS) $(LIBS) $(CFLAGS) $(CPPFLAGS) $(OBJS) 
%.o: %.c
	$(CC) -g -c $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LIBS)


.PHONY: clean
clean:
	@rm -rf $(OBJS) xmand.o $(TARGET) *.dSYM
