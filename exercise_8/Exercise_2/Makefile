SOURCES = main.cpp SmartString.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = smartstring

$(EXE): $(OBJECTS)
	$(CXX)  -o $@ $^

%.o: %.cpp
	$(CXX) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJECTS)
