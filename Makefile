GCC = g++
CXXFLAGS = -w -g -std=c++14
OBJECTS = constants.o room.o hotel.o main.o

TARGET = main

$(TARGET) : $(OBJECTS)
	$(GCC) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

room.o: constants.h

hotel.o: room.h handle.h

main.o: hotel.h Menu.h

clean:
	rm $(OBJECTS) $(TARGET)