
#include "list_dump.h"
#include "list_func.h"

int main()
{
    struct info_list info_lst = {};
    list_ctor(&info_lst);
    work_with_list(&info_lst);
    list_dtor(&info_lst);
    return 0;
}

