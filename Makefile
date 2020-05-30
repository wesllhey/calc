FLEX = flex
BISON = bison

CC = gcc -Wall -g

all: calc

calc: calc_symbol_table.o calc_parser.tab.o calc_lexer.lex.o
	$(CC) -o $@ $^ -ly -ll -lm
	
calc_symbol_table.o: calc_symbol_table.c
	$(CC) -c $^

calc_lexer.lex.o: calc_lexer.lex.c

calc_parser.tab.o: calc_parser.tab.c

calc_parser.tab.c: calc_parser.y
	$(BISON) -d $^

calc_lexer.lex.c: calc_lexer.l
	$(FLEX) -o $@ $^

clean:
	rm *.o calc

