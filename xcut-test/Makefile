CFLAG=-g -O2 -L./xcut/  -I./xcut/ -lxcut -static 

all:
#	gcc $(CFLAG) hash.c  hash.h  hash_unittest.c xcut/libxcut.a -o hashtable_test
	gcc hash.c  hash.h  hash_unittest.c -o hashtable_test $(CFLAG)
clean:
	rm hashtable_test
