SOURCES = PLCS.cpp
OBJECTS = $(SOURCES:.c=.o)
EXE = PLCS

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $< -pthread

%.o: %.cpp
	$(CXX) -c -o $@ $<
