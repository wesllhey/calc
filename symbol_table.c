
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "symbol_table.h"

symbol_table_t symbol_table;

void symbol_table_init()
{
    symbol_table.size = 0;
    symbol_table.capacity = SYMBOL_TABLE_DEFAULT_DATA_CAPACITY_SIZE;
    symbol_table.data = (symbol_table_data_t **)calloc(SYMBOL_TABLE_DEFAULT_DATA_CAPACITY_SIZE,
                                                            sizeof(symbol_table_data_t));   

    // default functions  
    symbol_table_add_symbol(symbol_table_new_symbol("sqrt", 0, sqrt));
    symbol_table_add_symbol(symbol_table_new_symbol("log2", 0, log2));      
}

void symbol_table_add_symbol(symbol_table_data_t *symbol)
{
    if (symbol_table.size >= symbol_table.capacity) {
        symbol_table_data_t **new_data = (symbol_table_data_t **)
            realloc(symbol_table.data, (symbol_table.capacity <<= 1) * sizeof(symbol_table_data_t));

        if (new_data)
            symbol_table.data = new_data;
    }

    symbol_table.data[symbol_table.size++] = symbol;
}

symbol_table_data_t *symbol_table_new_symbol(
    char *name,
    double value,
    double (*func_ptr)(double))
{
    symbol_table_data_t *new_symbol = (symbol_table_data_t *)malloc(sizeof(symbol_table_data_t));

    new_symbol->value = value;
    new_symbol->name = strdup(name);
    new_symbol->func_ptr = func_ptr;

    return new_symbol;
}

symbol_table_data_t *symbol_table_retrieve_data_by_name(
    char *name)
{
    for (unsigned i = 0; i < symbol_table.size; i++) {
        if (symbol_table.data[i]->name && !strcmp(symbol_table.data[i]->name, name)) {
            return symbol_table.data[i];
        }
    }

    symbol_table_data_t *new_symbol = symbol_table_new_symbol(name, 0, NULL);
    symbol_table_add_symbol(new_symbol);

    return new_symbol;
}

void symbol_table_free()
{
    for (unsigned i = 0; i < symbol_table.size; i++) {
        free(symbol_table.data[i]);
        symbol_table.data[i] = NULL;
    }

    free(symbol_table.data);
    symbol_table.data = NULL;
}
