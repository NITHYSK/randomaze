CC	= gcc
CFLAGS	= --std=c11
INCLUDE	= ./include
SRC	= ./src
OBJ	= ./obj
TARGET	= ./randomaze.out
STDAFX	= $(INCLUDE)/stdafx.h
SRCS	= $(wildcard $(SRC)/*.c)
OBJS	= $(subst $(SRC),$(OBJ),$(SRCS:.c=.o))

$(TARGET)	: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

$(OBJS)		: $(OBJ)/%.o: $(SRC)/%.c $(STDAFX)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c -o $@ $<

test		: $(TARGET)
	./$(TARGET) 21 51

clean		:
	rm $(OBJS)
	rm $(TARGET)

.PHONY	: test clean


