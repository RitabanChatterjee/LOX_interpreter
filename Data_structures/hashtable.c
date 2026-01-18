#include "hashtable.h"


hashtable init_hashtable(int size)
{
    hashtable ret;
    ret.capacity=size;
    ret.buckets=(Entry**)malloc(size*sizeof(Entry*));
    ret.numkeys=0;
    return ret;
}




int hash(const char *str, int capacity) 
{
    int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 
    return hash % capacity;
}

static void traverseBucket(int ind, hashtable* ht,char* key,Literal val) // returns last node if key not present
{
    Entry* head=ht->buckets[ind];
    Entry* cpy=ht->buckets[ind];
    while(head!=NULL)
    {
        if(!strcmp(head->key,key))
        {
            head->key=key;
            head->value=val;
            return ;
        }
        head=head->next;
    }
    if(head==NULL)
    {
        ht->buckets[ind]=(Entry*)malloc(sizeof(Entry));
        ht->buckets[ind]->key=strdup(key);
        ht->buckets[ind]->next=cpy;
        ht->buckets[ind]->value=val;
        ht->numkeys++;

    }
    return ;
}

void put(char* key, Literal l,hashtable* ht)
{
    int ind=hash(key,ht->capacity);
    traverseBucket(ind,ht,key,l);
}


int get(char* key,hashtable* ht,Literal* out)
{
    int ind=hash(key,ht->capacity);
    Entry* head=ht->buckets[ind];
    while(head!=NULL)
    {
        if(!strcmp(key,head->key))
        {
            *out=head->value;
            return 1;
        }
        head=head->next;
    }
    return 0;
}

void freeList(Entry* e)
{
    Entry* head=e;
    while(head!=NULL)
    {
        Entry* temp=head;
        head=temp->next;
        free(temp->key);
        if(temp->value.t.tType==STRING)
        {
            free(temp->value.val.str);
            free(temp->value.t.token_val.str);
        }
        free(temp);
        temp=NULL;
        
    }
}
void freeHashTable(hashtable* ht)
{
    for(int i=0;i<ht->capacity;i++)
    {
        freeList(ht->buckets[i]);
    }
    free(ht->buckets);
}

int isKeyPresent(char* key, hashtable* ht)
{
    int ind=hash(key,ht->capacity);
    Entry* head=ht->buckets[ind];
    while(head!=NULL)
    {
        if(!strcmp(key,head->key))
        {
            return 1;
        }
        head=head->next;
    }
    return 0;
}