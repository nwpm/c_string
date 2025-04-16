TARGET = tests
OBJS = c_string.o tests.o

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

