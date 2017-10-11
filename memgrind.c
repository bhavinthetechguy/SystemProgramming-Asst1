//Akshar Bhavin Assignment-1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

//This is a Demo Program to check mymalloc.c - if its working properly or not.
//This will exercise your memory allocator under a series of the different WorkLoads

//WorkLoad A - this will seperate 1000 mallocs of byte 1 then it will free it one by one.
void workLoadA(){
 //total memory
    char * myBlock[5000];
//struct timeval for starting time and end time
    struct timeval tv1, tv2; 
    int i,j,sCounter,cCount,fCounter,tFrees =0; 
//average time to calculate execute time
    long avgExTime =0; 
    int tMallocs = 0;
    long mult=0;
    long sub=0;
// this for loop will execute this test 100 times
    for (i=0; i<100; i++) 
	{
        //Get time from the strting point 
        gettimeofday(&tv1, 0); //default time
// this loop will run till we hit malloc 1000 , 1 byte each time
        for (j=0; j<1000; j++) 
	{
            //Assigning a 1 byte of memory block to myBlock 1 by 1 through 1000 times
            myBlock[j] = malloc(1); 
            //Incrementing in total malloc
            tMallocs++;
            //if total memmory is not null
            if (myBlock[j] != NULL)
	    {
               //Incrementing success memory counting and current count of memory 
               sCounter++;
                cCount++;
            }
        }
//this loop will free mallocs one bye one
        for (j = 0; j <cCount; j++) 
	{
            free(myBlock[j]);
            fCounter++;
            tFrees++;
        }
	cCount =0;
        //This is giving end time 
        gettimeofday(&tv2, 0); //default time
// math to calculate average time
	mult = mult + ((tv2.tv_sec-tv1.tv_sec)*1000000);
	sub =  sub +(tv2.tv_usec-tv1.tv_usec);
        avgExTime = (mult + sub);
	
    }
	avgExTime = (avgExTime/100);
   // printf("Total Mallocs:%d\n",tMallocs);
   // printf("Successful mallocs: %d\n", sCounter);
   // printf("Successful frees: %d\n", tFrees);

    printf("workLoad (A) Exucation Time: %ld microseconds.\n",avgExTime); 
    printf("workLoad (A) has been Exucated Successfully.\n");
}

