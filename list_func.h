#ifndef __FUNC_LST__
#define __FUNC_LST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int SIZE_LIST = 10;
const int NULL_ELEM = 0;
const int FREE = -666;

enum functions
{
    END_PROG,
    PRINT,
    DUMP,
    PUSH_AFTER,
    PUSH_IN_HEAD,
    PUSH_IN_BACK,
    DELETE,
    DUMP_IN_FILE
};

struct str_list
{
    int data;
    int next;
    int prev;
};

struct info_list
{
    FILE* dump_file;
    int free;
    struct str_list* list;
};

void list_ctor(struct info_list* lst);
void list_dtor(struct info_list* lst);
bool check_range_of_index(int num);
bool check_free_index(int num);
bool check_free_place(struct info_list* lst);
void delete_element(int num, struct info_list* lst);
void push_after_element(int num, int value, struct info_list* lst);
void push_in_back(int value, struct info_list* lst);
void print_list(struct info_list* lst);
void work_with_list(struct info_list* lst);
#endif
