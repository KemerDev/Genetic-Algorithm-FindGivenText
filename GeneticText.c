
/* kemerios*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// String size
#define SIZE 100

// Population Size
#define POP 100

//  Mutation chance

#define MUT 10

// Population Struct
struct population {

	char chr_so[SIZE];
	int fit;

};

struct population pope[POP];

//Random population generation function
void gene_gen(char* word) {

	char temp[strlen(word)];
	temp[strlen(word)] = '\0';

	//generate random genes
	for(int j = POP; j--;) {
		for(int i = 0; i < strlen(word); i++) {
			temp[i] = rand() % (127 - 32) + 32;
		}
		memcpy(pope[j].chr_so, temp, strlen(temp));
		strcpy(pope[j].chr_so, temp);
	}
}

//fitness function
void pop_fitness(char* word) {
	
	for(int i = POP; i--;){
			pope[i].fit = 0;
		}

	//compare strings with the given word and give fitness
	for(int j = POP; j--;) {
		for(int i = 0; i < strlen(word); i++) {
			if(pope[j].chr_so[i] != word[i]) {
				pope[j].fit += 1;
			}
		}
	}
}

// Mutation function
char* mutation(char* mut, char* word) {

	int ch_rand = rand() % strlen(word);

	//change 1 random gene from the kids
	for(int i = 0; i < strlen(word); i++) {
		if(i == ch_rand) {
			mut[i] = rand() % (127 - 32) + 32;
		}
	}
	
	mut[strlen(word)] = '\0';
	
	//return the mutated string
	return mut;
}

void crossover(char* father, char* mother,char* word) {
	
	char temp[strlen(word)];
	char kid1[strlen(word)];
	char kid2[strlen(word)];
	
	kid1[strlen(word)] = '\0';
	kid2[strlen(word)] = '\0';
	temp[strlen(word)] = '\0';
	
	int ran_mut;
	
	// Get a random crossover point
	int ch_rand = rand() % strlen(word);;
	
	//crossover parents 
	for(int i = ch_rand; i < strlen(word); i++) {
		temp[i] = father[i];
		father[i] = mother[i];
		mother[i] = temp[i];
	}
	
	// copy parents string into the kids arrays
	
	strcpy(kid1, father);
	strcpy(kid2, mother);
	
	// chance to get into mutation
	ran_mut = 1 + rand() % 100;

	//chance for the first kid to mutate
	if(ran_mut <= MUT) {
		strcpy(kid1, mutation(kid1, word));
	}
	
	ran_mut = 0;
	// chance to get into mutation
	ran_mut = 1 + rand() % 100;
	
	//chance for the second kid to mutate
	if(ran_mut <= MUT) {
		strcpy(kid2, mutation(kid2, word));
	}

	//kill 1 random and store the kid ---->
	ch_rand = rand() % POP;
	strcpy(pope[ch_rand].chr_so, kid1);

	ch_rand = 0;

	ch_rand = rand() % POP;
	strcpy(pope[ch_rand].chr_so, kid2);
	// <------ kill 1 random and store the kid
	
	// free up those arrays
	for(int i = strlen(word); i--;){
		kid1[i] = ' ';
		kid2[i] = ' ';
		temp[i] = ' ';
	}
	
	
}

void selection(char* word) {

	char* father = (char*) malloc(strlen(word));
	char* mother = (char*) malloc(strlen(word));;

	int fit_fath;
	int fit_mo;

	int choo_get;
	int mesa;

	int max = strlen(word);
	
	// Choose random number of individuals from population
	choo_get = rand() % POP;
	
	// Get Parents -------->
	for(int i = 0; i < choo_get; i++) {
		mesa = rand() % choo_get;
		if(pope[mesa].fit < max) {
			strcpy(father, pope[mesa].chr_so);
			max = pope[mesa].fit;
		}
	}
	max = strlen(word);
	
	// Choose random number of individuals from population
	choo_get = rand() % POP;

	for(int i = 0; i < choo_get; i++) {
		mesa = rand() % choo_get;
		if(pope[mesa].fit < max) {
			strcpy(mother, pope[mesa].chr_so);
			max = pope[mesa].fit;
		}
	}
	// <--------- get parerts

	// into crossover function --->
	crossover(father, mother, word);
	
	// free up those arrays
	for(int i = strlen(word); i--;){
		father[i] = ' ';
		mother[i] = ' ';
	}

}

int main(void) {
	
	srand((unsigned int)time(NULL));

	char* word = (char*) malloc(SIZE);

	int True = 1;
	
	printf("Give a word or a string or whatever: ");
	gets(word);
	
	word[SIZE] = '\0';

	gene_gen(word);

	pop_fitness(word);
	
	int b = 0;

	while(True) {

		selection(word);
		pop_fitness(word);

		for(int i = POP; i--;) {
			if(strcmp(pope[i].chr_so, word) == 0) {
				printf("I found: %s in gene: %d", pope[i].chr_so, b);
				True = 0;
			}
		}
		b++;
	}
}