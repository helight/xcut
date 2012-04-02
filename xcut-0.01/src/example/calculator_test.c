/*
 * Copyright (c) 2005-2010 Tony Bai <bigwhite.cn@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "xcut.h"

extern int add(int a, int b);
extern int subtract(int a, int b);
extern int multiply(int a, int b);
extern int divide(int a, int b);

void tc_add(lcut_tc_t *tc, void *data) {
    LCUT_INT_EQ(tc, 10, add(2, 8));
    LCUT_INT_EQ(tc, -6, add(2, -8));
    LCUT_INT_EQ(tc, 0, add(2, -2));
    LCUT_INT_GT(tc, 1, add(2, -2));
    LCUT_INT_LT(tc, -1, add(2, -2));
    LCUT_INT_GE(tc, 0, add(2, -2));
    LCUT_INT_LE(tc, 0, add(2, -2));
    LCUT_TRUE(tc, add(2, -2));
}

void tc_subtract(lcut_tc_t *tc, void *data) {
    LCUT_INT_EQ(tc, 6, subtract(8, 2));
    LCUT_INT_EQ(tc, 10, subtract(2, -8));
    LCUT_INT_EQ(tc, 0, subtract(2, 2));
}

void tc_multiply(lcut_tc_t *tc, void *data) {
    LCUT_INT_EQ(tc, 16, multiply(8, 2));
    LCUT_INT_EQ(tc, -16, multiply(2, -8));
    LCUT_INT_EQ(tc, 0, multiply(0, 2));
}

void tc_divide(lcut_tc_t *tc, void *data) {
    LCUT_INT_EQ(tc, 4, divide(8, 2));
    LCUT_INT_EQ(tc, 0, divide(0, 8));
    LCUT_INT_EQ(tc, 1, divide(2, 2));
}

int main() {
    LCUT_TEST_BEGIN("a simple calculator test", NULL, NULL);

    XCUT_TS_INIT(suite, "a simple calculator unit test suite", NULL, NULL);
    LCUT_TC_ADD(suite, "add test case", tc_add, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "subtract test case", tc_subtract, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "multiply test case", tc_multiply, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "divide test case", tc_divide, NULL, NULL, NULL);

	LCUT_TS_ADD(suite);
    XCUT_TEST_RUN();
}
