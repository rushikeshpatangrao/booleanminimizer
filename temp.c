#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include<stdlib.h>
#include "cstack.h"

#define NMAX 10
#define UNCHECK 10
#define CHECK 20
#define MATCH 30
#define MARK 40
#define NOVALUE 50
#define CHARMAX 1000



int nvar, mterms, mterm3, prime;
int *input;
int **ptr, **ptr1, **ptr2, **ptr3, **PI, **EssPI, ***temp, ****step;
/*void putminterm(int, int); //function for input of minterms in arrays
int compare(int, int);     // function to commpare adjacent group minnterms until no match is possible and form an array of prime implicants
int removedup(int, int); // function to remove duplicates from the array of matched minterms
int BinaryToDecimal(int, int, int);
void EssentialPI(int, int); 
void printstep1();
int combination(int, int);*/


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


int combination(int n, int r) {
	int a, b, c, i, res = 0;
	a = n;
	b = n - r;
	c = r;
	if(n == r || b == 0) {
		return 1;
	}
	for(i = 0; i < (n - 1); i ++) {
		if((b - i) < 1) {
			b = i + 1;
			
		}
		if((c - i) < 1) {
			c = i + 1;
		}
		res = res + (a - i) / ((b - i) * (c - i));
		
	}
	return res;
}


	
void printstep1() {
	int i, j, count, k, l, decimal;

	for(i = 0; i <= nvar; i ++) {
		for(j = 0; j < combination(nvar, i); j ++) {
			for(k = 0; k <= nvar; k ++) {
				temp[i][j][k] = -1;
			}
		}
	}
	int term[nvar + 1];
	for(i = 0; i <= nvar; i ++) 
		term[i] = 0;
	for(i = 0; i < mterms; i ++) {
		count = 0;

		for(j = 0; j < nvar ; j ++) {
			if(ptr1[i][j] == 1) {
				count ++;
			}
		}

		for(j = 0; j < nvar; j ++) {
			temp[count][(term[count])][j] = ptr1[i][j];
		}
		term[count] ++;
	}

	for(i = 0; i <= nvar; i ++) {
		for(j = 0; j < combination(nvar, i); j ++) {
			decimal = 0;
			for(k = 0; k < nvar; k ++) {
				if(temp[i][j][k] == -1) 
					break;
				decimal = decimal + temp[i][j][k] * pow(2, (nvar - k - 1));
			}
			temp[i][j][nvar] = decimal;
		}
	}
	for(i = 0; i <= nvar; i ++) {
		for(j = 0; j < combination(nvar, i); j ++) {
			for(k = 0; k <= nvar; k ++) {
				if(temp[i][j][k] == -1)
					break;
				step[0][i][j][k] = temp[i][j][k];
			}
		}
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

	static int currstep = 0;
	currstep ++;
	int index = 0, i, j, k, l, temp, index1, count;
	int arr[nvar + 1];
	for(i = 0; i <= nvar; i ++) {
		arr[i] = 0;
	}
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
/*	for(i = 0; i < index; i ++) {
		for(j = 0; j <= nvar; j ++) {
				printf("%d\t", ptr2[i][j]);
 			}
			printf("\n");
	}
	printf("__________________________________\n");	*/
	for(i = 0; i < index; i ++) {
		count = 0;
		for(j = 0; j <= nvar; j ++) {
			if(ptr2[i][j] == 1)
				count ++;
		}
		for(j = 0; j <= nvar; j ++) {
		step[currstep][count][arr[count]][j] = ptr2[i][j]; 	
		}
		arr[count] ++;
	}
/*	printf("step %d\n" , currstep);
	for(j = 0; j <= (nvar - currstep); j ++) {
		for(k = 0; k < NMAX; k ++) {
			for(l = 0; l <= nvar; l ++) {
				printf("%d\t", step[currstep][j][k][l]);
			}
		printf("\n");
		}
	printf("______________________________\n");
	}
*/
	
		
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
	index = compare(nvar, index);
	return index;
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
 
int BinaryToDecimal(int nvar, int mterms) {
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
void EssentialPI(int primeimp) {
	int i, j, m, n, count;
	EssPI = (int **)malloc(mterm3 * sizeof(int *));
	for(i = 0; i < mterm3; i ++)
		EssPI[i] = (int *)malloc((primeimp + 1) * sizeof(int));
	for(i = 0; i < mterm3; i ++) {
		for(j = 0; j < primeimp; j ++) {
			EssPI[i][j] = PI[i][j];
				
		}
		printf("\n");
		EssPI[i][primeimp] = 0;	
	}
	prime = primeimp;
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

}
int *findminterms(int *p) {
	int nterms = pow(2, nvar);
	int *arr;
	int i, j, k;
	arr = (int *)malloc(nterms * sizeof(int));
	int count, tmp;
	for(i = 0; i < nterms; i ++) {
		arr[i] = -1;
	}
	tmp = 0;
	for(j = 0; j < mterms; j ++) {
		count = 0;
		for(k = 0; k < nvar; k ++) {
			if((p[k] == ptr[j][k]) || (p[k] == MARK)) 
				count ++;
		}
		if(count == nvar) {
			arr[tmp] = input[j]; 
			tmp ++;
		}
	}

	return arr;
}	
void essential_prime_implicant (GtkButton* widget, GtkWidget* pWindow) {	
	static int flag = 0;
 	GtkWidget *popup_window, *lable, *table, *button, *vbox;

	popup_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (popup_window), "Pop Up window");
	gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
	gtk_window_set_resizable (GTK_WINDOW (popup_window), TRUE);

	gtk_widget_set_size_request (popup_window, 600, 800);
	//gtk_window_set_transient_for (GTK_WINDOW (popup_window), GTK_WINDOW (pWindow));
	gtk_window_set_position (GTK_WINDOW (popup_window), GTK_WIN_POS_CENTER);
	table = gtk_table_new((prime + 2), (mterms + 4), 0);

	int i, j, k;
	lable = gtk_label_new("PI Terms");
	gtk_table_attach(GTK_TABLE(table), lable, 0, 2, 0, 1, GTK_FILL, GTK_FILL, 50, 10);
	

	chardata var;
	cinitialize(&var);
	char *string[mterm3];
	for(i = 0; i < mterm3; i ++) {
		string[i] = (char *)malloc(20 * sizeof(char));
	}
	char ch;
	int n;
	for(i = 0; i < nvar; i ++) {
		if(!cisfull(&var)) {
			ch = 'A' + i;
			cpush(&var, ch);
		}
	}

	for(i = 0; i < mterm3; i ++) {
		n = 0;
		for(j = 0; j < nvar; j ++) {
			if(ptr3[i][j] != 40) {
				if(ptr3[i][j] == 1) {
					string[i][n] = cremove(&var, j);
					n ++;
				}
				else if(ptr3[i][j] == 0) {
					string[i][n] = '~';
					n ++;
					string[i][n] = cremove(&var, j);
					n ++;
				}
			}
		}
		string[i][n] = '\0';			
		lable = gtk_label_new(string[i]);
		gtk_table_attach(GTK_TABLE(table), lable, 0, 2, i + 2, i + 3, GTK_FILL, GTK_FILL, 50, 10);
					
	}



	lable = gtk_label_new("Decimal numbers");
	gtk_table_attach(GTK_TABLE(table), lable, 2, 4, 0, 1, GTK_FILL, GTK_FILL, 50, 10);

	char *prime_str[mterm3];

	for(i = 0; i < mterm3; i ++) {
		prime_str[i] = (char *)malloc(prime * sizeof(char));
	}
	for(i = 0; i < mterm3; i ++) {
		strcpy(prime_str[i], "\0");
	}
	k = 0;
	char buffer[5];
	int tmp;
	buffer[0] = '\0';
	for(i = 0; i < mterm3; i ++) {
		tmp = 0;
		for(j = 0; j < prime; j ++) {
			if(PI[i][j] != NOVALUE) {
				if(tmp != 0) {
					strcat(prime_str[k], ",");
				}
				sprintf(buffer, "%d", PI[i][j]);
				strcat(prime_str[k], buffer);
				tmp ++;
			}
			else
				break;
		}	
		strcat(prime_str[k], "\0");
		k ++;
	}
	j = 2;
	for(i = 0; i < mterm3; i ++) {
		lable = gtk_label_new(prime_str[i]);
		gtk_table_attach(GTK_TABLE(table), lable, 2, 4, j, j + 1, GTK_FILL, GTK_FILL, 50, 10);
		j ++;
	}


	lable = gtk_label_new("Minterms");
	gtk_table_attach(GTK_TABLE(table), lable, 4, (mterms + 4), 0, 1, GTK_FILL, GTK_FILL, 50, 10);
	char substr[5];
	for(i = 0; i < mterms; i ++) {
		sprintf(substr, "%d", input[i]);
		lable = gtk_label_new(substr);
		gtk_table_attach(GTK_TABLE(table), lable, (4 + i), (4 + i + 1), 1, 2, GTK_FILL, GTK_FILL, 50, 10);
	}
	if(flag == 0) {
		for(i = 0; i < mterm3; i ++) {
			for(k = 0; k < mterms; k ++) {
				for(j = 0; j < prime; j ++) {
					if(input[k] ==  PI[i][j]) {
						lable = gtk_label_new("*");
						gtk_table_attach(GTK_TABLE(table), lable, (4 + k), (4 + k + 1), i + 2, i + 3, GTK_FILL, GTK_FILL, 50, 10);			
						break;
					}
				}
			}
		}
	vbox = gtk_vbox_new(0, 0);
	button = gtk_button_new_with_label("NEXT");
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);	
	gtk_table_attach(GTK_TABLE(table), vbox, 4, 5, i + 2, i + 3, GTK_FILL, GTK_FILL, 50, 10);

	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (essential_prime_implicant), (gpointer) popup_window);
	}
	int *count;
	count = (int *)malloc(mterms * sizeof(int));
	for(i = 0; i < mterms; i ++) {
		count[i] = 0;
	}
	char ess_str[CHARMAX];
	ess_str[0] = '\0';
	if(flag == 1) {
		for(i = 0; i < mterm3; i ++) {
			for(k = 0; k < mterms; k ++) {
				for(j = 0; j < prime; j ++) {
					if(input[k] ==  PI[i][j]) {
						count[k] ++;
						break;
					}
				}
			}
		}
		for(i = 0; i < mterm3; i ++) {
			flag = 0;
			for(k = 0; k < mterms; k ++) {
				for(j = 0; j < prime; j ++) {
					if(input[k] ==  PI[i][j]) {
						if(count[k] == 1) {	
							if(flag == 0) {
								strcat(ess_str, string[i]);
								strcat(ess_str, " + ");
								flag ++;
							}
							lable = gtk_label_new("@");
							gtk_table_attach(GTK_TABLE(table), lable, (4 + k), (4 + k + 1), i + 2, i + 3, GTK_FILL, GTK_FILL, 50, 10);			
						}
						else if(count[k] > 1) {
							lable = gtk_label_new("*");
							gtk_table_attach(GTK_TABLE(table), lable, (4 + k), (4 + k + 1), i + 2, i + 3, GTK_FILL, GTK_FILL, 50, 10);			
						}
					}
				}
			}
		}
	}
		
	flag ++;
	printf("%s", ess_str);

	gtk_container_add(GTK_CONTAINER(popup_window), table);
	g_signal_connect(popup_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(popup_window);
	gtk_main();
}
		

	

	
void print_prime_implicant (GtkButton* widget, GtkWidget* pWindow) {
 	GtkWidget *popup_window, *lable, *table, *button, *vbox;

	popup_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (popup_window), "Pop Up window");
	gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
	gtk_window_set_resizable (GTK_WINDOW (popup_window), TRUE);

	gtk_widget_set_size_request (popup_window, 600, 800);
	//gtk_window_set_transient_for (GTK_WINDOW (popup_window), GTK_WINDOW (pWindow));
	gtk_window_set_position (GTK_WINDOW (popup_window), GTK_WIN_POS_CENTER);
	int i, j;
	char *str[mterm3];
	for(i = 0; i < mterm3; i ++) {
		str[i] = (char *)malloc(nvar * sizeof(char));
	}
	table = gtk_table_new(mterm3, 6, 0);
	
	lable = gtk_label_new("Varibles");
	gtk_table_attach(GTK_TABLE(table), lable, 4, 6, 0, 1, GTK_FILL, GTK_FILL, 50, 10);
	for(i = 0; i < mterm3; i ++) {
		for(j = 0; j < nvar; j ++) {
			if(ptr3[i][j] == 40) {
				str[i][j] = '*';
			}
			else
				str[i][j] = ptr3[i][j] + '0';
		}
		str[i][j] = '\0';

	}	
	
	for(i = 0; i < mterm3; i ++) {
		lable = gtk_label_new(str[i]);
		gtk_table_attach(GTK_TABLE(table), lable, 4, 6, i + 1, i + 2, GTK_FILL, GTK_FILL, 50, 10);
	}

	lable = gtk_label_new("Expression");
	gtk_table_attach(GTK_TABLE(table), lable, 2, 4, 0, 1, GTK_FILL, GTK_FILL, 50, 10);
	chardata var;
	cinitialize(&var);
	char string[20];
	char ch;
	int n;
	for(i = 0; i < nvar; i ++) {
		if(!cisfull(&var)) {
			ch = 'A' + i;
			cpush(&var, ch);
		}
	}

	for(i = 0; i < mterm3; i ++) {
		n = 0;
		for(j = 0; j < nvar; j ++) {
			if(ptr3[i][j] != 40) {
				if(ptr3[i][j] == 1) {
					string[n] = cremove(&var, j);
					n ++;
				}
				else if(ptr3[i][j] == 0) {
					string[n] = '~';
					n ++;
					string[n] = cremove(&var, j);
					n ++;
				}
			}
		}
		string[n] = '\0';			
		lable = gtk_label_new(string);
		gtk_table_attach(GTK_TABLE(table), lable, 2, 4, i + 1, i + 2, GTK_FILL, GTK_FILL, 50, 10);
					
	}

	lable = gtk_label_new("Minterm");
	gtk_table_attach(GTK_TABLE(table), lable, 0, 2, 0, 1, GTK_FILL, GTK_FILL, 50, 10);

	char *prime_str[mterm3];
	for(i = 0; i < mterm3; i ++) {
		prime_str[i] = (char *)malloc(prime * sizeof(char));
	}
	for(i = 0; i < mterm3; i ++) {
		strcpy(prime_str[i], "\0");
	}
	int k = 0;
	char buffer[5];
	int tmp;
	buffer[0] = '\0';
	for(i = 0; i < mterm3; i ++) {
		tmp = 0;
		for(j = 0; j < prime; j ++) {
			if(PI[i][j] != NOVALUE) {
				if(tmp != 0) {
					strcat(prime_str[k], ",");
				}
				sprintf(buffer, "%d", PI[i][j]);
				strcat(prime_str[k], buffer);
				tmp ++;
			}
			else
				break;
		}	
		strcat(prime_str[k], "\0");
		k ++;
	}
	j = 1;
	for(i = 0; i < mterm3; i ++) {
		lable = gtk_label_new(prime_str[i]);
		gtk_table_attach(GTK_TABLE(table), lable, 0, 2, j, j + 1, GTK_FILL, GTK_FILL, 50, 10);
		j ++;
	}
	vbox = gtk_vbox_new(0, 0);
	button = gtk_button_new_with_label("ESSENTIAL PRIME IMPLICANT");
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);	
	gtk_table_attach(GTK_TABLE(table), vbox, 4, 5, j, j + 1, GTK_FILL, GTK_FILL, 50, 10);

	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (essential_prime_implicant), (gpointer) popup_window);

	gtk_container_add(GTK_CONTAINER(popup_window), table);
	g_signal_connect(popup_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(popup_window);
	gtk_main();
}
		
		
void on_popup_clicked (GtkButton* widget, GtkWidget* pWindow) {
	static int currstep = -1;
	currstep ++;
	int *count, res = 0;	
	char substr[10];
	int  i, j, k, m, n;
	int rows = (nvar + 1) * NMAX;
	int flag = 0;
	char *str[rows];
	count = (int *)malloc((nvar - currstep + 1) * sizeof(int));
	for(i = 0; i <= (nvar - currstep); i ++) {
		count[i] = 0;
	}
 	GtkWidget *popup_window, *lable, *table, *button, *vbox;

	popup_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (popup_window), "Pop Up window");
	gtk_container_set_border_width (GTK_CONTAINER (popup_window), 10);
	gtk_window_set_resizable (GTK_WINDOW (popup_window), TRUE);

	gtk_widget_set_size_request (popup_window, 600, 800);
	//gtk_window_set_transient_for (GTK_WINDOW (popup_window), GTK_WINDOW (pWindow));
	gtk_window_set_position (GTK_WINDOW (popup_window), GTK_WIN_POS_CENTER);

	for(i = 0; i < rows; i ++) {
		str[i] = (char *)malloc(5 * sizeof(char));
	}
	table = gtk_table_new(rows, 6, 0);

	
	m = 0;
	for(i = 0; i <= (nvar - currstep); i ++) {
		for(j = 0; j < NMAX; j ++) {
			flag = 0;
			for(k = 0; k < nvar; k ++) {
	
				if(step[currstep][i][j][k] == -1) {
					flag = 1;
					str[m] = NULL;
					m ++;
					break;
				}
				else {
					if(step[currstep][i][j][k] == 40)
						str[m][k] = '*';
					else
						str[m][k] = step[currstep][i][j][k] + '0';	
				}
			}
			if(flag != 1) {
				count[i] ++;
				str[m][k] = '\0';
				m ++;
			}
		}
	}

	for(i = 0; i <= (nvar - currstep); i ++) {
		substr[0] = i + '0';
		substr[1] = '\0';
		lable = gtk_label_new(substr);
		if(count[i] == 0)
			continue;
		gtk_table_attach(GTK_TABLE(table), lable, 0, 1, res + 1, res + 2, GTK_FILL, GTK_FILL, 50, 10);
		res = res + count[i];


	}

	int *arr[m];
	int nterms = pow(2, nvar);
	for(i = 0; i < m; i ++) {
		arr[i] = (int *)malloc(nterms * sizeof(int));
	}
	int value = 0;
	for(i = 0; i <= (nvar - currstep); i ++) {
		for(j = 0; j < NMAX; j ++) {
			if(step[currstep][i][j][0] == -1) {
				break;
			}	
			arr[value] = findminterms(step[currstep][i][j]);
			value ++;
			
		}
	}	


	lable = gtk_label_new("GROUP");
	gtk_table_attach(GTK_TABLE(table), lable, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 50, 10);
	lable = gtk_label_new("MINTERMS");
	gtk_table_attach(GTK_TABLE(table), lable, 1, 3, 0, 1, GTK_FILL, GTK_FILL, 50, 10);
	lable = gtk_label_new("VARIABLES");
	gtk_table_attach(GTK_TABLE(table), lable, 3, 5, 0, 1, GTK_FILL, GTK_FILL, 50, 10);
	j = 1;
	for(i = 0; i < m; i ++) {
		if(str[i] != NULL) {
			lable = gtk_label_new(str[i]);
			gtk_table_attach(GTK_TABLE(table), lable, 3, 5, j, j + 1, GTK_FILL, GTK_FILL, 50, 10);
			j ++;
		}
	}

	char *minstr[value];
	for(i = 0; i < value; i ++) {
		minstr[i] = (char *)malloc(CHARMAX * sizeof(char));
	}
	for(i = 0; i < value; i ++) {
		minstr[i][0] = '\0';
	}
	k = 0;
	char buffer[5];
	int tmp;
	buffer[0] = '\0';
	for(i = 0; i < value; i ++) {
		tmp = 0;
		for(j = 0; j < nterms; j ++) {
			if(arr[i][j] != -1) {
				if(tmp != 0) {
					strcat(minstr[k], ",");
				}
				sprintf(buffer, "%d", arr[i][j]);
				strcat(minstr[k], buffer);
				tmp ++;
			}
			else
				break;
		}	
		k ++;
	}
	j = 1;
	for(i = 0; i < k; i ++) {
		lable = gtk_label_new(minstr[i]);
		gtk_table_attach(GTK_TABLE(table), lable, 2, 3, j, j + 1, GTK_FILL, GTK_FILL, 50, 10);
		j ++;
	}

		
		
	vbox = gtk_vbox_new(0, 0);
	button = gtk_button_new_with_label("NEXT");
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);	
	gtk_table_attach(GTK_TABLE(table), vbox, 4, 5, j, j + 1, GTK_FILL, GTK_FILL, 50, 10);
	gtk_container_add(GTK_CONTAINER(popup_window), table);
	if(currstep != (nvar - 1)) {
		g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (on_popup_clicked), (gpointer) popup_window);
	}
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (print_prime_implicant), (gpointer) popup_window);

		
	g_signal_connect(popup_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(popup_window);
	gtk_main();

	/*gtk_widget_set_events (popup_window, GDK_FOCUS_CHANGE_MASK);
	g_signal_connect (G_OBJECT (popup_window), "focus-out-event", G_CALLBACK (on_popup_focus_out), NULL);

	gtk_widget_show_all (popup_window);
	gtk_widget_grab_focus (popup_window);*/
}



