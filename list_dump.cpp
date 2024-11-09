#include "list_dump.h"

void dump_in_file(struct info_list* lst)
{
    fprintf(lst->dump_file, "digraph G{\n\
    rankdir = LR;\n\
    splines = ortho;\n\
    node[color = \"#000000\", fontsize = 10];\n\
    edge[color = \"#000000\", fontsize = 5];\n\
    subgraph list {\n\
    node[style = filled, color = white, fontsize = 10];\n\
    edge[color = \"#000000\", fontsize = 5];\n\
    style = \"dashed\";\n");
    for(int i = 0; i < SIZE_LIST; i++)
    {
        if (lst->list[i].data == FREE)
        {
            fprintf(lst->dump_file, "%d [shape = Mrecord, style = filled, fillcolor = \"#e34f4f\", color = \"#ff8333\", label = \" IP: %d | DATA: %d | NEXT: %d | PREV: %d \"];\n",
    i, i, lst->list[i].data, lst->list[i].next, lst->list[i].prev);
        } else if (lst->list[i].data == NULL_ELEM) {
            fprintf(lst->dump_file, "%d [shape = Mrecord, style = filled, fillcolor = \"#e8bf1a\", color = \"#ffef33\", label = \" IP: %d | DATA: %d | NEXT: %d | PREV: %d \"];\n",
    i, i, lst->list[i].data, lst->list[i].next, lst->list[i].prev);
        } else {
            fprintf(lst->dump_file, "%d [shape = Mrecord, style = filled, fillcolor = \"#94e34f\", color = \"#000000\", label = \" IP: %d | DATA: %d | NEXT: %d | PREV: %d \"];\n",
    i, i, lst->list[i].data, lst->list[i].next, lst->list[i].prev);
        }
    }
    fprintf(lst->dump_file, "0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 [weight = 10000, color = \"#ffffff\"];\n");
    for (int i = 0; i < SIZE_LIST; i++)
    {
        fprintf(lst->dump_file, "%d -> %d [constraint = false, color = \"#000000\", weight = 0]\n%d -> %d [constraint = false, color = \"#000000\", weight = 0]\n", i, lst->list[i].next, i, lst->list[i].prev);
    }
    fprintf(lst->dump_file, "}\nInfo[shape = note, style = \"filled\", fillcolor = \"#FFD100\" label = \" HEADER | Head: %d | Tail: %d | Free: %d \"];\n}", lst->list[NULL_ELEM].next, lst->list[NULL_ELEM].prev, lst->free);
}

void dump(struct info_list* lst)
{

    printf("data: ");
    for (size_t i = 0; i < SIZE_LIST; i++)
    {
        printf("%d ", lst->list[i].data);
    }
    printf("\n");

    printf("next: ");
    for (size_t i = 0; i < SIZE_LIST; i++)
    {
        printf("%d ", lst->list[i].next);
    }
    printf("\n");

    printf("prev: ");
    for (size_t i = 0; i < SIZE_LIST; i++)
    {
        printf("%d ", lst->list[i].prev);
    }
    printf("\n");

    printf("free = %d\n", lst->free);
    printf("head = %d\n", lst->list[NULL_ELEM].next);
    printf("tail = %d\n", lst->list[NULL_ELEM].prev);
}
