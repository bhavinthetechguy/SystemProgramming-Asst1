#ifndef malloc_h
#define malloc_h

#define malloc(x) my_malloc(x)
#define free(ptr) my_free(ptr)

//Here defining a malloc size which is giving in this assignment is 5000
#define malloc_size 5000
//compare value that comparing value with my input value and this and accordingly that program will execute 
#define compare 300

//Declaration of my_malloc and my_free mathod
void *my_malloc( unsigned int size );
void my_free( void * p );

//Making structure of MemoryEnter and using doubly linked list 
	struct MemoryEntry 
	{
		//This taking part data info in doubly linked list
		unsigned int size;
		//This taking part of boolean such as memory is allocated completly or not so its for true and false
		unsigned char bool;
		//This previous and next is for previous and next node in doubly linked list
		struct MemoryEntry *previous; 
                struct MemoryEntry *next;
	};

#endif 
