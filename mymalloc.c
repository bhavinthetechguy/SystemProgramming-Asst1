#include "mymalloc.h"
#include <stdio.h>

//Declaration of errors method and that giving me an errors accordinly input test.
void errors(int i , char * file, int line);

//making char bigger and smaller array with the size of 5000 and those are running according to my compare size which is (300) and real input test.
//This is for big chunks  
static char bigger[malloc_size];
//This is for small chunks			
static char smaller[malloc_size];		

// Pointer will return to memory buffer which is requested
	void* my_malloc(unsigned int size)
	{
		//Creating a check static int variable and assigning with '0' but here is as flase
		static int check = 0;
                //Creating variable of data type MemoryEntry
		struct MemoryEntry *p;
		struct MemoryEntry *q;
                static struct MemoryEntry *large;
		static struct MemoryEntry *small;
		//Checking a condition if the condition is true if block will run 
		if(!check)
		{
			//Assigning an address of block which is making dynamically and using own malloc to the pointer large
                        large = (struct MemoryEntry*)bigger;
                        //This block will act as doubly linked list and set a previous and next node to NULL
			(*large).previous = (*large).next = 0;
                        //Assigning a size using pointer large to size other way data info
			(*large).size = malloc_size - sizeof(struct MemoryEntry);
			//This is becoming true after all memory assigned successfully
                        //Act like a boolean and set it to true
			(*large).bool = 1;
                      
			//Assigning an address of block which is making dynamically and using own malloc to the pointer small			
			small= (struct MemoryEntry*)smaller;
			//This block will act as doubly linked list and set a previous and next node to NULL
                        (*small).previous = (*small).next = 0;
			//Assigning a size using pointer large to size other way data info
			(*small).size = malloc_size - sizeof(struct MemoryEntry);
			(*small).bool = 1;
			//This is becoming true after all memory assigned successfully
			//Act like a boolean and set it to true
			check = 1;
		}

		//Here checking the condition between comapre(300) and size which is given by inout test. 
                //if condition is true pointer p is starting pointing to the address of block which is created by small and pointer small is already pointing.
                //if condition is false pointer p is pointing to the adrees which one already kept by large pointer.		
		if(size<compare)
		   p= small;
		else
		   p= large;
		
		//This loop will keep going while the size is less than compare
		while(p != 0)
		{
                        //what ver the size assigned by a pointer p in struct MemoryEntery will check here 
			//if its a smaller than the real size which is consider by input test will execute if  
			if((*p).size < size)
			{	
				// the current size is smaller, go to next node
				p = (*p).next;
								
				// Here checking over time(saturation) 
				if (p == 0) 
				{
                                //This will shows the error that date is more than the final limit.
			    	errors(1,__FILE__,__LINE__);
				}
			}
			//If the first if will not true than command will come to elase if and checking its condition
			else if(!(*p).bool)
			{
				//check and go to the next node
				p = (*p).next;
				
			}
			//If previous two block's condition is not true than will check here and here will check the size which is kept by pointer p is less than iput test size and total struct MemoryEntry size
			else if((*p).size < (size + sizeof(struct MemoryEntry)))
			{
				//If condition is true initializing it to 0 means here making false 
				(*p).bool = 0;
				
				return (char*)p + sizeof(struct MemoryEntry);
			}
			//If previous condition is not true and command will come here directly and will create a head.
			else
			{
				//Take another q pointer of date type MemoryEntry and assiging a memory dynamically size of pointer p + size of struct + real size of input test
				q = (struct MemoryEntry*)((char*)p + sizeof(struct MemoryEntry) + size);

				//After this q is pointing to same as p otherway q will have a same address as what p has.				
                                (*q).previous = p;
				(*q).next = (*p).next;
				if((*p).next != 0)
				(*p).next->previous = q;
				(*p).next = q;
				(*q).bool = 1;
				//now size will change other way the the data info will set by subtraction p,strcut and original size of real input test
				(*q).size = (*p).size - sizeof(struct MemoryEntry) - size;
				//After p will get a original size of input test
				(*p).size = size;
				//Initializing by 0 and return total size
				(*p).bool = 0;
				return (char*)p + sizeof(struct MemoryEntry);
			}
		} 

		return 0;
	}


	// Free function
	void my_free(void *p)
	{
		//Here check the pointer is been freed is allocated or not 
		if ((p < (void*)bigger || p > ((void*)bigger + malloc_size)) && (p < (void*)smaller || p > ((void*)smaller + malloc_size))) 
		{	
			//Printing an error message that cannot free pointer because its not allocated
			errors(2,__FILE__,__LINE__);
			return;
		}
	
		struct MemoryEntry *a;
		
  		//Here check pointer p is a valid in bigger
		//Here TorF initializing by 0 and checking ture or false. 		
		int TorF = 0;

		//Assiging a memory which is in bigger[malloc_size] which is 5000 to the pointer 'a'.
		//So, from now 'a' will keep a address of that memory block which is making dynamically.		
		a = (struct MemoryEntry*)bigger;
		
		//Keep looping while the pointer is not equal to null or 0
		//Before that one time check the condition first if what p has and size of struct and 'a' will same than it will become true and go to the next node 
		//This same basic idea is also work in while loop.
          	if (p == (void*)a + sizeof(struct MemoryEntry)) 
			{
				TorF = 1;
				
			}
			//going into next node 
			a = a->next;
		while (a != 0){
			if (p == (void*)a + sizeof(struct MemoryEntry)) 
			{
				TorF = 1;
				break;
			}

			a = a->next;
		}

		//Here check pointer p is a valid in smaller
		//This is same as bigger 		
		a = (struct MemoryEntry*)smaller;

		//keep looping while the poiinter and meemory entery is not equal to null/0
		if (p == (void*)a + sizeof(struct MemoryEntry)) 
			{
				TorF = 1;
				
			}

			a = a->next;
           
		while (a != 0 && TorF == 0){
			if (p == (void*)a + sizeof(struct MemoryEntry)) 
			{
				TorF = 1;
				break;
			}

			a = a->next;
               }            

		//Here cheching whether pointer is returned by malloc or not 
		//
		if (!TorF) 
		{	
			//Here will print error message that cannot free pointer
			errors(3,__FILE__,__LINE__);
			return;
		}

		a = (struct MemoryEntry*)((char*)p - sizeof(struct MemoryEntry));

  		//Here chaning for the if allocatted memory is freeing twice or not if yes the will print error message
		if (a->bool) 
		{
			//Print error message that cannot free the pointer twice.
			errors(4,__FILE__,__LINE__);
			return;
		}
		
                struct MemoryEntry *b;
		//pointing a 'b' to a 'a' and also check for true or false 
		if((b = a->previous) != 0 && b->bool)
		{
			//Here mearge "b"'s node  with a previous node 
			b->size += sizeof(struct MemoryEntry) + a->size;
			a->bool=1;
			b->next = a->next;
			//if next to 'a' is not null then will keep addresing same as b
			if(a->next != 0)
				a->next->previous = b;
		}
		//Otherwise 'b' will keep aswaht 'a' has.
		else
		{
			a->bool= 1;
			b = a;	
		}
                struct MemoryEntry *c;

	
		if((c = a->next) != 0 && c->bool)
		{
			// Merge the current node with next node if it is free
			b->size += sizeof(struct MemoryEntry) + c->size;
			b->bool = 1;
			b->next = c->next;
			if(c->next != 0)
				c->next->previous=b;
		}
	}	
//This method will give a errors and what kind of errors and in which file and line number.
void errors(int i, char * file, int line)
{
   switch(i){
      case 1:
            printf("Error:oops!! Your data is exceeds the final limit. In file %s at line %d.\n",__FILE__,__LINE__);
             break;
      case 2:
           printf("Error:oops!! Cannot free pointer that was not allocated. In file %s at line %d.\n",__FILE__,__LINE__);
             break;
      case 3:
           printf("Error:oops!! Pointer is not returned by malloc. So, can't free the pointer. In file %s at line %d.\n",__FILE__,__LINE__);
             break;
      case 4:
           printf("Error:oops!! Worng Way it is. Cannot free the pointer twice. In file %s at line %d.\n",__FILE__,__LINE__);
             break;
       }
}

