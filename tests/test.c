//
// Created by sea on 2019/11/29.
//

#include <stdio.h>
#include <string.h>
#include "../src/list.h"
#include "../src/queue.h"

void print_str(void *data) {
    printf("%s ", (char *) data);
}

int cmp_str(void *x, void *y) {
    return -strcmp(x, y);
}

bool equal_1d(void *data) {
    return strcmp(data, "1d") == 0;
}

void print_list(List *list) {
    printf("\n\nlen: %u\n", list_len(list));
    list_foreach(list, print_str);
    printf("\n\n");
}

void test_list() {
    List *list = list_new();
    list_insert_sorted(list, "a", cmp_str);
    list_insert_sorted(list, "b", cmp_str);
    list_insert_sorted(list, "rtfd", cmp_str);
    list_insert_sorted(list, "we", cmp_str);
    list_insert_sorted(list, "1d", cmp_str);
    list_insert_sorted(list, "kg", cmp_str);
    list_insert_sorted(list, "1d", cmp_str);
    list_insert_sorted(list, "1d", cmp_str);
    print_list(list);

    print_str(list_at(list, 3));
    print_str(list_front(list));
    print_str(list_back(list));
    for (int i = 0; i < list_len(list); ++i) {
        print_str(list_at(list, i));
    }

    print_str(list_remove_front(list));
    print_list(list);

    print_str(list_remove_back(list));
    print_list(list);

    print_str(list_remove_at(list, 1));
    print_list(list);

    print_str(list_remove(list, "a"));
    print_list(list);

    list_insert_after(list, "k", "b");
    print_list(list);

    list_insert_before(list, "g", "k");
    print_list(list);

    list_insert_at(list, "f", 2);
    print_list(list);

    printf("count:%u ", list_remove_if(list, equal_1d));
    print_list(list);

    printf("count:%u ", list_remove_all(list, "b"));
    print_list(list);

    list_free(list);
}

int main() {
    test_list();
    return 0;
}
