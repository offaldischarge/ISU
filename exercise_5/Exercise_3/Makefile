SOURCES = PLCS.cpp
OBJECTS = $(SOURCES:.c=.o)
EXE = PLCS_extended

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $< -pthread

%.o: %.cpp
	$(CXX) -c -o $@ $<
