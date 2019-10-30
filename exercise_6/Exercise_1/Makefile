SOURCES = MsgQueue.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = MsgQueue

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $< -pthread

%.o: %.cpp
	$(CXX) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJECTS)