int main (int argc, char *argv[]) {
	int i, value, j, k, l, m;
	int primeimp, mterm1, mterm2;
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

	temp = (int ***)malloc((nvar + 1) * sizeof(int **));
	for(i = 0; i <= nvar; i ++)
		temp[i] = (int **)malloc((combination(nvar, i)) * sizeof(int *));
	for(i = 0; i <= nvar; i ++) {
		for(j = 0; j < combination(nvar, i); j ++) {
			temp[i][j] = (int *)malloc((nvar + 1) * sizeof(int));
		}
	}
	step = (int ****)malloc((nvar + 1) * sizeof(int ***));
	for(i = 0; i <= nvar; i ++) {
		step[i] = (int ***)malloc((nvar + 1 - i) * sizeof(int **));
	}
	for(i = 0; i <= nvar; i ++) {
		for(j = 0; j <= (nvar - i); j ++) {
			step[i][j] = (int **)malloc(NMAX * sizeof(int *));
		}
	}
	for(i = 0; i <= nvar; i ++) {
		for(j = 0; j <= (nvar - i); j ++) {
			for(k = 0; k < NMAX; k ++) {
				step[i][j][k] = (int *)malloc((nvar + 1) * sizeof(int));
			}
		}
	}
	for(i = 0; i <= nvar; i ++) {
		for(j = 0; j <= (nvar - i); j ++) {
			for(k = 0; k < NMAX; k ++) {
				for(l = 0; l <= nvar; l ++) {
					step[i][j][k][l] = -1;
				}
			}
		}
	}
	printstep1();	
	mterm2 = compare(nvar, mterms);




	mterm3 = removedup(nvar, mterm2);
	primeimp = BinaryToDecimal(nvar, mterms);
	EssentialPI(primeimp);

	GtkWidget *window, *lable, *table, *button;
	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW(window), "Parent window");
	gtk_container_set_border_width (GTK_CONTAINER(window), 10);
	gtk_widget_set_size_request (window, 600, 800);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	button = gtk_button_new_with_label("QUUINE Mc-CLAUSKY METHOD");
	gtk_container_add(GTK_CONTAINER(window), button);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (on_popup_clicked), (gpointer) window);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;


}



