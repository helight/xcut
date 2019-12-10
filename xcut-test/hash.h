#ifndef __XHASH__
#define __XHASH__
#include <stdlib.h>
#include <stdint.h>

//hash node
struct hnode{
        void *key;
        void *value;
        struct hnode *next;
};

//the head of hash table
struct hash_t{
	unsigned int tsize;	//length of the hash table
	unsigned int nsize;	//number of the node in this hash table
	unsigned int ksize;	//length of the hash key
	uint32_t  (*hash_idx)(unsigned char *, unsigned long );
				//hash fun to get the index
	int (*isnode)(const void *, const void *);
				//check the node if there is already in
	unsigned int (*index)(const void *);
				//get the index of table from key
	struct hash_ops *ops;	//operations of hash table
	struct hnode **ntable;	//hash table
};

//operations of hash table
struct hash_ops{
	unsigned int (*index)(struct hash_t *, void *);
	int (*insert)(struct hash_t *, struct hnode *);
	void *(*get)(struct hash_t *, void *);
	void *(*del)(struct hash_t *, void *);
};
struct hash_t *create_hasht(unsigned int tsize, unsigned int ksize,
                uint32_t (*hash_fun)(unsigned char * key, unsigned long len),
                int isnode(const void *key1, const void *key2));
int hash_insert(struct hash_t *htable, struct hnode *node);
void *hash_get(struct hash_t *htable, void *key);
void *hash_del(struct hash_t *htable, void *key);
int hash_free(struct hash_t *htable);

#endif
