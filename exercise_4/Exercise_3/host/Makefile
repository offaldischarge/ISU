SOURCES = mutexvector.cpp ScopedLocker.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = riaamutex

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $^ -pthread

%.o: %.cpp
	$(CXX) -c -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS)
