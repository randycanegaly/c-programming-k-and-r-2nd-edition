#include <stdio.h>

/*
return the first location in s1 where any character of s2 matches
*/

int firstMatch(char first[], char second[]);

int main (int argc, char *argv[]) {
	int result;

	if (argc < 3) 
		printf("You need to input two strings.\n");
	else {
		//squeeze(argv[1],  *argv[2]);
		result = firstMatch(argv[1], argv[2]);
		printf("result is %d\n", result);
	}
}

/*return the first location in s1 where any character from s2 matches*/
int  firstMatch(char first[], char second[]) {
	int i, j;

	for (j = 0; second[j] != '\0'; j++) {
		for (i = 0; first[i] != '\0'; i++) {//go until hitting the terminating \0 character
			if (first[i] == second[j]) 
				return i;
		}
	}	
	return -1;
}


