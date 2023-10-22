/**
 * Do not submit your assignment with a main function in this file.
 * If you submit with a main function in this file, you will get a zero.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "sfmm.h"

void *sf_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }
    //if allocation not successful
    // sf_errno = ENOMEM;
    // return NULL;

    sf_mem_grow(); //call mem grow

    

    //call mem grow
    //remember the first 8 bytes of heap are empty, unused
    //skip to 8 bytes after that the heap and then start doing prologue, epilouge
    //put a prologue in front of heap which is block of minimum size, has the header 16 bytes of padding and a footer
    //put a epilogue which is an 8 byte header whcih doesnt have footer or padding
    //EVERY THING in between epilogue and prologue those 4800 bytes you have to make into another block
    // that will be your first free block, you put a header for that too and a footer for that
   
    
    abort();
}

void sf_free(void *pp) {
    // To be implemented.
    abort();
}

void *sf_realloc(void *pp, size_t rsize) {
    // To be implemented.
    abort();
}

double sf_fragmentation() {
    // To be implemented.
    abort();
}

double sf_utilization() {
    // To be implemented.
    abort();
}
