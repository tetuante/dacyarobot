#!/usr/bin/make
TARGET=robot
SOURCES=main.c fsm.c colaEventos.c distFrontal.c distLateral.c mcp3008.c controlServo.c motores.c

OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
MY_INCLUDES=.
HEADERS=$(wildcard $(MY_INCLUDES)/*.h)
OS=$(shell uname)
LDFLAGS=-lpthread -lwiringPi
#CFLAGS=-g -Wall 
CFLAGS=-g -Wall 

all: $(TARGET)
	
$(TARGET): $(OBJECTS)
	gcc  -o  $(TARGET) $(OBJECTS) $(LDFLAGS)

.SUFFIXES:      .o .cpp .h

.h:

.c.o: $(HEADERS)
	gcc  $(CFLAGS)  -I$(MY_INCLUDES) -c $< -o $@  -Wall
	
clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -f  *~
	



