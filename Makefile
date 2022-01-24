CC = g++
CPU_SOURCES = $(wildcard src/*.cpp)
CPU_OBJECTS = $(CPU_SOURCES:.cpp=.o)

all: $(CPU_OBJECTS)
	$(CC) -o channel.bin $(CPU_OBJECTS)

$(CPU_OBJECTS): src/%.o: src/%.cpp
	$(CC) -c $(SIZE) $< -o $@

clean:
	rm src/*.o channel.bin
