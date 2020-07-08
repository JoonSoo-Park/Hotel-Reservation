GCC = g++
CXXFLAGS = -w -g -std=c++14
OBJECTS = constants.o Reservation.o room.o hotel.o main.o
PLOG = -I plog/include

TARGET = main

$(TARGET) : $(OBJECTS)
	$(GCC) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(PLOG)

Reservation.o: constants.h
	$(GCC) $(CXXFLAGS) -c $*.cpp $(PLOG)

room.o: constants.h
	$(GCC) $(CXXFLAGS) -c $*.cpp $(PLOG)

hotel.o: room.h handle.h
	$(GCC) $(CXXFLAGS) -c $*.cpp $(PLOG)

main.o: hotel.h Menu.h
	$(GCC) $(CXXFLAGS) -c $*.cpp $(PLOG)

clean:
	rm $(OBJECTS) $(TARGET) Log.txt