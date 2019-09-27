SOURCES = semaphorevector.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = vectorsemaphore

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $< -pthread

%.o: %.cpp
	$(CXX) -c -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS)
