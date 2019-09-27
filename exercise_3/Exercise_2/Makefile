SOURCES = 2.c
OBJECTS = $(SOURCES:.c=.o)
EXE = twothreads

$(EXE): $(OBJECTS)
	$(CC) -o $@ $< -pthread

%.o: %.cpp
	$(CC) -c -o $@ $<
