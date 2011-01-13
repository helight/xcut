# Makefile.am

noinst_PROGRAMS = runtests calculator_test product_database_test get_char_test hashtable_test list_test

runtests_SOURCES = runtests.c
runtests_LDADD = $(top_srcdir)/src/libxcut.a

calculator_test_SOURCES = calculator_test.c calculator.c
calculator_test_LDADD = $(top_srcdir)/src/libxcut.a

product_database_test_SOURCES = product_database_test.c product_database.c database.h
product_database_test_LDADD = $(top_srcdir)/src/libxcut.a

get_char_test_SOURCES = get_char_test.c get_char.c
get_char_test_LDADD = $(top_srcdir)/src/libxcut.a

hashtable_test_SOURCES = hash.c hash.h hash_unittest.c
hashtable_test_LDADD = $(top_srcdir)/src/libxcut.a

list_test_SOURCES = list.h list_unittest.c
list_test_LDADD = $(top_srcdir)/src/libxcut.a
