# Makefile
CC = gcc
CFLAGS = -Wall
TARGET = TCPEchoServer
SRCS = TCPEchoServer.c HandleTCPClient.c DieWithError.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o
