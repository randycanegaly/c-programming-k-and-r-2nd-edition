#include <stdio.h>

#define MAXLINE 1000 //size limit for input string
#define TABLEN 4 //positions between tab stops
#define FOLDAT 20 //cutoff where a line will be folded

/*
A program to fold lines longer than some cutoff position
*/


 
char line[MAXLINE]; //external char array where all building of output occurs

int expandtab(int pos);
int findablank(int pos);
int newpos(int pos);
void printline(int pos);

/*main function:
	- captures characters one at time from input
	- keeps track of position in the input and line via pos
*/
int main() {
	int c, pos;

	pos = 0;

	while((c = getchar()) != EOF) {
		line[pos] = c; //put the input character into line
		
		if(c == '\t') //see a tab, need to convert to the equivalent number of spaces to see where the line
			//ends up relative to the fold cutoff
			pos = expandtab(pos);
		else if (c == '\n') { //saw a newline character so the input string ended before fold cutoff was hit
			printline(pos);	
			pos = 0; //started a new line, position is back to zero
		} else if (++pos >= FOLDAT) {//check next pos to see if we hit the cutoff, no newline seen yet
			//find a blank character before but nearest the cutoff
			//this is why expanding tabs is important, need to know where blank space is resulting from tabs
			pos = findablank(pos);
			printline(pos); //print line up to that blank - this is the folded string
			pos = newpos(pos); //need to capture the part of the string past the fold cutoff and get
			//a new pos to continue processing
		}
	}
}

int expandtab(int pos) {
	//printf("expandtab() not implemented yet");
	line[pos] = '-';
	for(++pos; pos < FOLDAT && pos % TABLEN != 0; ++pos) {//convert tab to spaces, move position forward unless hit
	//fold boundary or come to next tab stop
		line[pos] = '-';//add space to line 
	} 

	if (pos < FOLDAT) {
		return pos; //didn't hit fold boundary, so pos is still good, return it
	} else {
		printline(pos); //hit the fold boundary, so print the line up to this point
		return 0; //have printed, starting a new line so return zero to be used as new pos = 0
	}
}

int findablank(int pos) {
	while(pos > 0 && line[pos] != ' ') {//back up in line, looking for the nearest blank
		--pos;
	}
	if(pos == 0) {//went all the way to the beginning and didn't find a blank
		//printf("in fab, returning FOLDAT");
		return FOLDAT;
	} else {
		//printf("in fab, returning pos: %d", pos+1);
		return pos + 1; //found a blank, return the next position so that any printing will include the blank
	}
}

void printline(int pos) {
	int i;
	for (i = 0; i < pos; ++i) 
		putchar(line[i]);
	if ( pos > 0 ) //there was some line to print, so need to tack on newline character at end
		putchar('\n'); 
}

int newpos(int pos) {
	//if this was called then we have a situation where the input string ran past the fold boundary
	//pos right now points to somewhere before the fold boundary because the folded string had to be printed out
	//we need to walk line from pos to the fold boundary
	//have an increasing index marking the front of line and an increasing index that starts at pos
	int i, j;
	//check that pos points to a useful position
	if (pos <= 0 || pos >= FOLDAT)
		return 0;//assume we are at the start of a new line
	else {
		i = 0;
		
		for (j = pos; j < FOLDAT; ++j) { //walk from pos to the fold boundary
			line[i] = line[j];//move char to front of line
			++i;//advance "front" marker	
		}

		return i;
	}
}





