#include "list_func.h"
#include "list_dump.h"

void list_ctor(struct info_list* lst)
{
    lst->dump_file = fopen("dump_file.txt", "w");
    if(lst->dump_file == NULL) fprintf(stderr,"ERROR, file is not open\n");
    lst->list = (struct str_list*) calloc(SIZE_LIST, sizeof(struct str_list));
    lst->free = 1;

    lst->list[0].data = NULL_ELEM;
    lst->list[0].prev = NULL_ELEM;
    lst->list[0].next = NULL_ELEM;

    for (size_t i = 1; i < SIZE_LIST; i++)
    {
        lst->list[i].data = FREE;
        if (i < SIZE_LIST - 1) lst->list[i].next = i + 1;
        lst->list[i].prev = i - 1;
    }

    lst->list[SIZE_LIST - 1].next = 0;
}

void list_dtor(struct info_list* lst)
{
    free(lst->list);
    for(int i = 1; i < SIZE_LIST; i++)
    {
        lst->list[i].data = FREE;
    }
    assert(fclose(lst->dump_file) == 0);
}

bool check_range_of_index(int num)
{
    if (num >= SIZE_LIST || num < NULL_ELEM)
    {
        fprintf(stderr, "ERROR, trying to access a non-existent index\n");
        return false;
    } else
    {
        return true;
    }
    return false;

}

bool check_free_index(int num, struct info_list* lst)
{
    if (lst->list[num].data == FREE)
    {
        fprintf(stderr, "ERROR, trying to access a free index\n");
        return false;
    }
    return true;
}

bool check_free_place(struct info_list* lst)
{
    if (lst->free == NULL_ELEM)
    {
        fprintf(stderr, "ERROR, free index does not anymore\n");
        return false;
    }
        return true;
}

void delete_element(int num, struct info_list* lst)
{
    if (check_range_of_index(num) && check_free_index(num, lst) && check_free_place(lst))
    {

        lst->list[lst->list[num].prev].next = lst->list[num].next;
        lst->list[lst->list[num].next].prev = lst->list[num].prev;

        lst->list[num].data = FREE;

        lst->list[num].next = lst->free;
        lst->list[lst->free].prev = num;
        lst->list[num].prev = NULL_ELEM;
        lst->free = num;
    }
}

void push_in_head(int value, struct info_list* lst)
{
    push_after_element(lst->list[NULL_ELEM].next, value, lst);
}

void push_in_back(int value, struct info_list* lst)
{
    push_after_element(lst->list[NULL_ELEM].prev, value, lst);
}

void push_after_element(int num, int value, struct info_list* lst)
{
    if (check_range_of_index(num) && check_free_index(num, lst) && check_free_place(lst))
    {
        int index_push = lst->free;
        lst->list[lst->free].data = value;
        lst->free = lst->list[lst->free].next;
        lst->list[lst->free].prev = NULL_ELEM;

        int next = lst->list[num].next;
        lst->list[num].next = index_push;
        lst->list[index_push].prev = num;
        lst->list[next].prev = index_push;
        lst->list[index_push].next = next;

        if (lst->list[NULL_ELEM].prev == 0)
        {
            lst->list[NULL_ELEM].prev = num;
        }

        if(lst->list[NULL_ELEM].prev == num)
        {
            lst->list[NULL_ELEM].prev = lst->list[num].next;
        }
    }
}

void print_list(struct info_list* lst)
{
    for(int i = lst->list[NULL_ELEM].next; i != lst->list[NULL_ELEM].prev; i = lst->list[i].next)
    {
        printf("%d ", lst->list[i].data);
        if (lst->list[i].next == lst->list[NULL_ELEM].prev)
        {
            printf("%d", lst->list[lst->list[i].next].data);
        }
    }
    if (lst->list[NULL_ELEM].next == lst->list[NULL_ELEM].prev && lst->list[NULL_ELEM].next != 0)
    {
        printf("%d", lst->list[lst->list[NULL_ELEM].next].data);
    }
    printf("\n");
}

void work_with_list(struct info_list* lst)
{
    printf("0 - end programm\n1 - print list\n2 - dump\n3 - push after element\n4 - push in head\n5 - push in head\n6 - delete element\n7 - dump in file\n");
    int programm_options = -1;
    while (programm_options != END_PROG)
    {
        printf("choose programm options\n");
        scanf("%d", &programm_options);
        switch(programm_options)
        {
            case END_PROG:
            {
                break;
            }
            case PRINT:
            {
                print_list(lst);
                break;
            }
            case DUMP:
            {
                dump(lst);
                break;
            }
            case DUMP_IN_FILE:
            {
                dump_in_file(lst);
                break;
            }
            case PUSH_AFTER:
            {
                int num = 0;
                int value = 0;
                printf("printf num and value for push to list\n");
                scanf("%d", &num);
                scanf("%d", &value);
                push_after_element(num, value, lst);
                break;
            }
            case PUSH_IN_HEAD:
            {
                int value = 0;
                printf("printf value for push to head\n");
                scanf("%d", &value);
                push_in_head(value, lst);
                break;
            }
            case PUSH_IN_BACK:
            {
                int value = 0;
                printf("printf value for push to head\n");
                scanf("%d", &value);
                push_in_back(value, lst);
                break;
            }
            case DELETE:
            {
                int num = 0;
                printf("printf num for delete from list\n");
                scanf("%d", &num);
                delete_element(num,lst);
                break;
            }
            default:
            {
                printf("wrong options\n");
                break;
            }
        }
    }
}
