#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook_opt_hash.h"
/* optimal version 1 */
entry *findName(char lastName[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0){
            printf(" %12s  is found!\n", lastName);
            return pHead;
        }
        pHead = pHead->pNext;
    }
    printf(" %12s  is found!\n", lastName);
    return NULL;
}

entry *appendOptimal(char lastName[], entry *lne)
{
    /* allocate memory for the new entry and put lastName in it.*/
    lne->pNext = (entry *) malloc(sizeof(entry));
    lne = lne->pNext;
    strcpy(lne->lastName, lastName);
    lne->pNext = NULL;

    return lne;
}

hashTable *createHashTable(int tableSize)
{
    hashTable *ht = NULL;
    int i;

    if( tableSize < 1 ){
        return NULL;
    }

    /* Allocate the table itself. */
    if((ht = (hashTable *) malloc(sizeof(hashTable))) == NULL) {
        return NULL;
    }

    /* Allocate array of list. */
    if( (ht->list = (entry **)malloc(sizeof(entry *)*tableSize)) == NULL ) {
        return NULL;
    }

    /* Allocate list header */
    for( i = 0; i < tableSize; i++ ) {
        ht->list[i] = NULL;
    }

    ht->tableSize = tableSize;

    return ht;
}

entry* findNameHash(char *key, hashTable *ht)
{
    entry *lne;
    hashIndex index = hash2(key, ht);
    
    /* search the bucket */
    for(lne = ht->list[index]; lne != NULL; lne = lne->pNext){
        if ( strcasecmp(key, lne->lastName) == 0 ){
            printf(" %12s is found!\n", key);
            return lne;
        }
    }
    printf(" %12s is not found!\n", key);
    return NULL;
}

int appendHash(char *key, hashTable *ht)
{
    hashIndex index = hash2(key, ht);
    entry *newEntry;
    // lastNameEntry *currentEntry;

    /* Does lastNameEntry already exist? If it does, don't append it again. 
    if( (currentEntry = findNameHash(key, ht)) != NULL ){
        return 1;
    }*/

    /* attempt to allocate memory for lastNameEntry */
    if ((newEntry = (entry *) malloc(sizeof(entry))) == NULL){
        return 2;
    }

    /* Insert into list */
    strcpy(newEntry->lastName, key);
    newEntry->pNext = ht->list[index];
    ht->list[index] = newEntry;

    return 0;
}

hashIndex hash1(char *key, hashTable *ht)
{   
    unsigned int hashVal = 0;
    while(*key != '\0'){
        hashVal+= *key++;
    }

    return hashVal % ht->tableSize;
}

hashIndex hash2(char *key, hashTable *ht)
{
    unsigned int hashVal = 0;
    while(*key != '\0'){
        hashVal = (hashVal << 5) + *key++;
    }

    return hashVal % ht->tableSize;
}
