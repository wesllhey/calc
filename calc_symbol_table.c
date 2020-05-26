
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "calc_symbol_table.h"

calc_symbol_table_t symbol_table;

void calc_symbol_table_init()
{
    symbol_table.size = 0;
    symbol_table.capacity = CALC_SYMBOL_TABLE_DEFAULT_DATA_CAPACITY_SIZE;
    symbol_table.data = (calc_symbol_table_data_t **)calloc(CALC_SYMBOL_TABLE_DEFAULT_DATA_CAPACITY_SIZE,
                                                            sizeof(calc_symbol_table_data_t));   

    // default functions  
    calc_symbol_table_add_symbol(calc_symbol_table_new_symbol("sqrt", 0, sqrt));
    calc_symbol_table_add_symbol(calc_symbol_table_new_symbol("log2", 0, log2));      
}

void calc_symbol_table_add_symbol(calc_symbol_table_data_t *symbol)
{
    if (symbol_table.size >= symbol_table.capacity) {
        calc_symbol_table_data_t **new_data = (calc_symbol_table_data_t **)
            realloc(symbol_table.data, (symbol_table.capacity <<= 1) * sizeof(calc_symbol_table_data_t));

        if (new_data)
            symbol_table.data = new_data;
    }

    symbol_table.data[symbol_table.size++] = symbol;
}

calc_symbol_table_data_t *calc_symbol_table_new_symbol(
    char *name,
    double value,
    double (*func_ptr)(double))
{
    calc_symbol_table_data_t *new_symbol = (calc_symbol_table_data_t *)malloc(sizeof(calc_symbol_table_data_t));

    new_symbol->value = value;
    new_symbol->name = strdup(name);
    new_symbol->func_ptr = func_ptr;

    return new_symbol;
}

calc_symbol_table_data_t *calc_symbol_table_retrieve_data_by_name(
    char *name)
{
    for (unsigned i = 0; i < symbol_table.size; i++) {
        if (symbol_table.data[i]->name && !strcmp(symbol_table.data[i]->name, name)) {
            return symbol_table.data[i];
        }
    }

    calc_symbol_table_data_t *new_symbol = calc_symbol_table_new_symbol(name, 0, NULL);
    calc_symbol_table_add_symbol(new_symbol);

    return new_symbol;
}

void calc_symbol_table_free()
{
    for (unsigned i = 0; i < symbol_table.size; i++) {
        free(symbol_table.data[i]);
        symbol_table.data[i] = NULL;
    }

    free(symbol_table.data);
    symbol_table.data = NULL;
}
