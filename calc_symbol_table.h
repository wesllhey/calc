/*  Symbol Table tends to be hash table data structre in order to improve more perfomance, O(1) to find elements.
    In this calc, I simply build a dynamic array data structure, because it's more simple and fast to develop. 
*/
#ifndef CALC_SYMBOL_TABLE_H
#define CALC_SYMBOL_TABLE_H

#define CALC_SYMBOL_TABLE_DEFAULT_DATA_CAPACITY_SIZE 1 << 5

typedef struct calc_symbol_table_data_t {
    char *name;
    double value;
    double (*func_ptr)(double);
} calc_symbol_table_data_t;

typedef struct calc_symbol_table_t {
    unsigned capacity;
    unsigned size;
    struct calc_symbol_table_data_t **data;
} calc_symbol_table_t;

extern void calc_symbol_table_init();

extern void calc_symbol_table_add_symbol(
    calc_symbol_table_data_t *symbol);

extern calc_symbol_table_data_t *calc_symbol_table_new_symbol(
    char *name,
    double value,
    double (*func_ptr)(double)
);

extern calc_symbol_table_data_t *calc_symbol_table_retrieve_data_by_name(
    char *name);

extern void calc_symbol_table_free();

#endif