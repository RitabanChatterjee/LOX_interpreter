#include "eval.h"

typedef struct hashtable hashtable;
typedef struct Entry Entry;

struct Entry
{
    char* key;
    Literal value;
    Entry* next;
};

struct hashtable
{
    Entry** buckets;
    int numkeys;
    int capacity;
};

hashtable init_hashtable(int size);
void put(char* key, Literal value,hashtable* ht);//returns -1 if key exists;
int get(char* key, hashtable* ht,Literal* out);
void freeHashTable(hashtable* ht);
int isPresent(char* key, hashtable* ht);