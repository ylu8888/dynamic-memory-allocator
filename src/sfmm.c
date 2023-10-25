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
    if (size <= 0) {
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

    //if the heap is empty !
    if(sf_mem_start() == sf_mem_end()){

    //initialize the sf_free_lists first 

    //Array called sf_free_list_heads, which is an array of sf blocks with a size of num_free_lists = 10
    //each element of the array is a sentinel which represents a circular doubly linked list
    //sentinel is a dummy block, which the sentinels next block points to the first elem of array, and prev block points to the end of the circular list

    //iterate through sf free list heads,i < num_free_lists  for each sf_head(i) set its next block it self and set its prev block to itself
    //going thru the list and wanting to insert somewhere, if the list is empty, if .next points back to the sentinel it means its empty
        
        for(int i = 0; i < NUM_FREE_LISTS; i++){
            sf_free_list_heads[i].body.links.next = &sf_free_list_heads[i]; //ampsersand to point it to the memory address not the element
            sf_free_list_heads[i].body.links.prev = &sf_free_list_heads[i]; // this initializes the sentinel and makes the circula doubly linklist behavior correct
            
            //FIBONACCI SEQUENCE 
            //fib seq represents the free list heads, they represent size classes
            //first one represents M = 32
            // index 0 = blocks of size M only aka size 32
            // index 1 = minimum of 48, maximum is 64 (both inclusive)
            //at block 8 = minimum of 48M inclusive, upper bound is infinity exlusive)
            //at block 9 = wilderness block , if we want to allocate and we dont find it anywhere, we put it in wilderness
            //otherwise, if we dont find it in wilderness we call mem_grow again getting another 4096 bytes
            //free lists is all the free blocks

            //go into sf free list heads, insert the free block after the sentinel at index 9

        }

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
        
        //epilogue has 8 byte header 
        endPtr->header = 0x8;

        sf_show_heap();

        sf_free_list_heads[9].body.links.next = nextPtr;
        sf_free_list_heads[9].body.links.prev = nextPtr;
        nextPtr->body.links.next = &sf_free_list_heads[9];
        nextPtr->body.links.prev = &sf_free_list_heads[9]; //adding the free block into the array
    
        //unused 8
        //prologue 32
        //actualy memory 4048
        //epilogue 8
        //whole thing 4096
        
    
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
        
    }

    //M    [0]
    //1, 2 [1]
    //2, 3 [2]
    //3, 5 [3]
    //5, 8  [4]
    //8, 13 [5]
    //13, 21 [6]
    //21, 34 [7]
    //34, inifnity [8] 9th
    //wildnerneses block

    //if the heap is not empty 
    //use the sf free block list, each of them represents a size class for example M, (M, 2M) following fibonacci
    //if we want to malloc(70), we go through this and see which size class the 70 falls in, and each M is 32
    //first thing we want to do is find the smallest size class for the 70, in this case is the 2nd one
    //now iterate thru freelists[1] aka the second one, which has the range we're looking for
    //look for blocks that might fit our 70, use next ptr to iterate for free blocks
    //use header which has block size
    //for every block within appropriate size class, get the header, use bit manipulation to get the block size, at bit 28
    //if this block size greater than or equal to the 70,
    //if it is then the block is appropriate
    //if go through the whole list and dont find it then jump to the next size class and look again iterateing thru the doubly link list

    
    //finding the right size to malloc based on if its a multiple of 16
    if(size < 32) {
        size = 32;
    }
    else{
        if(size % 16 != 0){
        size = ((size / 16) + 1) * 16;
        }
    }

    //follow the fibonacci sequence on our own,
    //there will not be any M blocks in the doubly link lists
    //we will fill it up on our own gradually as we malloc
    //go ahead and insert 4000 into index[8] for example
    
    size_t M = 32;
    size_t listPtr = 0;
    
    if(size == M){
        listPtr = 0;
    }
    else if(M < size && size <= 2 * M){
        listPtr = 1;
    }    
    else if(2 * M < size && size <= 3 * M){
        listPtr = 2;
    }
    else if(3 * M < size && size <= 5 * M){
        listPtr = 3;
    }
    else if(5 * M < size && size <= 8 * M){
        listPtr = 4;
    }    
    else if(8 * M < size && size <= 13 * M){
        listPtr = 5;
    }
    else if(13 * M < size && size <= 21 * M){
        listPtr = 6;
    }
    else if(21 * M < size && size <= 34 * M){
        listPtr = 7;
    }
    else if(size > 34 * M){
        listPtr = 8; //9th index aka the one before wilderness
    }

    sf_block* sentinel = &sf_free_list_heads[listPtr]; //find the start of sentinel aka the free list index from listPtr

    sf_block* block = sentinel->body.links.next;  //set the block pointer to the next one in sentinel

    sf_block* removedBlock = NULL;

    while(block != sentinel){
        size_t blockSize = block->header;
        blockSize >>= 4;
        blockSize = blockSize & ((1 << 28) - 1); //find the block size using bit manipulation
    
        if(blockSize >= size){ //if we find the block size thats greater than or equal to size
            //now we need to remove this block
            removedBlock = block;//just to keep track of which block we're removing

            sf_block* prevBlock = block->body.links.prev; //temporarily store the prev and next blocks
            sf_block* nextBloque = block->body.links.next;

            block = prevBlock;
            block->body.links.next = nextBloque; //set the prevblock's next to blocks.next.next

            block = nextBloque;
            block->body.links.prev = prevBloque; //set the next blocks prev to blocks.prev.prev

            removedBlock->body.links.prev = NULL; //set the blocks next and prev to null
            removedBlock->body.links.next = NULL;

            //now we need to check for splinter OR split
            if((blockSize - size) < 32){
                //splintering 
                //say malloc(25) you would round it up to be 32, if you try to split it 
                //if 48 is the only space available in block, and want to malloc (32)
                //when you split it, you''ll be left with 16 bytes, which is less than minimum 32 bytes
          
            } else{ //SPLITTING A BLOCK
                //regarding the free block, we are splitting the free block into two blocks when we malloc (40)
                //insert a footer that has block size 48 and change the header of free block to 48
                //then add a header of size 4000 below the blocksize 40 footer and change the bottom footer to 4000 
            
                //all the free block should be in free list heads
                //now the free block turned into an allocated block and a new free block
                //had 4048 in wilderness, malloc(48), then get rid of 4048
                //set the allocated bits , if allocated then its 1, change its size to 48 for header and footer
                //set the bottom footer which was 4048 and update it to 4000, no need to allocate bit because its defaulted on 0
            
                //take the new block, which is the 4000 one, look where u need to insert it on the freelists, based on the fibonacci
                //it just needs to be in the right size class, the right sentinel with the (M, xM)
                //keep a fibonacci counter that keeps track of where u are (im at M, im on 3M, 5M)
                //based on that counter, we could see which index has the appropriate range
                //up until (34M, infinity)

                //take the free block we have aka the 40 block
                //check if epilogue if end_header = 0;
                //to check if its epilogue check its block size == 0
                //if it is epilogue then put it in the wilderness then we are at the end of the heap

                //removedBlock->header = removedBlock->header & 0xffffffff0000000f; //change the block size 
                sf_block* endBlock = (sf_block *)((void *) removedBlock + blockSize - 8);//move endPtr to the end of the block
                
                removedBlock->header = (size | 0x8); //changes the header block size AND allocates the bit for removedBlcok

                //we add the size of input to the removedBlock(which is a ptr that points to the top of the free block)
                sf_block* nextBlock = (sf_block *)((void *)removedBlock + size - 8); //now we are at the next block, -8 to account for 

                nextBlock->prev_footer = (size | 0x8); //set the footer of the allocated block
                
                nextBlock->header = (blockSize - size); //set the header of the next block //unallocated

                endBlock->prev_footer = (blockSize - size); //set the footer of the next block

                size_t epiCheck = endBlock->header;
                epiCheck >>= 4;
                epiCheck = epiCheck & ((1 << 28) - 1); //find the block size using bit manipulation

                //check epilogues header if block size = 0
                //if the epilogue is there, then add this new free block into the wilderness INSTEAD

                if(epiCheck == 0){//this means this is the epilogue so
                    //put it into wilderness, which either only has 1 block or none
                    sf_free_list_heads[9].body.links.next = nextBlock; //not header just the nextblock
                    sf_free_list_heads[9].body.links.prev = nextBlock;
                    nextBlock->body.links.next = &sf_free_list_heads[9];
                    nextBlock->body.links.prev = &sf_free_list_heads[9];
                    
                }
                else{  //put it into the sentinels array respectively
                    size_t newSize = blockSize - size; //48 - 32 = 16
                     
                    if(newSize == M){
                        listPtr = 0;
                    }
                    else if(M < newSize && newSize <= 2 * M){
                        listPtr = 1;
                    }    
                    else if(2 * M < newSize && newSize <= 3 * M){
                        listPtr = 2;
                    }
                    else if(3 * M < newSize && newSize <= 5 * M){
                        listPtr = 3;
                    }
                    else if(5 * M < newSize && newSize <= 8 * M){
                        listPtr = 4;
                    }    
                    else if(8 * M < newSize && newSize <= 13 * M){
                        listPtr = 5;
                    }
                    else if(13 * M < newSize && newSize <= 21 * M){
                        listPtr = 6;
                    }
                    else if(21 * M < newSize && newSize <= 34 * M){
                        listPtr = 7;
                    }
                    else if(newSize > 34 * M){
                        listPtr = 8; //9th index aka the one before wilderness
                    }

                    //after finding the size class, iterate through that link list and add the newblock
                    //if cant find it any of the doubly link list then we put it into wilderness
                    
                    //make a new node at the end of the circular linked list that connects every next and prev node
                    //next block is the free block(16), 'new block' is the block at the end of link list, aka sentinel.prev
                    sf_block* sentinel2 = &sf_free_list_heads[listPtr]; //move to the sentinel index
                    sf_block* newBlock = sentinel2->body.links.prev; //go to the last index in circular link list aka sentinel.prev
                    newBlock->body.links.next = nextBlock; //set the newBlocks next to nextblock
                    nextBlock->body.links.next = sentinel2; //set the nextBlocks next to sentinel
                    nextBlock->body.links.prev = newBlock; //set the nextBlcosk prev to newBlock
                    sentinel2->body.links.prev = nextBlock; //set the sentinels prev to nextblock
                                    
                }
                   
            }
            
            break; //we can break out because we found the proper blocksize
            
        } //end of if(blockSize >= size)
        
        block = block->body.links.next; //iterate through the free list moving block ptr
        
        if(block == sentinel){ //this means we have reached the end of the circular link list and restarted at sentinel
            listPtr++;
            if(listPtr == 9) break; //means we hit the  wilderness block
            sentinel = &sf_free_list_heads[listPtr];
            block = sentinel->body.links.next;  
        }
        
    } //end of while(block != sentinel)

    
    //calling memgrow does coalescing => get another 4048 basically combines two blocks
    

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
