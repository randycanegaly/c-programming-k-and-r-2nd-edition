#include <stdio.h>

/*
implement a modification to squeeze() that deletes each character in s1
that matches a character in s2
*/

void squeeze(char s[], int c);
void chopper(char first[], char second[]);

int main (int argc, char *argv[]) {
	int result;

	if (argc < 3) 
		printf("You need to input two strings.\n");
	else {
		//squeeze(argv[1],  *argv[2]);
		chopper(argv[1], argv[2]);
		printf("result is %s\n", argv[1]);
	}
}

/*delete from first any characters in second that match*/
void chopper(char first[], char second[]) {
	int i, j, k;

	for (k = 0; second[k] != '\0'; k++) {
		for (i = j = 0; first[i] != '\0'; i++) {//go until hitting the terminating \0 character
			if (first[i] != second[k]) 
				first[j++] = first[i];
		}
		first[j] = '\0';//terminate the string
	}	
}

/*delete all characters c from string s*/
void squeeze(char s[], int c) {
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++) //go until hitting the terminating \0 character
		if (s[i] != c) 
			s[j++] = s[i];
	s[j] = '\0';//terminate the string
}

