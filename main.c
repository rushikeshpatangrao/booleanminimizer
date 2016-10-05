#include<stdio.h>
#include<stdlib.h>
#define UNCHECK 10
#define CHECK 20
#define MATCH 30
#define MARK 40
#define NOVALUE 50

int nvar, mterms;
int *input;
int **ptr, **ptr1, **ptr2, **ptr3, **PI, **EssPI;
void putminterm(int, int); //function for input of minterms in arrays
int compare(int, int);     // function to commpare adjacent group minnterms until no match is possible and form an array of prime implicants
int removedup(int, int); // function to remove duplicates from the array of matched minterms
int BinaryToDecimal(int, int, int);
void EssentialPI(int, int); 
int main() {
	int i, value;
	int primeimp, mterm1, mterm2, mterm3;
	printf("enter the number of variables to be minimize\n");
	scanf("%d", &nvar);
	printf("enter the number of minterms\n");
	scanf("%d", &mterms);
	//taking input in the form of minterms
	printf("enter the minterms\n");
	input = (int *)malloc(mterms * sizeof(int));
	for(i = 0; i < mterms; i ++) {
		scanf("%d", &value);
		input[i] = value;
	}
	ptr1 = ptr = (int **)malloc(mterms * sizeof(int *));
	for(i = 0; i < mterms; i ++) {
		ptr1[i] = ptr[i] = (int *)malloc((nvar + 1) * sizeof(int));
	}
	putminterm(nvar, mterms);
	mterm1 = (mterms * (mterms + 1)) / 2;
	ptr2 = (int **)malloc(mterm1 * sizeof(int *));
	for(i = 0; i < mterm1; i ++) {
		ptr2[i] = (int *)malloc((nvar + 1) * sizeof(int));
	}	
	mterm2 = compare(nvar, mterms);
	mterm3 = removedup(nvar, mterm2);
	primeimp = BinaryToDecimal(nvar, mterms, mterm3);
	EssentialPI(primeimp, mterm3);
	
}
//function to place binary equivalent of the  minterm in  corresponding array 
//it puts an UNCHECK value at last of each binary minterm which will be updated later depending on its comparison with other minterms
void putminterm(int nvar, int mterms) {			//correct
	int i, j, value;
	for(i = 0; i < mterms; i ++) {
		value = input[i];
		for(j = nvar - 1; j >= 0 ; j --) {
			ptr1[i][j] = value % 2;
			value = value / 2;
		}
		
		ptr1[i][nvar] = UNCHECK;

	}
	
	
}
//function to compare groups of minterms in order to get prime immplicants
//it creates a [pointer of pointer] of  size [y * (y + 1)] / 2 as 
//for nC2 (2 selected out of n) = [y * (y - 1)] / 2
//and other y minterms if any of the commbination is not possible
//minterm1 = {[y * (y - 1)] / 2} + y = [y * (y + 1)] / 2
//the function will operate till any combination of minterms is nt possible
//it will put * value at the place where the minterms differ from each other 
int compare(int nvar,int mterms) {
	int index = 0, i, j, k, l, temp, index1;

//comparison begins 
	for(i = 0; i < (mterms - 1); i ++) {
		for(j = (i + 1); j < mterms; j ++) {
			temp = 0;
			for(k = 0; k < nvar; k ++) {
				if(ptr1[i][k] != ptr1[j][k]) {
					temp ++;
					index1 = k;
				}
			}
//the minterms in adjacent grops having identical binary values are placed together 
//value * is placed at the index where the minterms differ	
			if(temp == 1) {
				for(l = 0; l < index1; l ++) 
					ptr2[index][l] = ptr1[i][l];
				ptr2[index][index1] = MARK;
				for(l = (index1 + 1); l < nvar; l ++) 
					ptr2[index][l] = ptr1[i][l];
				
				ptr2[index][nvar] = UNCHECK;
				ptr1[i][nvar] = CHECK;
				ptr1[j][nvar] = CHECK;
				index ++;
			}
		}
	}
			
//putting the minterms that haven't found a match
	for(i = 0; i < (mterms); i ++) {
		if(ptr1[i][nvar] == UNCHECK) {
			for(j = 0; j <= nvar; j ++) {
				ptr2[index][j] = ptr1[i][j]; 
 			}
		index ++;
		}
	}
//chcking if any of the match is found in the current comparison 
//if not found we can return the index
//if found comparison will be continued
	temp = 0;
	for(j = 0; j < nvar; j ++) {
		if(ptr1[0][j] == ptr2[0][j]) 
			temp ++;
	}

//check if any match of minterms is happeed or not
//if not happened return the index
	if(temp == nvar) {

		return (index);
	}
	else {
		ptr1 = (int **)malloc(index * sizeof(int *));	
		for(j = 0; j < index; j ++)
			ptr1[j] = (int *) malloc((nvar + 1) * sizeof(int));
// copying content of ptr2 in ptr1			
		for(i = 0; i < index; i++) {
			for(j = 0; j <=nvar; j ++) {
				ptr1[i][j] = ptr2[i][j];
			}
		}
	compare(nvar, index);
	}
	
}
// function removes the duplicate prime implicants from the respective array			
//returns the value of finalised prime implicants
int removedup(int nvar, int mterm2) {
	int count, i, j, k;
	//comparison of prime implicants
	for(i = 0; i < (mterm2 - 1); i ++) {		
		for(j = (i + 1); j < mterm2; j ++) {
			count = 0;
			for(k = 0; k < nvar; k ++) {
				if(ptr1[i][k] == ptr1[j][k]) {
					count ++;
				}
			}
			if(count == nvar) {
				ptr1[j][nvar] = MARK;
			}
		}

	}
	count = 0;		
	for(i = 0; i < mterm2; i ++) {
		if(ptr1[i][nvar] != MARK) {					
				count ++;
		}
	}
	ptr3 = (int **)malloc(count * sizeof(int *));
	for(j = 0; j < count; j ++)
		ptr3[j] = (int *)malloc((nvar + 1) * sizeof(int));
	count = 0;		
	for(i = 0; i < mterm2; i ++) {
		if(ptr1[i][nvar] != MARK) {
			for(j = 0; j <= nvar; j ++) {
				ptr3[count][j] = ptr1[i][j];				

			}
			count ++;
		}
	}


	return count;
}
//this function write together the indices of prime impllicant and form an array which contains all the indices of prime implicants
//first calculate maximum number of minterms that can be grouped together to form a prime implicant 
//for this it makes use of the maximum number of MARKS present in a prime implicant which can be present in the first element of array ptr3
 
