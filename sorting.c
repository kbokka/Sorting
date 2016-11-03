#include <stdlib.h>
#include "sorting.h"
#include <stdio.h>

//load file function
long *Load_File(char *Filename, int *Size) {
	if(Filename == NULL) {
		fprintf(stdout, "\nNo filename specified.");
		return NULL;
	}
	long *array = NULL;
	int i = 0;
	long int num = 0;
	FILE *fptr = NULL;
	//check to see if file opens
	fptr = fopen(Filename, "r");
	if(fptr == NULL) {
		fprintf(stdout, "Error reading input file.");
		return NULL;
	}

	//put file data into array 
	fscanf(fptr, "%d", Size);
	array = malloc((*Size)*(sizeof(long)));
	while(fscanf(fptr,"%li", &num) == 1) {
		array[i] = num;
		i++;
	}
	fclose(fptr);
	return array;
}

//save file function
int Save_File(char *Filename, long *Array, int Size) {
	if(Filename == NULL) {
		fprintf(stdout, "\nNo output filename specified");
		return -1;
	}
	if(Array == NULL) {
		fprintf(stdout, "\nNo Array");
		return -1;
	}

	FILE *fptr = NULL;
	int i = 0;
	int count = 0; //total number of numbers saved to file 
	
	//create file to write data into  
	fptr = fopen(Filename, "w");
	if(fptr == NULL) {
		fprintf(stdout, "\nCannot write to file");
		return count;
	}
	//write data into file 
	while(Size != 0) {
		fprintf(fptr, "%li", Array[i]);
		fprintf(fptr, "\n");
		count++;
		i++;
		Size--;
	}
	fclose(fptr);
	return count;
}

//Shell Sort algorithm 
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move) {
	//check to see if input array is null
	if(Array == NULL) {
		return;
	}

	if(Size == 0) {
		fprintf(stdout, "\nArray Size is 0, please input array with elements in it.");
		return;
	}

	int *seq1 = NULL;
	int p2 = 0;
	int p3 = 0;
	int a2 = 0;
	int a3 = 0;
	int counter = 0;//tracks the last index of seq1
	int gap = 0;
	int i = 0; 
	int check = 0; 
	int comp = 0;
	int move = 0;
	long int temp = 0;
	int k = 0;
	int j = 0;
	
	//check to see if array is already sorted
	for(i = 0; (i < (Size - 1)) && (check == 0); i++) {
		if(Array[i] > Array[i+1]) {
			check = 1;
		}
		comp++;
	}
	
	if(check == 0) {
		*N_Comp = comp;
		*N_Move = move;
		return;
	}
	
	//generate seq1 
	i = 0;
	seq1 = (int*)malloc(sizeof(int)*Size);
	if(seq1 == NULL) {
		fprintf(stdout, "\nCannot generate seq1.");
		return;
	}	
	seq1[i] = 1;
	i++;
	while(seq1[i - 1] < Size) {
		//printf("%d, ", seq1[i-1]);
		if((seq1[p2] * 2) == (seq1[i - 1])) {
			p2++;
		}
		if((seq1[p3] * 3) == (seq1[i - 1])) {
			p3++;
		}
		a2 = seq1[p2] * 2;
		a3 = seq1[p3] * 3;
		if(a2 < a3) {
			p2++;
			seq1[i] = a2;
		}
		else {
			p3++;
			seq1[i] = a3;
		}
		if(seq1[i] > Size) {
			break;
		}
		i++;
		counter = i;
	}
	//iterate through seq1 in descending order 
	for(i = (counter - 1);i >= 0; i--) {
		gap = seq1[i];
		//printf("%d, ", i);
		//shell sort algorithm 
		for(j = gap; j < Size; j++) {
			temp = Array[j];
			k = j;
			move++;
			while((k >= gap) && (Array[k-gap] > temp)) {
				Array[k] = Array[k-gap];
				k = k - gap;
				comp++;
				move++;
			}
			Array[k] = temp;
			move++;
		}
	}

	*N_Move = move;
	*N_Comp = comp;
	free(seq1);	
}

