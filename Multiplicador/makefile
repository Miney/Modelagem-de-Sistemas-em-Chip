CC = g++
CFLAGS = -g -Wall # flags when *compiling*
LFLAGS = -g -Wall # flags when *linking*
INC = -I/usr/local/systemc-2.3.0/include
LIBS = -lm -L/usr/local/systemc-2.3.0/lib-linux -lsystemc # math and systemc libraries
SOURCES = multiplicador.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@ $(LIBS) 

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< $(INC) 

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	
	
