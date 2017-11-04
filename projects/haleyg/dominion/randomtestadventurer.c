#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main (int argc, char** argv) {
	int kingdom[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int testSuccessful = 0, testFailed = 0,i, tests = 50;//sets number of tests, testSuccessful = successful, testFailed = not successful

	for(i = 0; i < tests; i++) {

		int num_players = rand() % 4, player = 0, rand_seed = rand();//set player, #players, and random seed		
		struct gameState *g = malloc(sizeof(struct gameState));//make gamestate
		int status = initializeGame(num_players, kingdom, rand_seed, g);//Initialize the game with values above

		g->deckCount[player] = rand() % MAX_DECK;//randomize deck size
		g->discardCount[player] = rand() % MAX_DECK;//randomize discard size
		g->handCount[player] = rand() % MAX_HAND;//randomize hand size

		int checkStatus = 0,x;//variable to track if cards added were treasure cards or not 
	
		for(x = 0 ; x < g->handCount[player]; x++) {
			if((g->hand[player][x] == gold) || (g->hand[player][x] == silver) || (g->hand[player][x] == copper)) {
				checkStatus++;
			}
		}
		cardEffect(adventurer, 1, 1, 1, g, 0, 0);//play the card

	
		for(x = 0 ; x < g->handCount[player]; x++) {
			if((g->hand[player][x] == gold) || (g->hand[player][x] == silver) || (g->hand[player][x] == copper)) {
				checkStatus--;
			}
		}

		if(checkStatus < 0) 
			testSuccessful++;//if cards were added, and were treasure cards, then this test was successful
		else 
			testFailed++;

		free(g);
	}
	printf("Random Test 1: Adventurer Card");
	printf("\nThere were %d successful adventurer card plays, and %d failures [out of %d games]\n\n", testSuccessful, testFailed, tests);

	return 0;
}
