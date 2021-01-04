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

#define test_func(name)  \
    void test_##name() { time_t start = time(NULL); \
        printf("\n\n- %s\n", __func__);

#define test_func_end printf("\n\n%s  finished in %lds.\n",__func__ ,time(NULL) - start);}

typedef void(*test_func_t)(void);

void invoke_test_funcs(test_func_t test, ...) {
    va_list ap;
    va_start(ap, test);
    while (test) {
        test();
        test = va_arg(ap, test_func_t);
    }
    va_end(ap);
}

#define invoke_test(...) invoke_test_funcs(__VA_ARGS__, NULL)

#define assert_str_eq(a, b) assert(0 == strcmp(a, b))

#define assert_eq(a, b) assert(a == b)

#endif //COLL_TEST_H
