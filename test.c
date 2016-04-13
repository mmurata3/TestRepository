/*
added comment here
Michael,

   Thanks for taking the time to sit in on our info session.  I hope it gave you a good understand of what Futurex does and how everything fits together.  I’ve attached the code sample mentioned during the webinar.  Please review the code and provide your input on the following questions: 

   1.  What does the function gen_modified_key do?
   2.  What problems or issues, if any, do you see with it?
   3.  How could you improve the function, and what benefits would your improvements make?
   4.  What other additional improvements could you make to the rest of the code? 

   In addition to answering the above questions in your response, we would also like you to re-write the code to incorporate your improvements. I would like to point out that the code is intentionally flawed and not indicative of our overall code quality. We would like you to improve it to make the function more efficient while ensuring the input parameters are the same, and the output matches what it would have been before your changes. We are looking for you to only make efficiency improvements, not changes related to security or functionality.

   There is not a set time limit for this exercise, but it’s not meant to be extensive.

   If you have any questions, feel free to reach out to me.

   Regards,
   Dee
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

typedef int int32;
typedef unsigned char int8;

static void integrate_arrays(int8  *output, int8  *input_1, const int8  *input_2, int32 length)
{
   int32 i = 0;

   for(i=0; i<length; i++) //length = 8 in this loop, this func called 4 times
   {
      output[i] = (int8)(input_1[i] ^ input_2[i]);
   }

   return;
}

static void itoa( int32 num, int8  *alpha, int32 radix )
{
   if( radix == 10 )
   {
      sprintf(alpha, "%i", num);
   }
   else if( radix == 16 )
   {
      sprintf(alpha, "%X", num);
   }
}

int8 *gen_modified_key(int8 modifier, const int8  *input_1, int32 length)
{
   int8  leading[3];
   int32 i_leading;
   int8 * temp_string = NULL;
   int8 * ret;
   int32 i = 0;

   itoa(modifier/2, leading, 10);		// 16/2
   i_leading = atoi(leading);			// 8
   temp_string = (int8 *) malloc(8);	// 8 unsigned char *
   ret = (int8 *) malloc(length);		// 32 unsigned char *
   memset(temp_string, 0, 8);			// 8 leading 0's
   temp_string[0] = 0; 				

   if( (modifier+1)%2 == 0 ) {			// is it even?	
      temp_string[0] = (int8)((i_leading<<4) + 8);	//(8<<4) = 128 + 8 = 136
   }   
   else {
      temp_string[0] = (int8)(i_leading<<4);			//(8<<4) = 128
   }   

   for(i=0; i<(length>>3); i++) //(32>>3) = 4
   {
      integrate_arrays(ret+i*8, temp_string, input_1+i*8, 8);
   }   
   free(temp_string);
   return ret;
}   

// Do not change anything in main
// main only contains example input
// Change anything else
int main(int argc, char **argv) {
   int i;
   struct timeval tv1, tv2;

   gettimeofday(&tv1, NULL);

   // Example input data
   int8 data[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,
      17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
   int8 *resp = gen_modified_key(0x10, data, sizeof(data));
   for(i=0; i < 32; i++){
      printf("%X ", resp[i]);
   }
   printf("\n");
   free(resp);

   gettimeofday(&tv2, NULL);

   printf("total time = %f seconds\n", 
         (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +\
         (double)(tv2.tv_sec - tv1.tv_sec));

   return 0;
}

