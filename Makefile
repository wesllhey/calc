FLEX = flex
BISON = bison

CC = gcc -Wall -g

all: calc

calc: symbol_table.o parser.tab.o lexer.lex.o
	$(CC) -o $@ $^ -ly -ll -lm
	
symbol_table.o: symbol_table.c
	$(CC) -c $^

lexer.lex.o: lexer.lex.c

parser.tab.o: parser.tab.c

parser.tab.c: parser.y
	$(BISON) -d $^

lexer.lex.c: lexer.l
	$(FLEX) -o $@ $^

clean:
	rm *.o calc

