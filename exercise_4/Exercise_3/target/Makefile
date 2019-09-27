SOURCES = mutexvector.cpp ScopedLocker.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = riaamutex
COMP = arm-rpizw-g++

$(EXE): $(OBJECTS)
	$(COMP) -o $@ $^ -pthread
	scp $(EXE) root@10.9.8.2:

%.o: %.cpp
	$(COMP) -c -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS)
