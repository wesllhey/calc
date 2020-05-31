%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "symbol_table.h"

extern void yyerror(char *s);
extern int yylex();
%}

%union {
    double d_value;
    symbol_table_data_t *symbol;
}

%token PLUS MINUS DIV MULT OPEN_PARENTHESES CLOSE_PARENTHESES EQUALS EOL

%token <d_value> NUMBER 
%type <d_value> expression
%type <d_value> factor
%type <d_value> term

%token <symbol> NAME 

%left '+' '-'
%left '*' '/'

%nonassoc UNIMUS

%%
statement_list:     
    { printf("> "); } 
    |               
    statement_list statement EOL
    |               
    statement_list EOL { printf("> "); }
    ;

statement:          
    NAME EQUALS expression { $1->value = $3; printf("> "); }
    |               
    expression { printf("> %g\n> ", $1); }
    ;

expression:         
    factor
    |               
    expression PLUS expression { $$ = $1 + $3; }   
    |               
    expression MINUS expression { $$ = $1 - $3; }
    |               
    MINUS expression %prec UNIMUS { $$ = -$2; }
    ;

factor:             
    term
    |               
    factor MULT factor { $$ = $1 * $3; } 
    |               
    factor DIV factor { if ($3 == 0.0) yyerror("divid by zero"); else $$ = $1 / $3; }
    ;

term:               
    NUMBER
    |               
    NAME    { $$ = $1->value; }
    |               
    OPEN_PARENTHESES expression CLOSE_PARENTHESES { $$ = $2; }
    |               
    NAME OPEN_PARENTHESES expression CLOSE_PARENTHESES 
    {     
        if ($1->func_ptr) {
            $$ = ($1->func_ptr)($3);
        } else {
            printf("%s not a function\n", $1->name);
            $$ = 0.0;
        }
    }
    ;
%%

void yyerror(
    char *s)
{
    fprintf(stderr, "%s\n", s);
}

int main(void)
{  
    symbol_table_init();
    yyparse();
    symbol_table_free();
}