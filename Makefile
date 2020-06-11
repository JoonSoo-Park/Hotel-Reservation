GCC = g++
CXXFLAGS = -w
OBJECTS = room.o hotel.o main.o

TARGET = main

$(TARGET) : $(OBJECTS)
	$(GCC) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

room.o: constants.h

hotel.o: room.h 

main.o: hotel.o

clean:
	rm $(OBJECTS) $(TARGET)