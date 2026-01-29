#include "hashtable.h"


hashtable init_hashtable(int size)
{
    hashtable ret;
    ret.capacity=size;
    ret.buckets=(Entry**)malloc(size*sizeof(Entry*));
        for(int i = 0; i < size; i++)
        ret.buckets[i] = NULL;  

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
static Literal copyLiteral(Literal src)
{
    Literal dst = src;

    if (src.t.lType == LIT_STRING && src.val.str) {
        dst.val.str = strdup(src.val.str);
        dst.t.token_val.str = strdup(src.val.str);  // if you mirror it there
    }

    return dst;
}

static void traverseBucket(int ind, hashtable* ht,char* key,Literal val) // returns last node if key not present
{
    Entry* head=ht->buckets[ind];
    Entry* cpy=ht->buckets[ind];
    int found=0;
    while(head!=NULL)
    {
        if(!strcmp(head->key,key))
        {
            // if(head->value.t.tType == STRING) 
            // {
            //     free(head->value.val.str);
            //     free(head->value.t.token_val.str);
            // }   
            //first we must erase the current literal
            
            freeLiteral(&head->value);found=1;
           // head->key=key;
            head->value=copyLiteral(val);
            return ;
        }
        head=head->next;
    }
    Entry* e = malloc(sizeof(*e));
    e->key = strdup(key);          // copy the key to heap
    e->value = copyLiteral(val);
    e->next = ht->buckets[ind];    // current head becomes next
    ht->buckets[ind] = e;          // new node is head
    ht->numkeys++;
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

void freeEntry(Entry* e)
{
    Entry* head=e;
    while(head!=NULL)
    {
        Entry* temp=head;
        head=temp->next;
        free(temp->key);temp->key=NULL;
        // if(temp->value.t.tType==STRING)
        // {
        //     free(temp->value.val.str);
        //     free(temp->value.t.token_val.str);
        // }
        freeLiteral(&temp->value);
         free(temp);
        temp=NULL;
        
    }
}
void freeHashTable(hashtable* ht)
{
    for(int i=0;i<ht->capacity;i++)
    {
        freeEntry(ht->buckets[i]);
        ht->buckets[i]=NULL;
    }
    free(ht->buckets);
    ht->buckets=NULL;
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