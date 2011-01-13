/*
 * Copyright (c) 2010-~ Helight Xu <Helight.Xu@gmail.com>
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

#include <time.h>
#include <sys/time.h> 
#include "xcut.h"

extern char * get_str(char *str, char *substr);

void tc_str(lcut_tc_t *tc, void *data) {
    char *str="Golden Global View";

    LCUT_STR_EQ(tc, "iew", get_str(str, "iew"));
    LCUT_STR_NE(tc, "eew", get_str(str, "iew"));
    LCUT_PTR_EQ(tc, NULL, get_str(str, "l"));
    LCUT_PTR_NE(tc, NULL, get_str(str, "w"));
    LCUT_STR_EQ(tc, "iew", get_str(str, "ie"));
    LCUT_STR_CASEEQ(tc, "ew", "IEW");
    LCUT_STR_CASENE(tc, "iew", "IeW");
    LCUT_STR_CASEEQ(tc, "ew", "eW");
}

void tc_nstr(lcut_tc_t *tc, void *data) {
    char *str="Golden Global View";

    LCUT_STR_EN(tc, "iw", get_str(str, "ie"), 2);
    //LCUT_STR_EN(tc, NULL, get_str(str, "xxe"), 3);
    //LCUT_STR_EN(tc, NULL, get_str(str, "dddd"), 1);
    LCUT_STR_EN(tc, "iew2", get_str(str, "ie"), 0);
}

int main() {
    lcut_ts_t   *suite = NULL;
    LCUT_TEST_BEGIN("a simple str test", NULL, NULL);

    LCUT_TS_INIT(suite, "a simple str unit test suite", NULL, NULL);
    LCUT_TC_ADD(suite, "str test case", tc_str, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "strn test case", tc_nstr, NULL, NULL, NULL);
    LCUT_TS_ADD(suite);

    LCUT_TEST_RUN();
    LCUT_TEST_REPORT();
    LCUT_TEST_END();

    LCUT_TEST_RESULT();

   return 0;
}
