CXX = g++

TARGET = SMAND

#CFLAGS = -I/usr/X11R6/include #-I/usr/X11R6/include/X11
#LFLAGS =  -L/usr/X11R6/lib -X11R6 -lX11

CFLAGS = -Wall
LFLAGS = -Wno-deprecated-declarations -L/System/Library/Frameworks -framework GLUT -framework OpenGL 

XMAND: smandel.o
	$(CXX) $(CFLAGS) $(LFLAGS) smandel.o
smandel.o: smandel.cpp 
	$(CXX) $(CFLAGS) $(LFLAGS) -c smandel.cpp

.PHONY: clean
clean: 
	rm *.o *.out