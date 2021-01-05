//
// Created by sea on 2021/1/4.
//

#ifndef COLL_TEST_H
#define COLL_TEST_H

#include <stdarg.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define test_func(name) \
    void test_##name() { time_t start = time(NULL); \
        printf("[%s]\n", __func__);

#define test_func_end printf("\n%s  finished in %lds.\n\n",__func__ ,time(NULL) - start);}

typedef void(*test_func_t)(void);

void invoke_test_funcs(test_func_t test, ...) {
    char str[20];
    time_t now;
    time(&now);
    strftime(str, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("Tests start at %s.\n", str);
    va_list ap;
    va_start(ap, test);
    while (test) {
        test();
        test = va_arg(ap, test_func_t);
    }
    va_end(ap);
    printf("All tests passed.\n");
}

#define invoke_test(...) invoke_test_funcs(__VA_ARGS__, NULL)

#define assert_eq_str(l, r) assert(0 == strcmp(l, r))

#define assert_eq(l, r) assert(l == r)

#endif //COLL_TEST_H
