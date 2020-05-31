/*  Symbol Table tends to be hash table data structre in order to improve more perfomance, O(1) to find elements.
    In this calc, I simply build a dynamic array data structure, because it's more simple and fast to develop. 
*/
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define SYMBOL_TABLE_DEFAULT_DATA_CAPACITY_SIZE 1 << 5

typedef struct symbol_table_data_t {
    char *name;
    double value;
    double (*func_ptr)(double);
} symbol_table_data_t;

typedef struct symbol_table_t {
    unsigned capacity;
    unsigned size;
    struct symbol_table_data_t **data;
} symbol_table_t;

extern void symbol_table_init();

extern void symbol_table_add_symbol(
    symbol_table_data_t *symbol);

extern symbol_table_data_t *symbol_table_new_symbol(
    char *name,
    double value,
    double (*func_ptr)(double)
);

extern symbol_table_data_t *symbol_table_retrieve_data_by_name(
    char *name);

extern void symbol_table_free();

#endif