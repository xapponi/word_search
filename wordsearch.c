/*
Pseudo Code

(done) 1. Read in the words from the input.txt and store in an array
(done) 2. Create two 40x40 puzzles using ln curses
3. Put the words from input.txt into both puzzles randomly
4. Fill in the 2nd puzzle with random characters

*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses/ncurses.h>
#include <unistd.h>

#define MAXWORDS 100
#define WORDLEN 20

/*************Function Prototypes**************/
//read words from the file
int readWords(char* wl[MAXWORDS], char* filename);
//get the row of an index
int row_of(int index);
int col_of(int index);
//get the index of a location
int index_of(int row, int col);
//trim right side of string
void trimws(char* s);
//draws the puzzle
void draw_puzzle(void);
//generates the puzzle
void generate_puzzle(void);
//2d character array which the puzzle is mapped into


/*************Main Function*******************/
int main(int argc, char* argv[]) {
	//initialize variables
	char* wordlist[MAXWORDS];
	int wordCount;
	int i;
	//get the number of words
	wordCount = readWords(wordlist, argv[1]);

	char puzzle[1641];

	//generate random number for orientation of word
	srand(1);
	int direction[100];
	for (i = 0; i< wordCount; i++) {
		direction[i] = rand()%(2);
		printf("%d\n", direction[i]);
	}

	for(i=0; i<1640;++i){
		if(i%40==0){
			puzzle[i]='\n';
		}
		else{
			puzzle[i]='.';
		}
	}

	for(i=0; i<1640;++i){
		printf("%c", puzzle[i]);
	}
}

/*************Other Functions*****************/
//read words from the file
int readWords(char* wl[MAXWORDS], char* filename) {
	FILE* inFile = NULL;
	inFile = fopen(filename, "r");
	int i = 0;
	for(i=0; !feof(inFile) ; ++i){
		wl[i] = (char*)malloc(WORDLEN*sizeof(char));
		fgets(wl[i], WORDLEN, inFile);
		trimws(wl[i]);
	}

	fclose(inFile);
	return i-1;
}

//int row_of(int index);
int row_of(int index){
	return index / 40;
}

//int col_of(int index);
int col_of(int index){
	return (index % 40);
}

//int index_of(int row, int col);
int index_of(int row, int col){
	int index = 0;
	index += row * 5;
	index += col;
	return index;
}

// trim the right side of each string
void trimws(char* s) {
	int end = strlen(s) - 1;
	while (isspace(s[end])){
		s[end] = 0;
		end -=1;
	}
}
