//Aaden Garcia
//Project 10
// 5/1/26

#include <stdio.h>
#include <stdbool.h>

#define WORD_LEN 6
#define MAX_GUESSES 6

void loadWord(char mystery[]);
void toLowerCase(char word[]);
bool isLetter(char c);
bool validGuess(char word[]);
int stringLength(char str[]);
bool wordsMatch(char a[], char b[]);
void displayGuesses(char guesses[MAX_GUESSES][WORD_LEN], int guessCount, char mystery[]);
bool letterInWord(char letter, char word[]); 
bool letterAlreadyCorrect(char guess[], char mystery[], int pos);

int main() {
	char mystery[WORD_LEN];
	char guesses[MAX_GUESSES][WORD_LEN];
	char currentGuess[WORD_LEN];
	int guessCount = 0;
	bool won = false;
	loadWord(mystery);
	
	printf("Welcome to Twordle!\n");
	while (guessCount < MAX_GUESSES && !won) {
	
		bool valid = false;
		while (!valid) {
			printf("Enter guess #%d: ", guessCount + 1);
			scanf("%5s", currentGuess);
			
			toLowerCase(currentGuess);
			
			if (stringLength(currentGuess) != 5) {
				printf("Invalid guess! Must be exactly 5 letters.\n");
				} else { 
					valid = true;
					
				for (int i = 0; i < 5; i++){
					if (!isLetter(currentGuess[i])) {
						valid = false;
					}
				}
			if (!valid) { 
				printf("invlaid guess! Letters only.\n");
				}	
			}
				for (int i = 0; i < WORD_LEN; i++){
					guesses[guessCount][i] = currentGuess[i];
					}
			guessCount++;
			
			displayGuesses(guesses, guessCount, mystery);
			
			if (wordsMatch(currentGuess, mystery)) {
			won = true;
		}
	}
}
	if (won) {
		printf("Congrats! You guessed the word!\n");
	} else {
		printf("Out of guesses! The Word was: %s\n", mystery);
	}
	return 0;
}

void loadWord(char mystery[]) { 
	FILE *file = fopen("mystery.txt", "r");
	
	if (file == NULL) {
		printf("Error opening mystery.txt\n");
		return;
	}
	char words [200][6];
	int count = 0;
	
	while (fscanf(file, "%5s", words[count]) == 1) {
		count ++;
	}

	fclose(file);
	
	int seed;
	printf("Enter a number for word slection: ");
	scanf("%d", &seed);
		
	int index = seed % count;
	
	for (int i = 0; i < 6; i++){
		mystery[i] = words[index][i];
		}
	toLowerCase(mystery);
}

void toLowerCase(char word[]) {
	int i = 0;
	
	while (word[i] != '\0') {
		if (word[i] >= 'A' && word[i] <= 'Z') {
			word[i] = word[i] + 32;
		}
		i++;
	}
}

bool isLetter(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int stringLength(char str[]) {
	int lenght = 0;
	
	while (str[lenght] != '\0') {
		lenght++;
	}
	return lenght;
}

bool wordsMatch(char a[], char b[]) {
	for (int i = 0; i < 5; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

bool letterInWord(char letter, char word[]) {
	for (int i = 0; i < 5; i++) {
		if (word[i] == letter) {
			return true;
		}
	}
	return false;
}

bool letterAlreadyCorrect(char guess[], char mystery[], int pos) {
	for (int i = 0; i < 5; i++) {
		if (guess[i] == mystery[i] && guess[pos] == guess[i]) {
		 return true;
		 }
	}
	return false;
}

void displayGuesses(char guesses[MAX_GUESSES][WORD_LEN], int guessCount, char mystery[]) {
	for (int i = 0; i < guessCount; i++) {
		for (int j = 0; j < 5; j++) {
			char c = guesses[i][j];
			if (c == mystery[j]) {
				c = c - 32;
			}
			printf("%c", c);
		}
	printf("\n");
	for (int j = 0; j < 5; j++) {
		if (guesses[i][j] != mystery[j] && letterInWord(guesses[i][j], mystery) && !letterAlreadyCorrect(guesses[i], mystery, j)) {
			printf("^");
		} else { 
			printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

	
	
	
	
	
	
	
	
	
	
