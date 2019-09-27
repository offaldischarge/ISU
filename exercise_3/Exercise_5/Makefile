SOURCES = 5_v2.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:.cpp=.d)
CXXFLAGS = -I.
EXE = writerthreadstweaked

$(EXE): $(DEPS) $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) -pthread

%.o: %.cpp
	$(CXX) -c -o $@ $<

%.d: %.cpp
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@
	$(CXX) -MT $@ -MM $(CXXFLAGS) $< >> $@

clean:
	rm -f $(EXE) $(DEPS) $(OBJECTS)
