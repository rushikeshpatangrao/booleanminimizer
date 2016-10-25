#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct chardata {
	char str[10];
	int top;
}chardata;

void cinitialize(chardata *product) {
	int i;
	product -> top = -1;

}

int cisempty(chardata *product) {
	if(product -> top == -1) 
		return 1;
	else
 		return 0;
}
int cisfull(chardata *product) {
	if(product -> top == 10)
		return 1;
	else 
		return 0;
}
void cpush(chardata *product, char ch) {
	product -> top ++;
	(product -> str)[product -> top] = ch;
}
char cpop(chardata *product) {
	char dummy;
	dummy = (product -> str)[product -> top];
	product -> top --;	
	return dummy;
}
char cremove(chardata *product, int pos) {
	char dummy;
	dummy = (product -> str)[pos];
	return dummy;
}
int cstacksize(chardata *product) {
	return ((product -> top) + 1);
}

	
