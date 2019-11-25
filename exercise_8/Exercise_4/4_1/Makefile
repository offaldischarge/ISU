SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = boosttest

$(EXE): $(OBJECTS)
	$(CXX)  -o $@ $^

%.o: %.cpp
	$(CXX) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJECTS)
