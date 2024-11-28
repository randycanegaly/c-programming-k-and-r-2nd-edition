#include <stdio.h>

typedef long Align;//for alignment to a long boundary
union header {//definition of the header for a free memory block
    struct {
        union header *ptr; //within the above 'outer' header is a pointer 
                           //to another header - the next block in the free list
        unsigned size; //size of this block, in units
    } s;
    Align x; //force alignment of blocks
};
typedef union header Header;//define Header as a new type representing the block header

static Header *morecore(unsigned nu); //get more memory from the OS
static Header base;//the initial Header, available to all functions throughout this file
static Header *freep = NULL; //pointer to the start of the free list, initially empty

void *rmalloc(unsigned nbytes);
void *rcalloc(unsigned num, unsigned size);

int main(void) {
    rcalloc(5, 32);
    return 0;
}

void *rcalloc(unsigned num, unsigned size) {
    unsigned i, total_bytes;
    char *p, *q;

    total_bytes = num * size;

    if((p = q = rmalloc(total_bytes)) != NULL)
        for (i = 0; i < total_bytes; i++)
            *p++ = 0;//set all data to zero

    return q;//return pointer to the front of the new block of memory for n items
}

//malloc: general-purpose storage allocator
void *rmalloc(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;//, alt_nunits, whole, fraction, hsize, rawbytes;

    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;//clever way of creating round up to get size of header multiples for number of units
    //printf("alt_nunits: %d, nbytes: %d\n", alt_nunits, nbytes);

    if ((prevp = freep) == NULL) { //don't have a free list yet. Pointer to the start of the list is NULL
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {//before any loop iterations, set tracking pointer to the next pointer of previous block
                                                       //after each iteration, set previous pointer to 
                                                       //current free block, set tracking pointer to next free block
        if (p->s.size >= nunits) { //found section of free blocks that's big enough
            if (p->s.size == nunits) //found section of free blocks that matches exactly
                prevp->s.ptr = p->s.ptr;//set next pointer of previous pointer to next pointer of current pointer
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;//set free pointer to point to previous block
            return (void *)(p+1);//return a pointer to the start of the actual free units - 1 past the header of the free block
        }
        if (p == freep) //wrap around to the front of the free list. Either have no more free memory or starting with none
            if ((p = morecore(nunits)) == NULL)//get more memory from the OS
                return NULL; //no memory available from OS
    }
}

#define NALLOC  1024    //minimum number of new memory units to request

//morecore: ask system for more memory
static Header *morecore(unsigned nu) {//static - function has internal linkage, is only available within this file, ask for nu new units
    char *cp, *sbrk(int); //linux system call - returns a pointer to n more bytes of storage
    Header *up;
    void rfree(void *ap);

    if(nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));// asking for units
    if (cp == (char *) -1) //failed, no system provided memory available
        return NULL;
    up = (Header *) cp;//succeeded, cp is a void pointer, need to cast it
    up->s.size = nu;//number of units
    rfree((void *)(up+1));
    return freep;
}

//free: scan the free list, starting at freep and find a place to insert the free block
void rfree(void *ap) {
    Header *bp, *p;

    bp = (Header *)ap - 1; //point to the block header
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; //freed block at end or start of arena

    if (bp + bp->s.size == p->s.ptr) { //join to upper nbr
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}
