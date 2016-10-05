#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define INPUT 4
#define MAX_SIZE 2048
typedef struct data {
	char **str;
	int top;
}data;

void initialize(data *product) {
	int i;
	product -> top = -1;
	product -> str = (char **)malloc(MAX_SIZE * sizeof(char *));
	for(i = 0; i < MAX_SIZE; i ++) {
		(product -> str)[i] = (char *)malloc(10 * sizeof(char));
	}

}

int isempty(data *product) {
	if(product -> top == -1) 
		return 1;
	else
 		return 0;
}
int isfull(data *product) {
	if(product -> top == MAX_SIZE)
		return 1;
	else 
		return 0;
}
void push(data *product, char *str) {
	if(!isfull(product)) {
		product -> top ++;
		strcpy((product -> str)[product -> top], str);
	}
	else
		return;
}
char *pop(data *product) {
	char *dummy;
	dummy = (char *)malloc(11 * sizeof(char));
	if(!isempty(product)) {
		strcpy(dummy, (product -> str)[product -> top]);
		product -> top --;	
		return dummy;
	}
	else
		return NULL;
}	
int stacksize(data *product) {
	return ((product -> top) + 1);
}

int readline(char *arr) {
	int i = 0;
	char ch;
	while((ch = getchar()) != '\n') {
		arr[i] = ch;
		i ++;
	}
	arr[i] = '\0';
	return i;
}
int *convert_to_binary(char *str,int size) {
	int *arr;
	int flag = 0, i, len;
	char ch;
	arr = (int *)malloc(50 * sizeof(int));
	for(i = 0; i < 50; i ++) 
		arr[i] = -1;
	len = strlen(str);
	
	for(i = 0; i < len; i ++) {
		if(((ch = str[i]) >= 65) && ((ch = str[i]) <= 90)) {
			if(flag == 1) {
 				arr[ch - 'A'] = 0;
				flag = 0;
			}
			else 
				arr[ch - 'A'] = 1;
		}
		else if((ch = str[i]) == 126) {
			flag = 1;
		}
	}
	for(i = 0; i < size; i ++) {
		if(arr[i] == -1) {
			arr[i] = 1;
		}
	}		
	return arr;
}
int compare(int *arr, int *binary, int len) {
	int count = 0, i;
	for(i = 0; i < len; i ++) {
		if(arr[i] == binary[i]) {
			count ++;
       		}
	}
	if(count == len) {
		return arr[len];
	}
	else
		return -1;
}
int main() {
	char str[2048];
	char *substr;
	substr = (char *)malloc(50 * sizeof(char));
	int minterms[1024];
	int **binary;
	int rows, columns, i, j, len, minterm, size;
	char ch;
	data product;
	initialize(&product);
	binary = (int **)malloc(1024 * sizeof(int *));
	for(i = 0; i < 1024; i ++) {
		binary[i] = (int *)malloc(10 * sizeof(int));
	}

	columns = INPUT;
	rows = pow(2, columns);
	int arr[rows][columns + 1];
	for(i = 0; i < rows; i ++) {
		for(j = 0; j <= columns; j ++) {
			if(j == columns) 
				arr[i][j] = i;
			else
				arr[i][columns - j - 1] = (i >> j) & 1;
		}
	}
	printf("enter the boolean expression\n");
	len = readline(str);
	for(i = 0; i < len; i ++) {
		j = 0;			
		while(str[i] != '+') {
			if((((ch = str[i]) >= 'A') && ((ch = str[i]) <= 'Z')) || ((ch = str[i]) == '~')) {
				substr[j] = str[i];
				j ++;
				i ++;
			}
			else 
				i ++;
		}
		substr[j] = '\0';
		push(&product, substr);
	}
	size = stacksize(&product);
	for(i = 0; i < size; i ++) {
		minterm = -1;
		substr = pop(&product);
		binary[i] = convert_to_binary(substr, INPUT);
		j = 0;
		while(minterm == -1) {
			minterm = compare(arr[j], binary[i], INPUT);
			j ++;
		}
		minterms[i] = minterm;
	}
	for(i = 0; i < size; i ++) {
		printf("%d", minterms[i]);
	}
	return 0;
}
    			





