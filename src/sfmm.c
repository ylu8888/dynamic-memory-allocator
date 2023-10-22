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

    //call mem grow
    //remember the first 8 bytes of heap are empty, unused
    //skip to 8 bytes after that the heap and then start doing prologue, epilouge
    //put a prologue in front of heap which is block of minimum size, has the header 16 bytes of padding and a footer
    //put a epilogue which is an 8 byte header whcih doesnt have footer or padding
    //EVERY THING in between epilogue and prologue those 4800 bytes you have to make into another block
    // that will be your first free block, you put a header for that too and a footer for that

    //initially memstart 
    if(sf_mem_start() == sf_mem_end()){
        //initialize the empty heap
        //grow the heap
        
        sf_block* startPtr = (sf_block*) sf_mem_grow(); //4096 bytes added to the heap returns a pointer to the top

        //sf_block* realStart = startPtr; //ptr + 8 to skip that and leave it

         //begin on the next part 
        //prologue min size of 32 which is allocated 
        //only has padding no payload
        //put the allocated bit to 1 
        startPtr->header = (0x20 | 0x8); //to get to the blocksize of the header and allocate block size to 32 and allocated bit to 1

        //gotta go to next block to access the footer
        sf_block* nextPtr = (sf_block *)((void *)startPtr + 32); // this will help us jump to next blocks start aka first blocks pointer
        nextPtr->prev_footer = startPtr->header; //this will set the block size the same as headers
       
        //just look at the block size at the header in order to tell if the block is big enoguh to allocate anything 
        nextPtr->header = (0xFD0);

        sf_block* endPtr = (sf_block *)((void *)sf_mem_end() - 16); //this will get to the prevFooter of the epilogue
        endPtr->prev_footer = nextPtr->header;

        endPtr->header = 0x8;

        sf_show_heap();

        //unused 8
        //prologue 32
        // actualy memory 4048
        // epilogue 8
        //whole thing 4096
        
        //epilogue has 8 byte header 
    
        
        //now the heap has the memoryy but we need to initialize it
        //heap needs blocks of memory to populate it
        //if alloc in block is allocated we set it to 1
        //but if its free we set it to 0
        //pre alloc refesr to the previous block
        //for the prologue it will always be unused

        //payload is in the memory we store
        //next and prev pointer if block is free (16 bytes)
        //minimum size requirement is 32 bytes 
        //payload must be double word aligned, aka a multiple of 16 -> next minimum would be 48
       
        //if it doesnt meet the double word alignment, for ex: malloc(40) we need to add padding of 8 bytes to make it multiple of 48


        //how to use the structs
        //block is actually just from the previous footer to the end of payload
        //to get the footer of a block, you need to get the next blocks prevFooter

        //skip the first 8 bytes to get alignment 
        //call memstart
        
    }
   
    
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
