#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next; /*next entry in chain*/
    char *name;         /*defined name*/
    char *defn;         /*replacement text*/
};

static struct nlist *hashtab[HASHSIZE]; /*pointer table*/
unsigned hash(char *);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);

int main(void) {
    //install one
    install("bofus", "snork");
    struct nlist *first = lookup("bofus");
    printf("%s: %s\n", first->name, first->defn); 
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

/*char* strdup(char* str) {
    // Allocate memory for the new string (including the null terminator)
    char* copy = (char*)malloc(strlen(str) + 1);
    if (copy == NULL) {
        // Allocation failed
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    // Copy the string
    strcpy(copy, str);
    return copy;
}*/