int BinaryToDecimal(int nvar, int mterms, int mterm3) {
	int value = 1, i, j, k, count, temp;

	for(j = 0; j < nvar; j ++) {
		if(ptr1[0][j] == MARK) {
			value = value * 2;
		}
	}

	PI = (int **)malloc(mterm3 * sizeof(int *));
	for(i = 0; i < mterm3; i ++)
		PI[i] = (int *)malloc(value * sizeof(int));
	for(i = 0; i < mterm3; i ++) {
		for(j = 0;j < value; j ++) {
			PI[i][j] = NOVALUE;
		}
	}
	for(i = 0; i < mterm3; i ++) {
		temp = 0;
		for(j = 0; j < mterms; j ++) {
			count = 0;
			for(k = 0; k < nvar; k ++) {
				if((ptr3[i][k] == ptr[j][k]) || (ptr3[i][k] == MARK)) {
					count ++;
				}
				if(count == nvar) {
					PI[i][temp] = input[j]; 
					temp ++;
				}
			}
		}
	}

	return value;
}	
void EssentialPI(int primeimp, int mterm3) {
	int i, j, m, n, count;
	EssPI = (int **)malloc(mterm3 * sizeof(int *));
	for(i = 0; i < mterm3; i ++)
		EssPI[i] = (int *)malloc((primeimp + 1) * sizeof(int));
	for(i = 0; i < mterm3; i ++) {
		for(j = 0; j < primeimp; j ++) {
			EssPI[i][j] = PI[i][j];
				
		}
		EssPI[i][primeimp] = 0;	
	}

	for(i = 0; i < mterm3; i ++) {
		for(j = 0; j < primeimp; j ++) {
			count = 0;
			if(EssPI[i][j] != MARK) {
				for(m = 0; m < mterm3; m ++) {
					if(i != m) {
						for(n = 0; n < primeimp; n ++) {	
							if(EssPI[i][j] == EssPI[m][n]) {
								count ++;
							}
						}
					}
					if(count == primeimp * (mterm3 - 1)) {
						EssPI[i][primeimp] = 1;
						count = 0;
					}
					else
						count = 0;
				}
			}
		}
	}
	for(i = 0; i < mterm3; i ++) {
		for(j = 0; j < primeimp; j ++) {
			printf("%d\t", EssPI[i][j]);
		}
	printf("\n");
	}
}
				
								












