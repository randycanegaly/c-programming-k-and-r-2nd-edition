#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

/*
 * Write a function undef that will remove a name and definition from the 
 * table maintained by lookup and install
 */

struct nlist {
    struct nlist *next; /*next entry in chain*/
    char *name;         /*defined name*/
    char *defn;         /*replacement text*/
};

static struct nlist *hashtab[HASHSIZE]; /*pointer table*/
unsigned hash(char *);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
void undef(char *);

int main(void) {
    //install one
    char *name = "bofus";
    char *defn = "snork";

    install(name, defn);
    struct nlist *first = lookup(name);
    printf("%s: %s\n", first->name, first->defn); 

    undef(name);

    struct nlist *after = lookup(name);
    if (after == NULL)//couldn't find it
        printf("remove successful\n");
    else
        printf("remove didn't work correctly\n");

    return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) //walk the pointer to string chars until the end
        hashval = *s + 31 *hashval; //calculate hash
    return hashval % HASHSIZE;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { //name not found in hash table
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;//memory allocation failed or name is NULL
        hashval = hash(name);
        np->next = hashtab[hashval];//will be null if new nlist point, because was null in lookup
        hashtab[hashval] = np; //put new nlist pointer in hash table
    } else /* name is already there in the hash table */
        free((void *) np->defn); //free the previous defn, going to replace it
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) ==0)
            return np; //found s in the hash table
    return NULL; //s not found
}

/* undef: remove a name and definition fromt he table */
void undef(char *name) {
    int h;
    struct nlist *prev, *np;
    
    prev = NULL;
    h = hash(name);

    //find the nlist that matches name
    for (np = hashtab[h]; np != NULL; np = np->next) {//get a pointer to the top of the matching block, walk the linked list
        //np->next only "increments" np after each loop iteration
        if (strcmp(name, np->name) == 0)//so, here name matches immediately and we break out of the loop
            break; 
        prev = np; //remembering, to know that the previous nlist is, but if name matches immediately (first nlist in block)
        //we broke out of the loop and this assignment never happens. So prev will be NULL if we are on the first nlist
        //in the block
    }
    if (np != NULL) { //double checking??
        //is this the first nlist in the block?
        if (prev == NULL)
            hashtab[h] = np->next;//skip 'this' nlist and make the next one the pointer in the hashtable, first of block
        else //not first in block, prev is not null
            prev->next = np->next;//prev points to the previous nlist. To skip 'this' nlist, set prev's next to 'this''s next
        //in either case, first nlist in block, or not, we've carved the matching nlist out of the singly-linked list
        //and now need to free the memory allocated to it. Do the struct elements first and then the pointer to the struct
        free((void *) np->name);
        free((void *) np->defn);
        free((void *) np);
    }
}

