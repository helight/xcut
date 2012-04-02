#include <stdio.h>
#include <stdlib.h>

#include "list.h" /* 经过改造后的list.h头文件 */
#include "xcut.h"


struct test_list {
    int test1;
    int test2;
    struct list_head list;
};

struct test_list xlist = {
    .list = LIST_HEAD_INIT(xlist.list),    /*初始化链表头*/
};

void tc_init_list(lcut_tc_t *tc, void *data) {

    LCUT_PTR_EQ(tc, (char *)xlist.list.next, (char *)xlist.list.prev);
    LCUT_PTR_EQ(tc, (char *)&xlist.list, (char *)&xlist.list);
}

void tc_add_show_list(lcut_tc_t *tc, void *data) {
    struct test_list *tmp;
    struct list_head *pos;
    unsigned int i;

    /* 给xlist增加元素 */
    for(i=5; i != 0; --i) {
        tmp= (struct test_list *)malloc(sizeof(struct test_list));
        /* 或者INIT_LIST_HEAD(&tmp->list); */
        tmp->test1 = i;
	tmp->test2 = i;
        list_add(&(tmp->list), &(xlist.list));
        /* 也可以用list_add_tail() 在表尾增加元素*/
    }
    i = 1;
    list_for_each(pos, &xlist.list) {
        /* 在这里 pos->next 指向next 节点, pos->prev指向前一个节点.这里的节点是
         * struct test_list类型. 但是，我们需要访问节点本身
         * 不是节点中的list字段，宏list_entry()正是为此目的。*/
        tmp= list_entry(pos, struct test_list, list);
	LCUT_INT_EQ(tc, i, tmp->test1);
	LCUT_INT_EQ(tc, i, tmp->test2);
	i++;
    }
}

void tc_add_show_list2(lcut_tc_t *tc, void *data) {
    struct test_list *tmp;
    struct list_head *pos;
    unsigned int i;

    for(i = 1; i < 6; i++) {
        tmp= (struct test_list *)malloc(sizeof(struct test_list));
        tmp->test1 = i;
	tmp->test2 = i;
        list_add_tail(&(tmp->list), &(xlist.list));
    }
    /* 因为这是循环链表，也可以以相反的顺序遍历它，
        *为此，只需要用'list_for_each_prev'代替'list_for_each'，   
       * 也可以调用list_for_each_entry() 对给定类型的节点进行遍历。
        * 例如:
        */
    i = 5;
    list_for_each_prev(pos, &(xlist.list)){
        tmp= list_entry(pos, struct test_list, list);
	LCUT_INT_EQ(tc, i, tmp->test1);
	LCUT_INT_EQ(tc, i, tmp->test2);
	i--;
    }
    i = 1;
    list_for_each_entry(tmp, &xlist.list, list) {
	LCUT_INT_EQ(tc, i, tmp->test1);
	LCUT_INT_EQ(tc, i, tmp->test2);
	i++;
    }
}

void tc_del_list(lcut_tc_t *tc, void *data) {
    struct test_list *tmp;
    struct list_head *pos, *q;
    unsigned int i;

    /*现在，我们可以释放 test_list节点了.我们本可以调用 list_del()删除节点
     * 但为了避免遍历链表的过程中删除元素出错，因此调用另一个更加安全的宏
     * list_for_each_safe(),具体原因见后面的分析
     */
    list_for_each_safe(pos, q, &xlist.list) {
        tmp = list_entry(pos, struct test_list, list);
	LCUT_PTR_NE(tc, NULL, (char *)tmp);
        list_del(pos);
        free(tmp);
	//LCUT_PTR_EQ(tc, NULL, (char *)tmp);
    }
    i = 0;
    list_for_each_entry(tmp, &xlist.list, list) {
        LCUT_PTR_EQ(tc, NULL, (char *)tmp);
        i++;
    }
    LCUT_PTR_EQ(tc, (char *)&xlist, (char *)tmp);
    LCUT_INT_EQ(tc, 0, i);
}

int main(int argc, char **argv)
{
    //lcut_ts_t   *suite = NULL;
    LCUT_TEST_BEGIN("List unit test", NULL, NULL);
    
    XCUT_TS_INIT(suite, "list unit test suite", NULL, NULL);
    LCUT_TC_ADD(suite, "Init list case", tc_init_list, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "add and show list case", tc_add_show_list, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "del list case", tc_del_list, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "add and show list case2", tc_add_show_list2, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "del list case2", tc_del_list, NULL, NULL, NULL);

    LCUT_TS_ADD(suite);
    XCUT_TEST_RUN();
}
