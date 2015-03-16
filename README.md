###About Xcut###

xcut is a C Unit Test framework maintained by HelightXu. xcut is another branch of lcut and more feature then lcut!

###demo:###

    #include "xcut.h"
      
    /*
     * A case that test nothing and succeed
    */
    void tc_null_test(lcut_tc_t *tc, void *data) {
    
    }
  
    int main() {
        lcut_ts_t   *suite = NULL;
        LCUT_TEST_BEGIN("a null test", NULL, NULL);
     
        LCUT_TS_INIT(suite, "a null test suite", NULL, NULL);
        LCUT_TC_ADD(suite, "null test", tc_null_test, NULL, NULL, NULL);
        LCUT_TS_ADD(suite);
    
        LCUT_TEST_RUN();
        LCUT_TEST_REPORT();
        LCUT_TEST_END();
    
        LCUT_TEST_RESULT();
    }

####run result:####

    ==================================================
            a null test 
    ==================================================

    ===RunSuite===: a null test suite 
    [  Passed  ] Case 'null test'
    
    ===Summary===:
          Type     Total       Ran    Passed    Failed
        Suites:         1         1         1         0
         Cases:         1         1         1         0
          Time:         84 us
    
    ==================================================
                     GREEN BAR!  
