CC = /usr/bin/g++

SRCS = ./src/main.C \

OBS  = ./src/main.o \

#INC = ./src/structs.h

TARGET = mandel


CFLAGS = -I$(INC) -pedantic -Wall -pedantic-errors \
		 -Wunused-command-line-argument -Wimplicit-function-declaration 

CPPFLAGS = -lSDL2main -lSDL2

LIBS = #-lX11 #-DUSE_SYSCTL_HW_MEMSIZE

$(TARGET): $(OBJS)
	$(CC) -g -o $(TARGET) $(SRCS) $(LIBS) $(CFLAGS) $(CPPFLAGS) $(OBJS) 
%.o: %.c
	$(CC) -g -c $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LIBS)


.PHONY: clean
clean:
	@rm -rf $(OBJS) xmand.o $(TARGET) *.dSYM
