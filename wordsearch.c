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
#define ROW 12
#define COL 12

/*************Function Prototypes**************/
//read words from the file
int readWords(char* wl[MAXWORDS], char* filename);

void trimws(char* s);



/*************Main Function*******************/
int main(int argc, char* argv[]) {
	//initialize variables
	char* wordlist[MAXWORDS];
	int wordCount;
	//get the number of words
	wordCount = readWords(wordlist, argv[1]);

	char puzzle[ROW][COL];

	int seed = 0;
	srand(seed);
	int i;
	int j;
	for(i=0; i<ROW; ++i){
		for(j=0; j<COL; ++j){
			puzzle[i][j]='.';
		}
	}

	int num_tries;
	int k;
	for(k=0; k<=wordCount; ++k){
		int out_bounds = 1;
		while(out_bounds){
			out_bounds = 0;
			//get a random x and y direction (not 0,0)
			int xdir = 0;
			int ydir = 0;
			while(xdir==0&&ydir==0){
				xdir = rand()%3-1;
				ydir = rand()%3-1;
			}
			i = rand()%(ROW);
			j = rand()%(COL);
			//printf("%d, %d, %s, %d, %d\n", xdir, ydir, wordlist[k], i, j);
			int ii = i;
			int jj = j;
			//puzzle[i][j] = wordlist[k][0];
			int letter;
			for(letter=0; letter<strlen(wordlist[k]); ++letter){
				num_tries = 0;
				//printf("(%d,%d)",i, j);
				if(puzzle[i][j]!=wordlist[k][letter]){
					if(j>=COL||i<0||j<0||puzzle[i][j]!='.'){
						//printf("1111:%d, %d, %s: %c, %c\n",i,j, wordlist[k], puzzle[i][j], wordlist[k][letter]);
						out_bounds = 1;
						j = j + xdir;
						i = i + ydir;
						//printf("DEBUG");
					}else{
						j = j + xdir;
						i = i + ydir;
					}
				}else{
					j = j + xdir;
					i = i + ydir;
				}
			}
			//printf("\n");
			i = ii;
			j = jj;
			if(out_bounds == 0){
				for(letter=0; letter<strlen(wordlist[k]); ++letter){
					puzzle[i][j]=wordlist[k][letter];
					j = j + xdir;
					i = i + ydir;
				}
			}

		}
	}


	for(i=0; i<ROW; ++i){
		for(j=0; j<COL; ++j){
			if(puzzle[i][j]=='.'&&argv[2]!=0){
				puzzle[i][j]=('A'+rand()%(26));
			}
			printf("%c ", puzzle[i][j]);
		}
		printf("\n");
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

// trim the right side of each string
void trimws(char* s) {
	int end = strlen(s) - 1;
	while (isspace(s[end])){
		s[end] = 0;
		end -=1;
	}
}