//WorkLoad B will mallocs 1000, 1 byte and then it will free it immediately
void workLoadB(){
    // Assigning myBlock to null memory
    char * myBlock = NULL;
    //struct timeval for start time and end time
    struct timeval tv1, tv2;
    int i,j,sCounter,cCount,fCounter,tFrees =0;
    // average time to calculate execution time
    long avgExTime =0;
    long mult =0;
    long sub =0;
    int tMallocs = 0;
    //this for loop will run this workload 100 times
    for (i=0; i<100; i++) 
	{
        //getting the starting point
        gettimeofday(&tv1, 0);
        //this for loop will run till its hit 1000 mallocs
        for (j=0; j<1000; j++) 
	{
	    //assigning myBlock to 1 byte memory
            myBlock = malloc(1);
            // incrementing total mallocs by one 
            tMallocs++;
           //if myBlock is not equal to null 
            if (myBlock!= NULL)
	    {
		// freeing memory - myBlock
		free(myBlock);
                // incrementing Total frees and succesful free and current frees
               sCounter++;
		fCounter++;
                tFrees++;
            }
        }
        // getting the end time
        gettimeofday(&tv2, 0);
        // calculation to calculate average time for execution.
	mult = mult + ((tv2.tv_sec-tv1.tv_sec)*1000000);
	sub =  sub +(tv2.tv_usec-tv1.tv_usec);
        avgExTime = (mult + sub);
	
    }
    avgExTime = avgExTime/100;
   // printf("Successful mallocs: %d\n", sCounter);
   // printf("Total frees: %d\n", tFrees);
   // printf("Successful frees:%d\n", fCounter);
    printf("workLoad (B) Exucation Time: %ld microseconds.\n",avgExTime); 
    printf("workLoad (B) has been Exucated Successfully.\n");
}
// added this helper method for workload C and D
// we can set the starting and ending byte using this helper method
int pick(int min, int max)
{

    return ((double)rand() / (((double)RAND_MAX) + 1.0)) * (max-min+1) + min;
}
//Added this helper method for workload C and D
//delete the pointer index and shift all the values in the array at the end
void itemDelete( int in, int len, char ** a)
{
    int i;
    for (i = in; i < len - 1; i++ )
    {
         a[i] = a[i + 1];
    }
}
// this workload Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer - do this 1000 times
// Keep track of each operation so that you eventually malloc() 1000 bytes, in total
// Keep track of each operation so that you eventually free() all pointers
void workLoadC(){
    //Assigning myBlock to 1000 
    char * myBlock[1000];
    //struct timeval to get start and end time
    struct timeval tv1, tv2;
    int i;
    int mCounter = 0;
    int fCounter = 0;
    int tMallocs = 0;
    int sCounter = 0;
    int len = 0;
    //Average time to calculate execution time
    long avgExTime= 0;
    long mult =0;
    long sub =0;
//this for loop will run this workload 100 Times
    for ( i = 0; i < 100; i++)
	{
	//getting the starting time
       gettimeofday(&tv1, 0);
       // this while loop will run till its hit 1000
        while(mCounter < 1000)
	{
            //setting the minimum and maximum byte using helper method
            int p = pick(0, 1);
            // if p is equal 0
            if (p == 0){   
                //Assiging ptr to malloc 1 byte
                void * ptr = malloc(1);
                //incrementing total mallocs
                tMallocs++;
                //if ptr is not null
                if (ptr != NULL){
                    myBlock[len] = ptr;
                    len++;
                    sCounter++;
                }
                mCounter++;
             
            }
            //else statement if ptr is Null
            else {
		// if length is grether than 0
                if (len > 0){
 		//again using helper method to set minimum and maximum byte
                   int in = pick(0, len - 1);
		// freeing the memory - myBlock
                   free(myBlock[in]);
		  
                   char ** start = &myBlock[0];
		//using helper method to remove the pointer index and shift all the values in the array at the end
                      itemDelete(in, len, start);
		//decremeting the length and incrementing total free
                    len--;
                    fCounter++;
                }

            }
      
        }
	//while length is greather than 0
        while (len > 0){
            // using helper method to set minimum byte to 0 and maximum byte to length-1
            int in = pick(0, len - 1);
		//freeing myBlock-memory
            free(myBlock[in]);
            char ** start = &myBlock[0];
	//using helper method to remove the pointer index and shift all the values in the array at the end
	//decremeting the length and incrementing total free
            itemDelete(in, len, start);
            len--;
            fCounter++;
        }
        mCounter = 0;
	//getting the end time
        gettimeofday(&tv2, 0);
        // calculation to calculate average time of execution
        mult = mult + ((tv2.tv_sec-tv1.tv_sec)*1000000);
	sub =  sub +(tv2.tv_usec-tv1.tv_usec);
        avgExTime = (mult + sub);

    }
  	avgExTime  =avgExTime /100;
    printf("workLoad (C) Total mallocs: %d\n", tMallocs);
   // printf("Successful mallocs: %d\n", sCounter);
    printf("workLoad (C) Total Frees: %d\n", fCounter);
    printf("workLoad (C) Exucation Time: %ld microseconds.\n", avgExTime);
     printf("workLoad (C) has been Exucated Successfully.\n");
}
//This Workload will Randomly choose between a randomly-sized malloc() or free()ing a pointer
// Keep track of each malloc so that all mallocs do not exceed your total memory capacity
//Keep track of each operation so that you eventually malloc() 1000 times
//Keep track of each operation so that you eventually free() all pointers
// Choose a random allocation size between 1 and 64 bytes
void workLoadD(){
    //assigning myBlock to 1000 memory
    char * myBlock[1000];
    //struct timeval for start and end time
    struct timeval tv1, tv2;
    int i;
    int mCounter = 0;
    int fCounter = 0;
    int tMallocs = 0;
    int sCounter = 0;
    int len = 0;
 //average time to calculate execution time
    long avgExTime= 0;
    long mult =0;
    long sub =0;
    // this for loop will run this workload 100 times
    for ( i = 0; i < 100; i++)
	{
	//getting the start time
       gettimeofday(&tv1, 0);
	// while malloc is less than 1000
        while(mCounter < 1000)
	{
	    //using helper method to set minimum byte to 1 and maximum to 64
            int p = pick(1,64);	
		//if byte is greather than 1 and less than 64s
            if (p>=1 || p<=64){ 
		//picking random byte 1 and assigning to ptr
                void * ptr = malloc(1);
	//incrementing total mallocs
                tMallocs++;
	//if ptr is not null
                if (ptr != NULL){
                    myBlock[len] = ptr;
		//incrementing length 1 and success counter
                    len++;
                    sCounter++;
                }
                mCounter++;
             
            }
	//if p is not between 1 and 64
            else {
	//if length is greater than 0
                if (len > 0){
	//using helper method to set minimum byte to 1 and maximum to length-1
                   int in = pick(0, len - 1);
		//freeing myBlock
                   free(myBlock[in]);
                   char ** start = &myBlock[0];
			//using helper method to remove the pointer index and shift all the values in the array at the end
	//decremeting the length and incrementing total free

                      itemDelete(in, len, start);
                    len--;
                    fCounter++;
                }

            }
      
        }
		//while length is greater than 0
        while (len > 0){
            //using helper method to set minimum value to 0 and maximum to length -1
            int in = pick(0, len - 1);
		//freeing myBlock 
            free(myBlock[in]);
            char ** start = &myBlock[0];
	//using helper method to remove the pointer index and shift all the values in the array at the end
	//decremeting the length and incrementing total free
            itemDelete(in, len, start);
            len--;
            fCounter++;
        }
        mCounter = 0;
	//getting the end time
        gettimeofday(&tv2, 0);
	//calculating for average time execution
        mult = mult + ((tv2.tv_sec-tv1.tv_sec)*1000000);
	sub =  sub +(tv2.tv_usec-tv1.tv_usec);
        avgExTime = (mult + sub);

    }
  	avgExTime  =avgExTime /100;
    printf("workLoad (D) Total mallocs: %d\n", tMallocs);
    printf("workLoad (D) Successful mallocs: %d\n", sCounter);
    printf("workLoad (D) Successful Frees: %d\n", fCounter);
    printf("workLoad (D) Exucation Time: %ld microseconds.\n", avgExTime);
    printf("workLoad (D) has been Exucated Successfully.\n");

}
// Two workloads - (E) and (F) are my choosing
//This workload is to check if its any error if we try to free pointer twice
void workLoadE()
{	
	//average time to calculate execution time
	long avgExTime =0;
	long mult=0;
	long sub=0;
	int i;
	//struct timeval for starting and ending time
	struct timeval tv1,tv2;
	int *pointer;
	void *ptr;
        //this for loop will run this workload 100 times
	for(i=0;i<100;i++)
	{
          //getting the starting time
	  gettimeofday(&tv1, 0);
         //her i am trying to free pointer (x) twice
	 int *x = malloc(sizeof(int));
         free(x);
         free(x);
        //getting end time
	gettimeofday(&tv2, 0);
        //calculation to calculate avegate time of execution
	mult = mult + ((tv2.tv_sec-tv1.tv_sec)*1000000);
	sub =  sub +(tv2.tv_usec-tv1.tv_usec);
        avgExTime = (mult + sub);
	}
	avgExTime =avgExTime /100;
	printf("workLoad (E) Exucation Time:%1d microseconds.\n",avgExTime);
 
}
//trying to free the pointer that is not allocated
void workLoadF()
{
	int i;
        //average time to calculate execute time
	long avgExTime =0;
	long mult=0;
	long sub=0;
	//struct timeval for staring and end
	struct timeval tv1,tv2;
	int *y;
        //this for loop will run this workload 100 Times
	for(i=0;i<100;i++)
	{
	// getting the starting time
	  gettimeofday(&tv1, 0);
        // trying to free variable y that is not allocated
        free(y);
	//getting the end time
	gettimeofday(&tv2, 0);
        // calculation to calcute avergae time for execution
	mult = mult + ((tv2.tv_sec-tv1.tv_sec)*1000000);
	sub =  sub +(tv2.tv_usec-tv1.tv_usec);
        avgExTime = (mult + sub);
	}
	avgExTime =avgExTime /100;
	printf("workLoad (F) Exucation Time:%1d microseconds.\n",avgExTime);
}
//Extra Workload to see its generates error or not(given in assignment as an example)
/*
void workkLoadExtra()
{
	long mult=0;
	long sub=0;
	long avgExTime =0;
	struct timeval tv1,tv2;
	char *p;
	p = (char*)malloc(100);
	  gettimeofday(&tv1, 0);
        free( p );
        free( p );


	gettimeofday(&tv2, 0);
	mult = mult + ((tv2.tv_sec-tv1.tv_sec)*1000000);
	sub =  sub +(tv2.tv_usec-tv1.tv_usec);
        avgExTime = (mult + sub);
	avgExTime =avgExTime /100;
	printf("workLoad (Extra) Exucation Time:%1d microseconds.\n",avgExTime);
}*/



int main(int argc, char ** argv){

   if (argc != 1){
       printf("Incorrect Input");

   }
   else {	
	printf("\nTest result of Workloads A to F\n");
	printf("---------------------------------");
        printf("\nExecuting each workload (100) times\n");
        printf("\nworkLoad (A):1000 1 byte pointers one by one.\n");
        workLoadA();
        printf("\nworkLoad (B):1000 1 byte pointers immediately\n");
        workLoadB();
	printf("\nworkLoad (C):Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer.\n");
        workLoadC();
        printf("\nworkLoad (D):Randomly choose between a randomly-sized malloc() or free()ing a pointer.\n");
        workLoadD();
        printf("\nworkLoad (E):workloads of my choosing (1)(Execute 100 Times)\n");
        workLoadE();
	printf("\nworkLoad (F):workloads of my choosing (2)(Execute 100 Times)\n");
        workLoadF();
	/*printf("\nExtra Workloads that are given as example\n");
	printf("\nworkkLoadExtra: Redundant free()ing of the same pointer.\n");
	workkLoadExtra();*/
        printf("\n\n");
   }

    return 0;
  
}
