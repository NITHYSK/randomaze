CC	= gcc
CFLAGS	= --std=c11
SRCS	= $(wildcard ./*.c)
OBJS	= $(SRCS:.c=.o)
TARGET	= randomaze.out

$(TARGET)	: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

$(OBJS) : stdafx.h

test	: $(TARGET)
	./$(TARGET) 21 71

clean	:
	rm ./*.o ./$(TARGET)

.PHONY	: test clean


