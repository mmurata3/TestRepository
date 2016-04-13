#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

typedef int int32;
typedef unsigned char int8;

int8 *gen_modified_key(int8 modifier, const int8  *input_1, int32 length) {
   int8  *ret;
   int32 i_leading, i, xorValue;

   i = 0;
   i_leading = modifier/2;
   
   ret = (int8 *) malloc(length);
   if(ret == NULL){
      fprintf(stderr, "Memory allocation failure\n");
      exit(-1);
   }

   if( (modifier+1)%2 == 0 ) {
      xorValue = (int8)((i_leading<<4) + 8);
   } else {
      xorValue = (int8)(i_leading<<4);
   }   

   for(i=0; i<length; i++) {
      if(i%8==0){
         ret[i] = input_1[i] ^ xorValue;  
      } else {
         ret[i] = input_1[i];
      }
   }   
   return ret;
}   

// Do not change anything in main
// main only contains example input
// Change anything else
int main(int argc, char **argv) {
   // Example input data
   int8 data[32] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,
      17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
   int8 *resp = gen_modified_key(0x10, data, sizeof(data));
   free(resp);

   return 0;
}

