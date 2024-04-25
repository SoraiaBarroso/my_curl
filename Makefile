CC = gcc
CFLAGS = -Wall -Wextra -Werror
SOURCE = my_curl.c helper_fun.c socket.c my_curl.h
TARGET = my_curl

all : $(TARGET)

$(TARGET) : $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all