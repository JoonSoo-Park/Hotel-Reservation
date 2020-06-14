GCC = g++
CXXFLAGS = -w -g
OBJECTS = constants.o room.o hotel.o main.o

TARGET = main

$(TARGET) : $(OBJECTS)
	$(GCC) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

room.o: constants.h

hotel.o: room.h handle.h

main.o: hotel.h

clean:
	rm $(OBJECTS) $(TARGET)