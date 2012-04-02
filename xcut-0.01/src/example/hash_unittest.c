#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "xcut.h"

int cmp(const void *p1, const void *p2)
{
    if(!p1) return !p2;
    if(!p2) return -1;

    return strcmp((const char * ) p1, (const char * ) p2);
}

char* key[]={"name","address","phone","door","city","sex","major"};
char* value[]={"netboy","china","263788","110#","guangzhou","male","information"};
char *tchar[]={"helightxu"};
struct hash_t *htable;

void tc_init_hashtable(lcut_tc_t *tc, void *data) {

    LCUT_INT_EQ(tc, 5, htable->tsize);
    LCUT_INT_EQ(tc, 7, htable->ksize);
    LCUT_INT_EQ(tc, 0, htable->nsize);
}

void tc_add_node(lcut_tc_t *tc, void *data) {
    int i = 0;
    struct hnode *tmp;

    for(i = 0; i < 7; i++) {
        tmp = malloc(sizeof(struct hnode));
        tmp->key = key[i];
        tmp->value = value[i];
        tmp->next = NULL;
        LCUT_INT_EQ(tc, 0, hash_insert(htable, tmp));
    }
    for(i = 0; i < 7; i++) {
        LCUT_STR_EQ(tc, value[i], ((struct hnode *)hash_get(htable, key[i]))->value);
    }
}

void tc_del_node(lcut_tc_t *tc, void *data) {
    struct hnode *tmp;

    tmp = (struct hnode *)hash_del(htable, key[2]);
        if (tmp != NULL)
            free(tmp);
    LCUT_STR_EQ(tc, NULL, hash_get(htable, key[2]));
}

void tc_change_node(lcut_tc_t *tc, void *data) {
    struct hnode *tmp;

    tmp = (struct hnode *)hash_get(htable, key[3]); 
    if (tmp != NULL)
        tmp->value = tchar[0];
    LCUT_STR_EQ(tc, tchar[0], ((struct hnode *)hash_get(htable, key[3]))->value);
    LCUT_STR_EQ(tc, "helightxu", ((struct hnode *)hash_get(htable, key[3]))->value);
    LCUT_STR_NE(tc, value[3], ((struct hnode *)hash_get(htable, key[3]))->value);
    LCUT_STR_EQ(tc, "helightxu", ((struct hnode *)hash_get(htable, key[3]))->value);
}

void setup()
{
    htable = create_hasht(5, 7, NULL, cmp);
}

void teardown()
{
    hash_free(htable);
}

int main() {
    LCUT_TEST_BEGIN("a simple calculator test", setup, teardown);

    XCUT_TS_INIT(suite, "hashtable unit test suite", NULL, NULL);
    LCUT_TC_ADD(suite, "Init hashtable case", tc_init_hashtable, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "add node to hashtable", tc_add_node, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "del node from hashtable", tc_del_node, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "del node from hashtable", tc_change_node, NULL, NULL, NULL);
	
	LCUT_TS_ADD(suite);
    XCUT_TEST_RUN();
}

