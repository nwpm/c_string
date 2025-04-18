TARGET = tests
OBJS = c_string.o tests.o

CC = gcc
DCFLAGS = -g -O0 -Wall -Wextra -std=c99
CFLAGS = -Wall -Wextra -std=c99 

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(DCFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