//Bubble Sort Algorithm
void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move) {
	//check to see if input array is null
	if(Array == NULL) {
		fprintf(stdout, "\n No input array.");
		return;
	}
	if(Size == 0) {
		fprintf(stdout, "\n Size is 0 please input array with values.");
		return;
	}
	
	int move = 0;
	int comp = 0;
	int check = 0;
	int i = 0;
	//check to see if array is already sorted
	for(i = 0; (i < (Size - 1)) && (check == 0); i++) {
		if(Array[i] > Array[i + 1]) {
			check = 1;
		}
		comp++;
	}
	if(check == 0) {
		*N_Move = move;
		*N_Comp = comp;
		return;
	}
	int power = 2;//exponent for seq2 generator 
	int* seq2 = NULL;
	int temp = 0;
	int gap = 0;
	int counter = 0;//holds the last index of seq2 
	int j = 0; 
	int k = 0;
	int prev = Size / 1.3; 
	//genearte seq2 in the {N/1.3, N/(1.3)^2,...1} format
	i = 0;
	seq2 = (int*)malloc(sizeof(int)*Size);
	if(seq2 == NULL) {
		fprintf(stdout, "\nCannot allocate space for seq2");
	}
	seq2[i] = (int)(Size / 1.3);
	while(seq2[i] != 1) {
		//temp = (int)(Size / pow(1.3, power));	
		temp = (int)(prev / 1.3);
		if((temp == 9) || (temp == 10)) {
			temp = 11;
		}
		
		i++;
		seq2[i] = temp;
		prev = temp;
		power++;
	}
	counter = i;
	//improved bubble sort algo using seq1 for gap
	for(i = 0; i < (counter + 1); i++) {
		//getting the values of seq2 
		gap = seq2[i];	
		//printf("%d, ", gap);
		//improved bubble sort algo
		for(j = 0, k = gap; k < Size; j++, k++) {

			if(Array[j] > Array[k]) {
				temp = Array[k];
				Array[k] = Array[j];
				Array[j] = temp;
				move = move + 3;
			}
			comp++;
			
		}
	}
	//gurrantees sorting
	k = 1;
	int flag = 0; 
	for(j = 0; k < Size; j++) {
		if(Array[j] > Array[k]) {
			temp = Array[k];
			Array[k] = Array[j];
			Array[j] = temp;
			move += 3;
			flag = 1;
		}
		comp++;
		k++;
	}

	for(i = 0; i < (Size - 1); i++) {
		if(Array[i] > Array[i+1]) {
			flag = 1;
			break;
		}
	}

	if(flag == 1) {
		k = 1;
		for(j = 0; k < Size; j++) {
			if(Array[j] > Array[k]) {
				temp = Array[k];
				Array[k] = Array[j];
				Array[j] = temp;
				flag = 2;
				move += 3;
			}
			k++;		
		}
		comp++;
	}
	
	if(flag == 2) {
		k = 1;
		for(j = 0; k < Size; j++, k++) {
			if(Array[j] > Array[k]) {
				temp = Array[k];
				Array[k] = Array[j];
				Array[j] = temp;
				move +=3;
			}
		}
		comp++;
	
	}
	free(seq2);
	*N_Move = move;
	*N_Comp = comp;
}

void Save_Seq1(char *Filename, int Size) {
	if(Filename == NULL) {
		fprintf(stdout, "\nNo filename given.");
		return;
	}
	FILE *fptr = NULL;
	int i = 0;
	int counter = 0;
	int p2 = 0;
	int p3 = 0;
	int a2 = 0;
	int a3 = 0;
	int *seq1 = NULL;
	fptr = fopen(Filename, "w");
	if(fptr == NULL) {
		fprintf(stdout, "\nCannot Open file.");
		return;
	}

	i = 0;
	seq1 = (int*)malloc(sizeof(int)*Size);
	if(seq1 == NULL) {
		fprintf(stdout, "\nCannot generate seq1.");
		return;
	}	
	seq1[i] = 1;
	i++;
	while(seq1[i - 1] < Size) {
		//printf("%d, ", seq1[i-1]);
		if((seq1[p2] * 2) == (seq1[i - 1])) {
			p2++;
		}
		if((seq1[p3] * 3) == (seq1[i - 1])) {
			p3++;
		}
		a2 = seq1[p2] * 2;
		a3 = seq1[p3] * 3;
		if(a2 < a3) {
			p2++;
			seq1[i] = a2;
		}
		else {
			p3++;
			seq1[i] = a3;
		}
		if(seq1[i] > Size) {
			break;
		}
		i++;
		counter = i;
	}

	while(counter != 0) {
		fprintf(fptr, "%d", seq1[counter]);
		fprintf(fptr, "\n");
		counter--;
	}
	fprintf(fptr, "%d", seq1[counter]);

	fclose(fptr);		
	free(seq1);
}

void Save_Seq2(char *Filename, int Size) {
	if(Filename == NULL) {
		fprintf(stdout, "\nNo filename to write too.");
		return;
	}

	FILE *fptr = NULL;
	int *seq2 = NULL;
	int i = 0;
	fptr = fopen(Filename, "w");
	if(fptr == NULL) {
		fprintf(stdout, "\nCannot Open file.");
		return;
	}

	i = 0;
	seq2 = (int*)malloc(sizeof(int)*Size);
	if(seq2 == NULL) {
		fprintf(stdout, "\nCannot generate seq1.");
		return;
	}
	int temp = 0;
	int counter = 0;//holds the last index of seq2 
	int prev = Size / 1.3;
	//genearte seq2 in the {N/1.3, N/(1.3)^2,...1} format
	i = 0;
	seq2[i] = (int)(Size / 1.3);
	while(seq2[i] != 1) {
		temp = (int)(prev / 1.3);				
		if((temp == 9) || (temp == 10)) {
			temp = 11;
		}
		i++;
		seq2[i] = temp;
		prev = temp;
	}
	counter = i;
	for(i = 0; i < (counter + 1); i++) {
		fprintf(fptr, "%d", seq2[i]);
		fprintf(fptr, "\n");
	}

	fclose(fptr);		
	free(seq2);

}


