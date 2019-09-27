SOURCES = 1_1.c
OBJECTS = $(SOURCES:.c=.o)
EXE = hellothread

$(EXE): $(OBJECTS)
	$(CC) -o $@ $< -pthread

%.o: %.cpp
	$(CC) -c -o $@ $<
