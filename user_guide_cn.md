## 简介 ##
> xcut是从lcut分出来的一个分支，主要加入了helight.xu认为个人的一些特性，重新组织了输出方式了提供了更为丰富的断言函数。
> 该文档也是由lcut的文档修改而来！
lcut 是"Lightweight C Unit Test framework"的缩写，它使用标准C语言实现，可以很容易的在不同额主流平台上使用，如Solaris、Linux等。

## 测试执行 ##

一个使用lcut进行的单元测试有三个层次：一个逻辑测试、测试套件和测试用例。每个逻辑测试可以包含多个测试套件，且每个测试套件又包含多个测试用例。在lcut这个测试框架中，测试用例是最基本和最小的单元。

实际上，lcut中的测试用例是原型为"void (**tc\_func)(lcut\_tc\_t**tc, void **data)"的函数。lcut使用 LCUT\_TC\_ADD 宏向一个测试套件中添加一个测试用例，测试套件使用 LCUT\_TS\_INIT 宏初始化。每个使用lcut进行的单元测试开始于 LCUT\_TEST\_BEGIN ，结束于 LCUT\_TEST\_END 。另外 LCUT\_TEST\_RESULT 宏可用于将执行结果反馈给本次测试的调用者(例如一些持续集成脚本等)。**

```
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

```
上面测试输出结果如下:
```
==================================================
	 a simple str test 
==================================================

===RunSuite===: a simple str unit test suite 
 [  Failed  ] Case 'str test case':
  * File    : get_char_test.c : 28 : Failed
  * Function: LCUT_PTR_EQ  
  * Expected: NULL 
  * Actual  : lden Global View 
 [  Failed  ] Case 'strn test case':
  * File    : get_char_test.c : 39 : Failed
  * Function: LCUT_STR_EN  
  * Expected: iw : Length: 2 
  * Actual  : iew 

===Summary===:
      Type     Total       Ran    Passed    Failed
   Suites:         1         1         0         1
    Cases:         2         2         0         2
     Time:        174 us

==================================================
		 RED BAR!  
==================================================
```
如果所有测试用例都通过，则你的控制台上会输出一个绿色的"GREEN BAR!"，否则红色的"RED BAR!"将被呈现出来，并且伴随着失败用例的原因，
## 断言 ##

xcut提供了许多断言宏：

整型断言：
  * LCUT\_INT\_EQ(tc, expected, actual)
  * LCUT\_INT\_NE(tc, expected, actual)
  * LCUT\_INT\_GT(tc, expected, actual)
  * LCUT\_INT\_LT(tc, expected, actual)
  * LCUT\_INT\_GE(tc, expected, actual)
  * LCUT\_INT\_LE(tc, expected, actual)

字符串断言：
  * LCUT\_STR\_EQ(tc, expected, actual)   字符串相等
  * LCUT\_STR\_NE(tc, expected, actual)   不相等
  * LCUT\_STR\_EN(tc, expected, actual, n)前n个字符相等
  * LCUT\_STR\_CASEEQ(tc, expected, actual)不区分大小相等
  * LCUT\_STR\_CASENE(tc, expected, actual) 不区分大小不相等

指针断言：
  * LCUT\_PTR\_EQ(tc, expected, actual)     指针一样
  * LCUT\_PTR\_NE(tc, expected, actual)     指针不一样

浮点数断言：
  * LCUT\_DOU\_EQ(actual, expected, granularity)   granularity为精度
  * LCUT\_DOU\_NE(actual, expected, granularity)

真假断言：
  * LCUT\_TRUE(tc, condition)    条件为真
  * LCUT\_FALSE(tc, condition)   条件为假

断言宏的使用方法显而易见，这里不赘述。

## Mock支持 ##

xcut支持mock，该部分直接继承于lcut。

mock是一种重要的将你的单元测试与外部依赖隔离的方法。 LCUT\_MOCK\_RETV 和 LCUT\_MOCK\_ARG 分别用例mock函数的返回值和输出参数。

Mocked函数 'table\_row\_count' 实现如下:
```
int table_row_count(const database_conn *conn,
                    const char *table_name,
                    int *total_count) {
    (*total_count) = (int)LCUT_MOCK_ARG();
    return (int)LCUT_MOCK_RETV();
}
```
依赖'table\_row\_count'的测试用例可以使用被mocked的'table\_row\_count'函数，并且可通过 LCUT\_RETV\_RETURN 和 LCUT\_ARG\_RETURN 宏来自由控制被mocked的'table\_row\_count'的返回值和输出参数的值。
```
    LCUT_ARG_RETURN(table_row_count, 5);  /* the total_count will be 5 after invoking the mocked table_row_count */
    LCUT_RETV_RETURN(table_row_count, 0); /* the return value of mocked table_row_count will be 0 */
```
跟过关于mock支持的细节可参考lcut包中example目录下的例子。

注意 : lcut不支持mock类型为double的函数返回值或参数。