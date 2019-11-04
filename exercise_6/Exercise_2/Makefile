SOURCES = Point.cpp MsgQueue.cpp Message.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = points

$(EXE): $(OBJECTS)
	$(CXX)  -o $@ $^ -lpthread

%.o: %.cpp
	$(CXX) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJECTS)
