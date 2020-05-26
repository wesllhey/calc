LEX = lex -I
YACC = yacc

CC = gcc -Wall -g

all: calc

calc: calc_symbol_table.o y.tab.o lex.yy.o
	$(CC) -o $@ $^ -ly -ll -lm
	
calc_symbol_table.o: calc_symbol_table.c
	$(CC) -c $^

lex.yy.o: lex.yy.c y.tab.h

lex.yy.o y.tab.o: calc_symbol_table.h

y.tab.c y.tab.h: calc_parser.y
	$(YACC) -d $^

lex.yy.c: calc_lex.l
	$(LEX) $^

clean:
	rm *.o

