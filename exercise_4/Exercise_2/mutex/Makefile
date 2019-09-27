SOURCES = mutexvector.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = vectormutex

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $< -pthread

%.o: %.cpp
	$(CXX) -c -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS)
