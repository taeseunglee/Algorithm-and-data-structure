#include <stdio.h>
#include <stdlib.h>

#define get_min(a,b) ((a)>(b) ? (b):(a))
#define diff(i, j) ((str_fir[i])!=(str_sec[j])? 1:0)

int get_str(char *str);

int main() {
	int test, i;


	scanf("%d\n", &test);
	printf("%d\n", test);

	while (test --) {
		char str_fir[4096], str_sec[4096];
		int len_fir, len_sec;

		// actual length is get_str - 1, but we use length of string + 1
		len_fir = get_str(str_fir);
		len_sec = get_str(str_sec);
		
		int **entry_table = (int **) calloc(len_fir, sizeof(int*));
		int i, j;
		
		for (i = 0; i < len_fir; i++) {
			entry_table[i] = (int *) calloc(len_sec, sizeof(int));
		}


	/* ################################################################### */
		/* initialization */
		i = 0;
		while (i < len_fir && i < len_sec) {
			entry_table[i][0] = i;
			entry_table[0][i++] = i;
		}
		/* Since only one of them is executed, we can use this code */
		while (i < len_fir) {
			entry_table[i++][0] = i;
		}
		while (i < len_sec) {
			entry_table[0][i++] = i;
		}


		/* build the entry_table */
		for (i = 1; i < len_fir; i++) {
			for (j = 1; j < len_sec; j++) {
				entry_table[i][j] = get_min(entry_table[i - 1][j] + 1, get_min(entry_table[i][j - 1] + 1, entry_table[i -1][j - 1] + diff(i, j)));
			}
		}


	/* #################################################################### */
		/* back trace */
		int **data = (int **) calloc(entry_table[len_fir - 1][len_sec - 1], sizeof(int*));
		int sol = entry_table[len_fir - 1][len_sec - 1], k = 0;

		for (i = 0; i < sol; i++) {
			data[i] = (int *) calloc(3, sizeof(int));
		}


		printf("%d\n", sol);		// number of solution steps
		i = len_fir - 1, j = len_sec - 1;
		k = 0;
		while (i && j) {
			// deletion
			if (entry_table[i - 1][j] < entry_table[i][j]) {
				data[k][0] = 0;
				data[k][1] = i--;
			}
			// insertion
			else if (entry_table[i][j - 1] < entry_table[i][j]) {
				data[k][0] = 1;
				data[k][1] = i;
				data[k][2] = str_sec[j--];
			}
			// replacement
			else {
				if (diff(i, j)) {
					data[k][0] = 2;
					data[k][1] = i;
					data[k][2] = str_sec[j];
				}
				else {
					k--;
				}
				i --, j --;
			}
			k ++;
		}

		// deletion
		while (i) {
			data[k][0] = 0;
			data[k++][1] = i--;
		}

		// insertion
		while (j) {
			data[k][0] = 1;
			data[k][1] = i;
			data[k++][2] = str_sec[j--];
		}


	/* #################################################################### */
		/* print the traces of  solution */
		for (k = sol - 1; k >= 0; k--) {
			switch (data[k][0]) {
				case 0 : /* deletion */
					printf("D %d\n", data[k][1]);
					break;
				case 1 : /* insertion */
					printf("I %d %c\n", data[k][1], data[k][2]);
					break;
				case 2: /* replacement */
					printf("R %d %c\n", data[k][1], data[k][2]);
					break;
			}
		}



	/* #################################################################### */
		/* free allocated memory */
		for (i =0; i < sol; i++) {
			free(data[i]);
		}
		free(data);

		for (i = 0; i < len_fir; i++) {
			free(entry_table[i]);
		}
		free(entry_table);
	}

	return 0;
}


/* argument		: pointer of string
 * return		: length of string 
 * description	: store input to str and return length of string.
 *				 initial point is str+1.
 * */
int get_str(char *str) {
	int i = 0;

	while (scanf("%c", &str[++i]) && str[i] != '\n');
	str[i] = '\0';

	return i;
}
