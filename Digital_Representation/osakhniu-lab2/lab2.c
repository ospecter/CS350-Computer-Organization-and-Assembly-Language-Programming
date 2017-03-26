// OKSANA SAKHNIUK


// Compile this file on fourier.cs.iit.edu with gcc -Wall -std=c99 -lm -o lab2 lab2.c

// CS 350, Spring 2017
// Lab 2: Digital Representations
//
// Illinois Institute of Technology, (c) 2017, Kyle C. Hale
//
// See the functions that say "YOU WILL FINISH WRITING..."
// It is your job to finish these functions. To see how to start,
// read the comments before the functions. Note that your output
// will be tested with cases that are not in the comments.
//
// Code that does not compile will get a zero!
//
// You will be given points based on the number of test cases passed
// for each of your functions.
//

#define _GNU_SOURCE
#include <stdlib.h> // standard library functions
#include <stdio.h>  // to access printf, scanf
#include <math.h>   // to access sqrt (be sure to compile with -lm for math library)
#include <unistd.h> // used here for "getopt" (argument parsing)
#include <getopt.h> // also used for "getopt"
#include <string.h> // string functions 
#include <ctype.h>  // provides "isprint()" routine

#define MAX_STR_LEN 64


// YOU WILL FINISH WRITING THIS FUNCTION
//
// You are given an ASCII string which you can 
// assume is NULL terminated (ends with a '0')
// Go through character by character in this string and
// convert the letters to capital versions. If a letter
// is already in caps, keep it that way. Non-alphabetic 
// characters you should ignore. 
//
// The result should be stored in "newstring," which
// is returned from the function.
//
// ./lab2 -c capitalizeme
//
// Your program should print out:
// CAPITALIZEME
//
// If I give you 
//
// ./lab2 -c 01bbbZzZz
//
// I should get 
//
// 01BBBZZZZ
//
// Note the C macro above, there is a maximum string length.
// You should ignore any 
// HINT: use the ASCII code chart linked on the website
// 
static char *  // <-- this function returns data of type char* (a memory address that contains characters)
capitalize (char * string) 
{
	// get the length of the string, only up to MAX_STR_LEN characters
	// (there is another function, strlen, which does the same thing but
	// blindly keeps counting until it hits a null terminator. Do not use this function ever
	// Note the "+ 1." This is because we want to include space for a null terminator in our
	// new string. Strnlen does not count it, so we explicitly add one.
	unsigned len = strnlen(string, MAX_STR_LEN) + 1; 

	// we must make space for our new string. In C, we do this using "malloc," short
	// for "memory allocate." "len" is the number of bytes to allocate. 
	char * newstring = malloc(len);

	// normally I'd check here to see if I failed to allocate memory. Not going to 
	// bother here since we should never run out of memory if we're allocating <= 65 bytes!
	
	// we set the memory to zero using the memset routine;
	memset(newstring, 0, len);

	// YOU FILL THE REST IN
	// treat newstring like an array. For example, to copy the old string
	// I might write
	// int i;
	// for (i = 0; i < len; i++) {
	// 	newstring[i] = string[i];
	// 	}
	// Remember your goal is to capitalize letters
	

	// FILL ME IN
	int i;
	for (i=0;i<len;i++){
	newstring[i]=string[i];
	if ((newstring[i]>96) && (newstring[i]<123))
		newstring[i]=newstring[i]-32;
	}


	return newstring;
}


// YOU WILL FINISH WRITING THIS FUNCTION
//
// This function accepts a 32-bit *unsigned* integer as
// its argument. You should print this integer out as
// a 32-bit binary number. You should explictly pad to
// the left with zeros (use all 32 bits). Your number
// should have the least significant bit furthest to the right
//
// For example, if I provide 
//
// ./lab2 -b 10
//
// You should print out:
// 00000000000000000000000000001010
//
// I can also provide my input in hex format:
//
// ./lab2 -b 0xffff0001
// 11111111111111110000000000000001
//
// ./lab2 -b 0x01234567
// 00000001001000110100010101100111
//
//./lab2 -b 0xdeadbeef
// 11011110101011011011111011101111
//
// HINT: consider using shifts (<< and/or >>)
// HINT: you will want to use printf
// HINT: don't forget to put a newline after your bits!
//
static void
to_binary (unsigned n) 
{	

	int i;
	long unsigned int k;
//	printf("size of n: %d bits\n",sizeof(n)*8);
	for (i=31; i>=0;i--)
	{
	 //	printf("i=%d", i);
		k=n>>i;
		if (k & 1)
		printf("1");
		else
		printf("0");
	}	// FILL ME IN
	
	printf("\n");	
	return;
}


// YOU WILL FINISH WRITING THIS FUNCTION
//
// This function accepts a *signed* 32-bit integer.
// You are meant to return the number with all the bits
// flipped. You do not need to print it (the printing will 
// be done for you).
//
// HINT: a certain logical operator will help here
//
static int 
flip_bits (int x)
{
	long unsigned flipped= x ^0xffffffff;			
 // FILL ME IN

	return flipped; // you will change this to return something else
}


static void
usage (char * prg)
{
	printf("\nUsage: %s [-c <string> | -f <int> | -b <int>]\n", prg);
	printf("    -c option expects a string to capitalize\n");
	printf("    -f option expects an integer whose bits will be flipped\n");
	printf("    -b option expects an integer which will be printed in binary\n");
	printf("\n");
}


int 
main (int argc, char ** argv) 
{
	int c;
	char * string;
	int flipee;
	unsigned b;


	opterr = 0;

	if (argc < 2) { 
		usage(argv[0]);
		return 1;
	}

	while ((c = getopt(argc, argv, "f:b:c:")) != -1) { 
		switch (c) {
			case 'f':
				flipee = strtol(optarg, NULL, 0);
				printf("0x%08x\n", flip_bits(flipee));
				break;
			case 'b':
				b = (unsigned)(strtol(optarg, NULL, 0));
				to_binary(b);
				break;
			case 'c':
				string = optarg;
				printf("%s\n", capitalize(string));
				break;
			case '?': {
						  if (optopt == 'c' || optopt == 'b' || optopt == 'f') {
							  fprintf(stderr, "Option '-%c' requires an argument!\n", optopt);
							  usage(argv[0]);
							  return 1;
						  } else if (isprint(optopt)) {
							  fprintf(stderr, "Unknown option '-%c'\n", optopt);
							  usage(argv[0]);
							  return 1;
						  } else {
							  fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
							  usage(argv[0]);
							  return 1;
						  }
					  }
			default:
					  usage(argv[0]);
					  return 1;
		}
	}

	
	return 0;
}
