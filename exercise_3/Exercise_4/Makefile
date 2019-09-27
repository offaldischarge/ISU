SOURCES = 4.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = writerthreads

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $< -pthread

%.o: %.cpp
	$(CXX) -c -o $@ $<
