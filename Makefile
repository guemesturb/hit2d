CC = g++ -std=c++17 
CPU_SOURCES = $(wildcard src/*.cpp)
CPU_OBJECTS = $(CPU_SOURCES:.cpp=.o)
LIBS = -lfftw3

NX:= $(shell python readconf.py NX)
NY:= $(shell python readconf.py NY)
SIZE = -DNX=${NX} -DNY=${NY}

all: $(CPU_OBJECTS)
	$(CC) -o channel.bin $(CPU_OBJECTS) $(LIBS)

$(CPU_OBJECTS): src/%.o: src/%.cpp
	$(CC) -c $< -o $@ 

clean:
	rm src/*.o channel.bin
