EXEC = a.out
CC = g++
OBJ = lexer.o main.o myparser.o
CFLAGS= -g -Wall -Wextra
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm

lexer.o : lexer.cpp lexer.h
	$(CC) -c lexer.cpp

main.o : main.cpp lexer.h
	$(CC) -c main.cpp

parser.o:myparser.cpp myparser.h
	$(CC) -c myparser.cpp

clean:
	rm -f $(EXEC) lexer.o main.o myparser.o
