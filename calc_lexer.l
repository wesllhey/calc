%{
#include "calc_symbol_table.h"

#include "calc_parser.tab.h"
%}

%%

exit { calc_symbol_table_free(); exit(0); }

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) { yylval.d_value = atof(yytext); return NUMBER; }
[ \t] ;

[A-Za-z][A-Za-z0-9]* { yylval.symbol = calc_symbol_table_retrieve_data_by_name(yytext); return NAME; }

"=" { return EQUALS; }
"(" { return OPEN_PARENTHESES; }
")" { return CLOSE_PARENTHESES; }
"+" { return PLUS; }  
"-" { return MINUS; } 
"*" { return MULT; } 
"/" { return DIV; }
"$" { return 0; }
\n  { return EOL; }
.   return yytext[0];   
%% 
