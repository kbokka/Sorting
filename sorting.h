#ifndef __sorting_h_
#define __sorting_h_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Constant Definitions

/* Return/Error Codes */
#define OK               (  0 )  // No errors, everything as should be
#define ERROR            ( -1 ) // Generic error

// structures
  
/* Function Prototypes */
long *Load_File(char *Filename, int *Size);
int Save_File(char *Filename, long *Array, int Size);
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Save_Seq1(char *Filename, int Size);
void Save_Seq2(char *Filename, int Size);
#endif  // __sorting_h_ 

