CC = gcc
CFLAGS = -Wall
OBJECTS = main.o lexer.o token.o parser.o
TARGET =  main

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

lexer.o: lexer/src/lexer.c lexer/include/lexer.h
	$(CC) $(CFLAGS) -c lexer/src/lexer.c -o lexer.o

token.o: lexer/src/token.c lexer/include/token.h
	$(CC) $(CFLAGS) -c lexer/src/token.c -o token.o
	
parser.o: parser/src/parser.c parser/include/parser.h
	$(CC) $(CFLAGS) -c parser/src/parser.c -o parser.o

clean:
	rm *.o $(TARGET) 
