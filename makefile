CC = gcc
# -Wall shows warnings
# -Wextra shows more warnings
# -g informations about errors
CFLAGS = -Walls -Wextra -g

TARGET = program.exe

OBJECTS = project2.o functionsbodies.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

project2.o: project2 functionsdeclarations
	$(CC) $(CFLAGS) -c project2 -o project2.o

functionsbodies.o: functionsbodies functionsdeclarations
	$(CC) $(CFLAGS) -c functionsbodies -o functionsbodies.o

clean:
	del $(TARGET) $(OBJECTS)

