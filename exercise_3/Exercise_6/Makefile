SOURCES = 6_v2.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXE = writerthreadstarget
COMP = arm-rpizw-g++

$(EXE): $(OBJECTS)
	$(COMP) -o $@ $< -pthread
	scp writerthreadstarget root@10.9.8.2:

%.o: %.cpp
	$(COMP) -c -o $@ $<
