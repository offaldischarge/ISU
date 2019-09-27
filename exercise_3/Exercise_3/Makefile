SOURCES = 3.c
OBJECTS = $(SOURCES:.c=.o)
EXE = shareddata

$(EXE): $(OBJECTS)
	$(CC) -o $@ $< -pthread

%.o: %.cpp
	$(CC) -c -o $@ $<
